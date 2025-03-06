#include "water_level_sensor.h"

int get_water_level(int container) {
  int sensorValue = 1000;
  switch(container) {
    case 1:
      sensorValue = analogRead(WL_SENS_1);
      break;
    case 2:
      sensorValue = analogRead(WL_SENS_2);    
      break;
    case 3:
      sensorValue = analogRead(WL_SENS_3);
      break;
    case 4:
      sensorValue = analogRead(WL_SENS_4);
      break;
  }
  Serial.println(sensorValue);
  return sensorValue;
}

void pump_to_container(int container) {
  config_valves(container);
  digitalWrite(PUMP, HIGH);
  unsigned long startTime = millis();
  while (get_water_level(container) <= WL_THRESH) {
    if (millis() - startTime > MAX_PUMP_TIME) {  
      Serial.println("Pump timeout, stopping to prevent overflow.");
      break;
    }
    delay(10);
  }
  digitalWrite(PUMP, LOW);
}
