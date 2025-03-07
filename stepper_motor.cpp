#include "stepper_motor.h"

// Initialize stepper motor pins as outputs
void setupStepperMotor() {
  pinMode(SM_DIR_PIN, OUTPUT); 
  pinMode(SM_STEP_PIN, OUTPUT);
}

// Move the stepper down motor by a specified depth (in millimeters)
void spool_down_mm(float depth) {
  float deg_depth_factor = 3.1218781219;  // Conversion factor from mm to degrees
  float deg = depth * deg_depth_factor;   // Convert depth to degrees
  int dir = (deg > 0)? HIGH:LOW;         // Set direction based on depth
  float speed = 0.05;                    // Speed of the stepper motor
  digitalWrite(SM_DIR_PIN, dir);         // Set the direction pin

  int steps = abs(deg) * 4.5;            // Convert degrees to steps
  float usDelay = (1 / speed) * 60;      // Calculate delay between steps

  // Step the motor
  for(int i = 0; i < steps; i++) { 
    digitalWrite(SM_STEP_PIN, HIGH); 
    delayMicroseconds(usDelay); 
    digitalWrite(SM_STEP_PIN, LOW); 
    delayMicroseconds(usDelay); 
  }
}

// Move stepper motor up by a specified depth (in millimeters)
void spool_up_mm(float depth){
  spool_down_mm(-depth);                // Spool down with negative depth
}
