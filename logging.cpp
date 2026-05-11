#include <Arduino.h>
#include "logging.h"

void printStatus(const HVACData &data) {
    Serial.println("----------------------");

    Serial.print("Temperature: ");
    Serial.print(data.temperature);
    Serial.println(" °C");

    Serial.print("Setpoint: ");
    Serial.print(data.setpoint);
    Serial.println(" °C");

    Serial.print("Fan/LED: ");
    Serial.println(data.fanOn ? "ON" : "OFF");

    Serial.print("Emergency: ");
    Serial.println(data.emergency ? "YES" : "NO");

    Serial.print("Sensor Fault: ");
    Serial.println(data.sensorFault ? "YES" : "NO");
}