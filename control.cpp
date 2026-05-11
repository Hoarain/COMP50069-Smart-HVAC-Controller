#include <Arduino.h>
#include "control.h"
#include "config.h"

void initControl() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void updateControl(HVACData &data) {

    if (data.emergency == true) {
        data.fanOn = false;
        digitalWrite(LED_PIN, LOW);
        return;
    }

    if (data.temperature > data.setpoint) {
        data.fanOn = true;
        digitalWrite(LED_PIN, HIGH);
    } else {
        data.fanOn = false;
        digitalWrite(LED_PIN, LOW);
    }
}