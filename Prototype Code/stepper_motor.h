#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <Arduino.h>

// Define pin numbers for stepper motor control
#define SM_DIR_PIN 5
#define SM_STEP_PIN 4

// Function prototypes
void setupStepperMotor();          // Initialize stepper motor pins
void spool_down_mm(float depth);   // Move the stepper down motor by a specified depth
void spool_down_mm(float depth);   // Move the stepper up motor by a specified depth

#endif
