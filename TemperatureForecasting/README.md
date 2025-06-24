# IoT Project: Real-Time Environmental Monitoring & Temperature Prediction

This project demonstrates a complete IoT-based system for real-time environmental monitoring and temperature prediction using machine learning and deep learning techniques.

## Project Overview

Over a period of 5 days, temperature and humidity data were collected every minute using an ESP32-based smart sensor system. The data was transmitted to a local machine and stored for further analysis. The main goal was to build predictive models that forecast temperature trends based on historical data.

## Features

- **Real-Time Data Collection** using ESP32 and digital sensors (SHT4x/HTS221)
- **MQTT Protocol Integration** for efficient data transfer
- **Data Storage** on local desktop/laptop for offline analysis
- **Temperature Prediction Models:**
  - Linear Regression (LR)
  - Support Vector Regression (SVR)
  - Long Short-Term Memory (LSTM) Neural Network
- **Model Comparison** in terms of prediction accuracy and visualization

## How to Run

1. Connect the ESP32 with your PC
2. Run the MQTT broker on your local machine or cloud
3. Collect data for at least a few hours (ideally 5 to 7 days)
4. Use this data to train and evaluate prediction models

## Author

**Hammad Hassan** – Electrical Engineer & AI Enthusiast  
_“Building smart systems with clean code and clear vision.”_



