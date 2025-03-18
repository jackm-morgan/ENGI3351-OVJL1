#include "water_level_sensor.h"

// Read the water level for a specific container
int get_water_level(int container) {
  int sensorValue = 1000;  // Default value if no sensor is read
  switch(container) {
    case 1:
      sensorValue = analogRead(WL_SENS_1);  // Read sensor for container 1
      break;
    case 2:
      sensorValue = analogRead(WL_SENS_2);  // Read sensor for container 2
      break;
    case 3:
      sensorValue = analogRead(WL_SENS_3);  // Read sensor for container 3
      break;
    case 4:
      sensorValue = analogRead(WL_SENS_4);  // Read sensor for container 4
      break;
  }
  Serial.println(sensorValue);  // Print the sensor value for debugging
  return sensorValue;
}

// Pump water to a specific container until the water level reaches the threshold
void pump_to_container(int container) {
  config_valves(container);  // Configure valves for the target container
  digitalWrite(PUMP, HIGH);  // Turn on the pump
  unsigned long startTime = millis();  // Record the start time

  // Continue pumping until the water level reaches the threshold or the maximum time is reached
  while (get_water_level(container) <= WL_THRESH) {
    if (millis() - startTime > MAX_PUMP_TIME) {  
      Serial.println("Pump timeout, stopping to prevent overflow.");
      break;
    }
    delay(10);  // Small delay to avoid excessive loop speed
  }
  digitalWrite(PUMP, LOW);  // Turn off the pump
}
