#include "sample.h"
#include "valve_control.h"
#include "stepper_motor.h"
#include "water_level_sensor.h"

void sample(int container, int depth) {
  default_state();
  spool_down_mm(depth);
  purge();
  pump_to_container(container);
  default_state();
  spool_down_mm(-depth);
  Serial.print("Sampling Complete in Container [");
  Serial.print(container);
  Serial.println("]");
}
