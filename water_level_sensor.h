#ifndef WATER_LEVEL_SENSOR_H
#define WATER_LEVEL_SENSOR_H

#include <Arduino.h>

// Define pin numbers for water level sensors
#define WL_SENS_1 A5
#define WL_SENS_2 A4
#define WL_SENS_3 A3
#define WL_SENS_4 A2

// Define threshold and maximum pump time
#define WL_THRESH 650
#define MAX_PUMP_TIME 15000 // 15 seconds

// Function prototypes
int get_water_level(int container);  // Read water level for a specific container
void pump_to_container(int container); // Pump water to a specific container

#endif
