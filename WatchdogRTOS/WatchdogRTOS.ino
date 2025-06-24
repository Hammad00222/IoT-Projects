#include <WiFi.h> 
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <esp_sleep.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"

// Wi-Fi credentials
const char* ssid = "iPhone 15";
const char* password = "password";

// NTP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7*3600, 60000);

// Task handles
TaskHandle_t task1_handle = NULL;
TaskHandle_t task2_handle = NULL;

// Function prototypes
void disableWatchdog();

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi.");


  // Initialize time
  timeClient.begin();


  // Create tasks
  xTaskCreatePinnedToCore(
    task1,
    "Task1",
    4096,
    NULL,
    1,
    &task1_handle,
    PRO_CPU_NUM
  );

  xTaskCreatePinnedToCore(
    task2,
    "Task2",
    4096,
    NULL,
    2,
    &task2_handle,
    PRO_CPU_NUM
  );

  xTaskCreatePinnedToCore(
    task3,
    "Task3",
    4096,
    NULL,
    3,
    NULL,
    PRO_CPU_NUM
  );
}

void loop() {
  // Empty - FreeRTOS tasks handle the work
}

void task1(void *pvParameters) {
  while (1) {
    Serial.print("Current Time: ");
    Serial.println(timeClient.getFormattedTime());
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay 1 second
  }
}

void task2(void *pvParameters) {
  while (1) {
    Serial.println("Updating time from NTP server...");
    timeClient.update();
    vTaskDelay(60000 / portTICK_PERIOD_MS);
  }
}

void task3(void *pvParameters) {
  vTaskDelay(600000 / portTICK_PERIOD_MS); // Wait 10 minutes
  
  // Suspend other tasks
  vTaskSuspend(task1_handle);
  vTaskSuspend(task2_handle);
  
  // Prepare for deep sleep
  disableWatchdog();
  Serial.println("Entering deep sleep for 10 minutes");
  
  esp_sleep_enable_timer_wakeup(600 * 1000000);
  esp_deep_sleep_start();
}

void disableWatchdog() {
  // Disable Watchdog timer
  esp_task_wdt_deinit(); 
  Serial.println("Watchdog timer disabled.");
}
