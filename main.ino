#include "valve_control.h"
#include "water_level_sensor.h"
#include "mavlink_communication.h"
#include "stepper_motor.h"

void setup() {
  Serial.begin(57600);
  setupValves();
  setupPump();
  setupStepperMotor();
  setupMavlink();
  default_state();
}

void loop() {
  handleMavlinkCommunication();
}
