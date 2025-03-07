#ifndef VALVE_CONTROL_H
#define VALVE_CONTROL_H

#include <Arduino.h>

// Define pin numbers for valves and pump
#define VALVE_1 6
#define VALVE_2 10
#define VALVE_3 8 
#define VALVE_4 11
#define VALVE_PURGE 7
#define PUMP 9

// Function prototypes
void setupValves();          // Initialize valve and pump pins
void config_valves(int container); // Configure valves for a specific container
void default_state();        // Set all valves and pump to their default state
void purge();                // Perform a purge operation

#endif
