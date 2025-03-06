#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <Arduino.h>

#define SM_DIR_PIN 5
#define SM_STEP_PIN 4

void setupStepperMotor();
void spool_down_mm(float depth);

#endif
