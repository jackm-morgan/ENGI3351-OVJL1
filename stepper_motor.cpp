#include "stepper_motor.h"

void setupStepperMotor() {
  pinMode(SM_DIR_PIN, OUTPUT); 
  pinMode(SM_STEP_PIN, OUTPUT);
}

void spool_down_mm(float depth) {
  float deg_depth_factor = 3.1218781219;
  float deg = depth * deg_depth_factor;
  int dir = (deg > 0)? HIGH:LOW;
  float speed = 0.05;
  digitalWrite(SM_DIR_PIN, dir); 
 
  int steps = abs(deg) * 4.5;
  float usDelay = (1 / speed) * 60;
 
  for(int i = 0; i < steps; i++) { 
    digitalWrite(SM_STEP_PIN, HIGH); 
    delayMicroseconds(usDelay); 
    digitalWrite(SM_STEP_PIN, LOW); 
    delayMicroseconds(usDelay); 
  }
}
