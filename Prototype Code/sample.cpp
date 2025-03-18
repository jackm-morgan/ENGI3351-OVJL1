#include "sample.h"
#include "valve_control.h"
#include "stepper_motor.h"
#include "water_level_sensor.h"

// Perform sampling for a specific container and depth
void sample(int container, int depth) {
  default_state();          // Set valves and pump to default state
  spool_down_mm(depth);     // Lower the sampling mechanism
  purge();                  // Perform a purge operation
  pump_to_container(container);  // Pump water to the target container
  default_state();          // Set valves and pump to default state
  spool_up_mm(depth);       // Raise the sampling mechanism
}
