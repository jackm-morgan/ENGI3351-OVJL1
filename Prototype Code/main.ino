#include "valve_control.h"
#include "water_level_sensor.h"
#include "mavlink_communication.h"
#include "stepper_motor.h"

void setup() {
  // Initialize serial communication for debugging and MAVLink
  Serial.begin(57600);

  // Initialize valve control, pump, stepper motor, and MAVLink communication
  setupValves();
  setupPump();
  setupStepperMotor();
  setupMavlink();

  // Set all valves and pumps to their default state
  default_state();
}

void loop() {
  // Continuously handle MAVLink communication and process incoming messages
  handleMavlinkCommunication();
}
