# IoT Projects Collection

Welcome to my collection of Internet of Things (IoT) projects! These projects demonstrate how smart devices, sensors, and wireless communication can work together to gather, analyze, and act on real-world data.

Each project combines hardware programming (using ESP32S2 and sensors) with software tools (Python, MQTT, ML/DL models) to build intelligent and connected systems.

---

## Projects Overview

| Project | Description | Key Features |
|--------|-------------|--------------|
| [Project 1: Watchdog Timer & FreeRTOS](./WatchdogRTOS) | Demonstrates task management and system reliability using FreeRTOS and ESP32's hardware watchdog timer | FreeRTOS tasks, ESP32 WDT, fault simulation |
| [Project 2: Sensor Streaming to NETPIE](./CucumberNetpie) | Reads temperature, humidity, pressure, acceleration, and gyro from multiple sensors on ESP32-S2 (Cucumber), then streams to Serial Monitor and NETPIE cloud every minute | SHT4x/HTS221, BMP280, MPU6050, MQTT, NETPIE |
| [Project 3:Temperature Prediction](./TemperatureForecasting) | Minutely data logging for 5 days and temperature forecasting using ML/DL | Linear Regression, SVR, LSTM |


---

## Tech Stack

- **Microcontroller**: ESP32S2 
- **Sensors**: SHT4x, HTS221, PIR, BMP280, MPU6050
- **Protocols**: MQTT, HTTP, WebSocket
- **Languages**: C++ (Arduino), Python
- **ML/DL Tools**: scikit-learn, TensorFlow/Keras
- **Visualization**: Matplotlib, Seaborn, Web Dashboard

---

## Getting Started

Each project folder contains:
- Python scripts or notebooks for data processing or analysis
- README with instructions for hardware setup and execution

**To run a project:**
1. Navigate to the project folder
2. Follow the setup guide in its README
3. Flash the ESP32 with the provided code
4. Run the Python or dashboard interface if included

---

## About Me

**Hammad Hassan**  
Electrical Engineer | AI & IoT Developer  
📫 _Building smart, data-driven systems with real-world impact._

---
