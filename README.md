# Smart Power Optimization and Fault Prediction System

## 📌 Project Overview

The Smart Power Optimization and Fault Prediction System is an IoT-based embedded system designed to monitor electrical and operating parameters of a load in real time.

The system uses an ESP32 microcontroller along with current, voltage, temperature, and vibration sensors to monitor the operating condition of the system. Abnormal conditions such as overload and unusual operating behavior can be identified, while the monitored parameters are visualized remotely using the Blynk IoT platform.

## 🎯 Objectives

- Monitor electrical parameters in real time
- Detect overload and abnormal operating conditions
- Monitor temperature and vibration
- Provide remote monitoring through Blynk IoT
- Improve awareness of equipment operating conditions
- Implement an embedded IoT-based monitoring system

## 🛠️ Hardware Components

- ESP32
- ACS712 Current Sensor
- ZMPT101B AC Voltage Sensor
- DS18B20 Temperature Sensor
- Vibration Sensor
- 5V DC Motor
- Relay Module
- BC547 Transistor
- Lithium-Ion Battery

## 💻 Software & Technologies

- Embedded C
- Arduino IDE
- ESP32
- Blynk IoT
- Sensor Interfacing
- IoT
- Embedded Systems

## ⚙️ Working Principle

The ESP32 collects data from the connected sensors.

The ACS712 measures current, while the ZMPT101B monitors AC voltage. The DS18B20 measures temperature and the vibration sensor detects abnormal vibrations.

The ESP32 processes the sensor readings and identifies abnormal operating conditions based on predefined thresholds. The monitored data is also sent to the Blynk IoT platform for remote visualization.

A relay-based control mechanism is used for load control when required.

## 📊 Key Features

- Real-time current monitoring
- Voltage monitoring
- Temperature monitoring
- Vibration monitoring
- Overload detection
- Remote IoT monitoring
- Embedded sensor interfacing
- Relay-based load control

## 🚀 Future Improvements

- Machine-learning-based predictive maintenance
- Improved fault classification
- Data logging and historical analysis
- Mobile notifications for critical faults
- Energy consumption analytics

- ## 📊 Results

The system is designed to monitor current, voltage, temperature and vibration parameters and provide real-time visualization through the Blynk IoT platform. The implemented fault-detection logic can trigger motor protection and alerts when predefined conditions are detected.

## 👩‍💻 Developed By

**Bhoomika N Chikkannavar**

Electronics & Communication Engineering
