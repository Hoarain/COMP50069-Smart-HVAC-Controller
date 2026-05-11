#include <Arduino.h>
#include "safety.h"
#include "config.h"

volatile bool resetRequest = false;
volatile unsigned long lastInterruptTime = 0;

void IRAM_ATTR buttonISR() {

    unsigned long currentTime = millis();

    // Debounce protection
    if (currentTime - lastInterruptTime > 300) {
        resetRequest = true;
        lastInterruptTime = currentTime;
    }
}

void initSafety() {

    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    digitalWrite(BUZZER_PIN, LOW);

    attachInterrupt(
        digitalPinToInterrupt(BUTTON_PIN),
        buttonISR,
        FALLING
    );
}

bool emergencyResetRequested() {

    if (resetRequest == true) {
        resetRequest = false;
        return true;
    }

    return false;
}

void checkSafety(HVACData &data) {

    // Overheat detection
    if (data.temperature >= OVERHEAT_LIMIT) {
        data.emergency = true;
    }

    // Sensor anomaly detection
    if (data.sensorFault == true) {
        data.emergency = true;
    }

    // Reset emergency when safe
    if (
        emergencyResetRequested() &&
        data.temperature < OVERHEAT_LIMIT &&
        data.sensorFault == false
    ) {
        data.emergency = false;
    }

    // Alarm buzzer
    if (data.emergency == true) {
        digitalWrite(BUZZER_PIN, HIGH);
    } else {
        digitalWrite(BUZZER_PIN, LOW);
    }
}