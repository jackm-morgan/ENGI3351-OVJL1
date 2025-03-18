#ifndef MAVLINK_COMMUNICATION_H
#define MAVLINK_COMMUNICATION_H

#include <Arduino.h>
#include <mavlink.h>

#define MAX_SAMPLES 4			// Number of Containers

// Function prototypes
void setupMavlink();                  // Initialize MAVLink communication
void handleMavlinkCommunication();    // Handle incoming MAVLink messages

#endif
