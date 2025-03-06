#include "valve_control.h"

void setupValves() {
  pinMode(VALVE_1, OUTPUT);
  pinMode(VALVE_2, OUTPUT);
  pinMode(VALVE_3, OUTPUT);
  pinMode(VALVE_4, OUTPUT);
  pinMode(VALVE_PURGE, OUTPUT);
  pinMode(PUMP, OUTPUT);
}

void config_valves(int container) {
  switch(container) {
    case 1:
      digitalWrite(VALVE_1, HIGH);
      digitalWrite(VALVE_2, LOW); 
      digitalWrite(VALVE_3, LOW); 
      digitalWrite(VALVE_4, LOW); 
      digitalWrite(VALVE_PURGE, LOW);
      break;
    case 2:
      digitalWrite(VALVE_1, LOW);
      digitalWrite(VALVE_2, HIGH); 
      digitalWrite(VALVE_3, LOW); 
      digitalWrite(VALVE_4, LOW); 
      digitalWrite(VALVE_PURGE, LOW);
      break;
    case 3:
      digitalWrite(VALVE_1, LOW);
      digitalWrite(VALVE_2, LOW); 
      digitalWrite(VALVE_3, HIGH); 
      digitalWrite(VALVE_4, LOW);
      digitalWrite(VALVE_PURGE, LOW);  
      break;
    case 4:
      digitalWrite(VALVE_1, LOW);
      digitalWrite(VALVE_2, LOW); 
      digitalWrite(VALVE_3, LOW); 
      digitalWrite(VALVE_4, HIGH); 
      digitalWrite(VALVE_PURGE, LOW); 
      break;     
    default:
      default_state();
  }
}

void default_state() {
  digitalWrite(PUMP, LOW);
  digitalWrite(VALVE_1, LOW);
  digitalWrite(VALVE_2, LOW);
  digitalWrite(VALVE_3, LOW);
  digitalWrite(VALVE_4, LOW);
  digitalWrite(VALVE_PURGE, HIGH); 
}

void purge() {
  default_state();
  digitalWrite(PUMP, HIGH);
  delay(10000); // 10 sec purge
  digitalWrite(PUMP, LOW);
}
