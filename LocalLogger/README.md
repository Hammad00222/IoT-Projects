# Project 2: Multisensor Streaming on ESP32-S2 (Cucumber Board)

This project uses the **Cucumber ESP32-S2** board to read multiple sensor values (Temperature, Humidity, Pressure, Acceleration, and Gyroscope) and stream the data both to the **Serial Monitor** and to the **NETPIE** IoT platform via MQTT.

## Sensors Used

- SHT4x / HTS221: Temperature & Humidity
- BMP280: Pressure
- MPU6050: Accelerometer & Gyroscope

## Key Features

- I²C sensor initialization and data acquisition
- Real-time serial output of sensor values
- Data publishing to NETPIE every 60 seconds via MQTT
- FreeRTOS queue for task-safe sensor-to-MQTT communication

## Technologies Used

- ESP32-S2 (Cucumber board)
- PubSubClient (MQTT)
- FreeRTOS Queues and Tasks
- Arduino IDE / PlatformIO

## How to Run

1. Connect ESP32-S2 to PC.
2. Update your Wi-Fi and NETPIE credentials in the code.
3. Upload firmware and open Serial Monitor.
4. Check data being printed and uploaded to NETPIE every minute.

## Use Case

Ideal for environmental monitoring and sensor fusion applications that require both local logging and remote cloud updates.

---

