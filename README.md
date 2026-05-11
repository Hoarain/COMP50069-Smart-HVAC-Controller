# Industrial IoT Smart HVAC Controller

## Overview
This project is an Industrial IoT Smart HVAC Controller developed using ESP32 and FreeRTOS for the COMP50069 Hardware, Microcontrollers and Sensors module.

The system monitors temperature using a DHT22 sensor and automatically controls a simulated HVAC fan using an LED output.

## Features
- FreeRTOS multitasking
- Mutex-protected shared data
- Interrupt-driven emergency reset button
- Software debouncing
- 12-bit ADC integration
- ADC filtering
- Sensor anomaly detection
- Industrial fail-safe emergency logic
- Watchdog timer
- Serial diagnostic logging

## Hardware Used
- ESP32
- DHT22 Temperature Sensor
- Potentiometer
- Push Button
- LED
- Buzzer

## FreeRTOS Tasks
- Sensor Task
- Safety Task
- Control Task
- Logging Task

## Safety Features
- Overheat shutdown
- Emergency recovery
- Sensor fault detection
- Alarm buzzer
- Watchdog timer

## Author
Juthamat Rachsuwo
