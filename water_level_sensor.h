#ifndef WATER_LEVEL_SENSOR_H
#define WATER_LEVEL_SENSOR_H

#include <Arduino.h>

#define WL_SENS_1 A5
#define WL_SENS_2 A4
#define WL_SENS_3 A3
#define WL_SENS_4 A2
#define WL_THRESH 650
#define MAX_PUMP_TIME 15000 // 15 secs

int get_water_level(int container);
void pump_to_container(int container);

#endif
