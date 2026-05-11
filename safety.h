#ifndef SAFETY_H
#define SAFETY_H

#include "sensors.h"

void initSafety();
void checkSafety(HVACData &data);
bool emergencyResetRequested();

#endif