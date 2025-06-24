#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_HTS221.h>
#include <Adafruit_SHT4x.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

// Hardware Objects
Adafruit_BMP280 bmp;
Adafruit_HTS221 hts;
Adafruit_SHT4x sht;
Adafruit_MPU6050 mpu;

// FreeRTOS Components
QueueHandle_t sensorQueue;
struct SensorData {
  float pressure;
  float temperature;
  float humidity;
  float accel[3];
  float gyro[3];
};

// NETPIE Configuration
const char* NETPIE_CLIENT_ID = "3403ada3-4db0-4e33-bed8-61dfef581791";
const char* NETPIE_TOKEN = "PxB5RC2RQqJQ9hkpEXbwwkc9GstxKX6u";
const char* NETPIE_SECRET = "gF8ckoiBmvLKUy7CcHQUBVA9LpSB4bAx";
WiFiClient espClient;
PubSubClient mqttClient(espClient);

// Sensor Detection Flags
bool hasBMP     = false;
bool hasHTS221  = false;
bool hasSHT4x   = false;
bool hasMPU     = false;

void setupHardware() {
  Wire.begin(41, 40, 100000);
  
  // Detect Temperature/Humidity Sensor
  if (hts.begin_I2C()) {
    hasHTS221 = true;
    Serial.println("HTS221 sensor ready");
  } 
  else if (sht.begin()) {
    hasSHT4x = true;
    Serial.println("SHT4x sensor ready");
  }

  // Initialize BMP280
  if (bmp.begin(0x76)) {
    hasBMP = true;
    Serial.println("BMP280 sensor ready");
  }

  // Initialize MPU6050
  if (mpu.begin()) {
    hasMPU = true;
    Serial.println("MPU6050 sensor ready");
  }

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
}

// FreeRTOS Tasks
void sensorTask(void *pvParams) {
  TickType_t lastWakeTime = xTaskGetTickCount();
  const TickType_t interval = pdMS_TO_TICKS(15000);

  while(1) {
    SensorData data;
    
    // Read environmental sensors
    if(hasHTS221) {
      sensors_event_t temp, humid;
      hts.getEvent(&humid, &temp);
      data.temperature = temp.temperature;
      data.humidity = humid.relative_humidity;
    }
    else if(hasSHT4x) {
      sensors_event_t temp, humid;
      sht.getEvent(&humid, &temp);
      data.temperature = temp.temperature;
      data.humidity = humid.relative_humidity;
    }
    
    data.pressure = bmp.readPressure() / 100.0F;
    
    // Read IMU data
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    data.accel[0] = a.acceleration.x;
    data.accel[1] = a.acceleration.y;
    data.accel[2] = a.acceleration.z;
    data.gyro[0] = g.gyro.x;
    data.gyro[1] = g.gyro.y;
    data.gyro[2] = g.gyro.z;

    xQueueSend(sensorQueue, &data, portMAX_DELAY);
    vTaskDelayUntil(&lastWakeTime, interval);
    Serial.println("Sensors data sent to the queue.");
  }
}

void mqttTask(void *pvParams) {
  mqttClient.setServer("broker.netpie.io", 1883);
  
  while(1) {
    if (!mqttClient.connected()) {
      if (mqttClient.connect(NETPIE_CLIENT_ID, NETPIE_TOKEN, NETPIE_SECRET)) {
        mqttClient.subscribe("@shadow/data/update");
        mqttClient.subscribe("@msg/sensors/cucumber");
      }
    }
    
    SensorData data;
    if(xQueueReceive(sensorQueue, &data, portMAX_DELAY)) {
      
      String payload = "{ \"data\": { ";
      payload += "\"temperature\": " + String(data.temperature) + ", ";
      payload += "\"humidity\": " + String(data.humidity) + ", ";
      payload += "\"pressure\": " + String(data.pressure) + ", ";
      payload += "\"acceleration\": [" + String(data.accel[0]) + "," + String(data.accel[1]) + "," + String(data.accel[2]) + "], ";
      payload += "\"gyro\": [" + String(data.gyro[0]) + "," + String(data.gyro[1]) + "," + String(data.gyro[2]) + "] ";
      payload += "} }";
  
      mqttClient.publish("@shadow/data/update", payload.c_str());
      mqttClient.publish("@msg/sensors/cucumber", payload.c_str());
      Serial.println("Data Published to NETPIE -> " + payload);

    }
    mqttClient.loop();
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}


void setup() {
  Serial.begin(115200);
  setupHardware();
  
  // Initialize WiFi
  WiFi.begin("iPhone 15", "password");
  while (WiFi.status() != WL_CONNECTED) delay(500);
  
  // Create FreeRTOS components
  sensorQueue = xQueueCreate(5, sizeof(SensorData));
  xTaskCreate(sensorTask, "SensorTask", 4096, NULL, 1, NULL);
  xTaskCreate(mqttTask, "MQTTTask", 4096, NULL, 1, NULL);
  
 
}

void loop() {
  // FreeRTOS handles task scheduling
  vTaskDelete(NULL);
}
