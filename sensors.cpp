#include "sensors.h"
#include "config.h"

DHT dht(DHTPIN, DHTTYPE);

void initSensors() {
    dht.begin();
}

void readSensors(HVACData &data) {

    // Read temperature from DHT22
    float temp = dht.readTemperature();

    // Sensor anomaly detection
    if (isnan(temp) || temp < -40 || temp > 125) {
        data.sensorFault = true;
        return;
    }

    data.sensorFault = false;
    data.temperature = temp;

    // ADC filtering: take 10 samples and average them
    int total = 0;
    const int samples = 10;

    for (int i = 0; i < samples; i++) {
        total += analogRead(POT_PIN);
        delay(5);
    }

    int averagePotValue = total / samples;

    // Convert filtered ADC value 0-4095 to setpoint 18-35°C
    data.setpoint = map(
        averagePotValue,
        0,
        4095,
        MIN_SETPOINT,
        MAX_SETPOINT
    );
}