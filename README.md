Temperatue & Humidity Monitor

This project implements an ESP32-based DHT server to monitor temperature and humidity, displaying real-time data on a web interface. The firmware is written in C++, utilizing libraries such as WiFi.h, WebServer.h, and DHT.h to handle WiFi connectivity, web server functionality, and sensor interfacing, respectively.

Features:
Real-time monitoring of temperature and humidity.
Web-based interface accessible from any device connected to the same network.
Automatic refresh of data every 4 seconds.
Usage:
Upload the provided firmware to an ESP32 microcontroller.
Connect a DHT temperature and humidity sensor to the ESP32.
Configure the WiFi SSID and password in the firmware.
Power on the ESP32 and access the web interface via a web browser using the ESP32's IP address.
View real-time temperature and humidity data on the web interface.
Technologies Used:
C++: ESP32 microcontroller firmware.
HTML/CSS/JavaScript: Web interface for displaying sensor data.
Libraries: WiFi.h, WebServer.h, DHT.h.
Dependencies:
Arduino Core for ESP32: ESP32 development platform for Arduino IDE.
DHT sensor library: Library for interfacing with DHT temperature and humidity sensors.
