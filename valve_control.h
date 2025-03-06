#ifndef VALVE_CONTROL_H
#define VALVE_CONTROL_H

#include <Arduino.h>

#define VALVE_1 6
#define VALVE_2 10
#define VALVE_3 8 
#define VALVE_4 11
#define VALVE_PURGE 7
#define PUMP 9

void setupValves();
void config_valves(int container);
void default_state();
void purge();

#endif
