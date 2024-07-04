# LoRaWAN-Based Smart Farming Modular IoT Architecture

## Project Overview

The **LoRaWAN-Based Smart Farming Modular IoT Architecture** is a comprehensive solution designed to enhance agricultural practices using the Internet of Things (IoT) and LoRaWAN technology. This project leverages long-range, low-power wireless communication to collect and monitor environmental data such as soil moisture, temperature, humidity, and light intensity in agricultural fields. The collected data is transmitted to a central server where it is visualized through a web-based application.

## Features

- **Long-Range Communication:** Utilizes LoRaWAN technology to achieve long-distance data transmission with low power consumption.
- **Real-Time Monitoring:** Provides real-time monitoring of soil moisture, temperature, humidity, and light intensity.
- **Web-Based Visualization:** Data is displayed on a web-based platform for easy remote access and management.
- **Automation:** Controls irrigation systems based on soil moisture levels.

## Hardware Requirements

- **DOIT ESP32 DEVKIT V1 BOARD** (x2)
- **LoRa SX1278 RA02** (x2)
- **LoRa ANTENNA** (x2)
- **LDR SENSOR** (x1)
- **DHT11 TEMPERATURE AND HUMIDITY SENSOR** (x1)
- **SOIL MOISTURE SENSOR** (x1)
- **LIQUID CRYSTAL DISPLAY (LCD) 16X2** (x1)
- **I2C MODULE** (x1)
- **RELAY** (x1)
- **SUBMERSIBLE WATER PUMP** (x1)
- **RAINDROP SENSOR** (x1)
- **BREADBOARD 840 POINT** (x2)

## Software Requirements

- **Operating System:** Windows OS
- **Programming Languages:** HTML, CSS, AJAX, JavaScript, PHP
- **Backend:** MySQL Server, PHP
- **IDE:** Visual Studio Code, Arduino IDE, XAMPP
- **Web Hosting:** 000Webhost

## System Architecture

The architecture comprises the following components:
1. **LoRaWAN End Nodes:** Equipped with various sensors to collect environmental data and transmit it to the LoRaWAN gateway.
2. **LoRaWAN Gateway:** Receives data from end nodes, processes it, and forwards it to the cloud. It also features an LCD for real-time data display and a buzzer for alerts.
3. **Cloud Platform:** Manages data storage and provides a web-based interface for visualization.
4. **Web Application:** Displays collected data and allows remote monitoring and control.

## Implementation

### 1. Setting Up Hardware
- Connect sensors to the ESP32 boards.
- Configure the LoRa modules with antennas.
- Set up the LCD and buzzer on the LoRaWAN gateway.

### 2. Software Installation
- Install the necessary libraries for ESP32 and LoRaWAN in Arduino IDE.
- Program the ESP32 for both the gateway and sensor nodes.

### 3. Database and Web Application
- Prepare the database using MySQL.
- Develop the web application using HTML, CSS, and PHP.
- Deploy the web application on 000Webhost.

### 4. Testing and Deployment
- Test the system components to ensure proper communication and data transmission.
- Deploy the system in the agricultural field and monitor performance through the web interface.

## Usage

1. **Field Setup:**
   - Place the LoRaWAN end nodes equipped with sensors at different locations in the field.
   - Ensure the gateway is positioned to receive data from all end nodes.

2. **Monitoring:**
   - Access the web-based application to view real-time data and control irrigation systems based on soil moisture levels.

3. **Maintenance:**
   - Regularly check sensor and gateway functionality.
   - Replace batteries as needed to ensure continuous operation.

## Author

- **Akash R**
