#ifndef SENSORS_H
#define SENSORS_H

#include "DHT.h"

struct HVACData {
    float temperature;
    float setpoint;
    bool fanOn;
    bool emergency;
    bool sensorFault;
};

void initSensors();
void readSensors(HVACData &data);

#endif