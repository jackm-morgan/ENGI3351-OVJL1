#include "valve_control.h"

// Initialize valve and pump pins as outputs
void setupValves() {
  pinMode(VALVE_1, OUTPUT);
  pinMode(VALVE_2, OUTPUT);
  pinMode(VALVE_3, OUTPUT);
  pinMode(VALVE_4, OUTPUT);
  pinMode(VALVE_PURGE, OUTPUT);
  pinMode(PUMP, OUTPUT);
}

// Configure valves for a specific container
void config_valves(int container) {
  switch(container) {
    case 1:
      digitalWrite(VALVE_1, HIGH);  // Open valve for container 1
      digitalWrite(VALVE_2, LOW); 
      digitalWrite(VALVE_3, LOW); 
      digitalWrite(VALVE_4, LOW); 
      digitalWrite(VALVE_PURGE, LOW);
      break;
    case 2:
      digitalWrite(VALVE_1, LOW);
      digitalWrite(VALVE_2, HIGH);  // Open valve for container 2
      digitalWrite(VALVE_3, LOW); 
      digitalWrite(VALVE_4, LOW); 
      digitalWrite(VALVE_PURGE, LOW);
      break;
    case 3:
      digitalWrite(VALVE_1, LOW);
      digitalWrite(VALVE_2, LOW); 
      digitalWrite(VALVE_3, HIGH);  // Open valve for container 3
      digitalWrite(VALVE_4, LOW);
      digitalWrite(VALVE_PURGE, LOW);  
      break;
    case 4:
      digitalWrite(VALVE_1, LOW);
      digitalWrite(VALVE_2, LOW); 
      digitalWrite(VALVE_3, LOW); 
      digitalWrite(VALVE_4, HIGH);  // Open valve for container 4
      digitalWrite(VALVE_PURGE, LOW); 
      break;     
    default:
      default_state();  // If an invalid container is selected, revert to default state
  }
}

// Set all valves and pump to their default state (purge state)
void default_state() {
  digitalWrite(PUMP, LOW);         // Turn off the pump
  digitalWrite(VALVE_1, LOW);      // Close all container valves
  digitalWrite(VALVE_2, LOW);
  digitalWrite(VALVE_3, LOW);
  digitalWrite(VALVE_4, LOW);
  digitalWrite(VALVE_PURGE, HIGH); // Open the purge valve
}

// Perform a purge operation to clear the system
void purge() {
  default_state();              // Set valves and pump to default state
  digitalWrite(PUMP, HIGH);     // Turn on the pump
  delay(10000);                 // Run the pump for 10 seconds
  digitalWrite(PUMP, LOW);      // Turn off the pump
}
