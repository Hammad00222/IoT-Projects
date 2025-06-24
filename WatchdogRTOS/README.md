# Project 1: Watchdog Timer with FreeRTOS

This project demonstrates how to implement a **Watchdog Timer (WDT)** using **FreeRTOS** on an ESP32 board. It ensures the system can automatically reset itself if any task becomes unresponsive or crashes.

## Key Features

- FreeRTOS-based multitasking
- Watchdog Timer configured for system safety
- Simulated task hang to trigger system reset
- Serial output to observe task status and reset events

## Technologies Used

- ESP32 / Arduino Framework
- FreeRTOS
- Serial Monitor Debugging

## How to Run

1. Flash the code to the ESP32 board.
2. Open Serial Monitor to observe:
   - Task execution logs
   - WDT-triggered system reset when a task hangs

## Use Case

Useful in any real-time or embedded system where high availability is required, such as industrial controllers or IoT edge devices.

---

