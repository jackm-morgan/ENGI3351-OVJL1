# OVJL1 USV Water Sampling System

## Overview
This repository contains the code for the **OVJL1 group** as part of **ENGI3351 - L3 Design**. The project involves the development of an **Unmanned Surface Vehicle (USV)** designed for **water sampling**. The USV is equipped with a system that controls valves, pumps, and sensors to collect water samples from different depths and store them in designated containers.

The code is written in **C++** for the **Arduino** platform and is modularized for better organization and maintainability. It integrates **MAVLink communication** for remote control and monitoring, **stepper motor control** for depth adjustment, and **water level sensing** to ensure accurate sampling.

---

## Features
- **Valve Control**: Manages the opening and closing of valves to direct water flow into specific containers.
- **Pump Control**: Activates and deactivates the pump to move water through the system.
- **Water Level Sensing**: Monitors water levels in containers to prevent overflow and ensure proper sampling.
- **Stepper Motor Control**: Adjusts the depth of the sampling mechanism using a stepper motor.
- **MAVLink Communication**: Enables remote control and monitoring of the USV via MAVLink protocol.
- **Modular Code**: The code is split into multiple files for better organization and readability.

---

## Code Structure
The code is organised into the following files:

### 1. **main.ino**
   - The main file that initializes the system and runs the main loop.
   - Handles MAVLink communication and coordinates the sampling process.

### 2. **valve_control.h / valve_control.cpp**
   - Manages the configuration and control of valves and the pump.
   - Includes functions for setting the default state and purging the system.

### 3. **water_level_sensor.h / water_level_sensor.cpp**
   - Handles water level sensing using analog sensors.
   - Includes functions to read water levels and control the pump based on thresholds.

### 4. **stepper_motor.h / stepper_motor.cpp**
   - Controls the stepper motor to adjust the sampling depth.
   - Includes functions for moving the motor up and down.

### 5. **mavlink_communication.h / mavlink_communication.cpp**
   - Handles MAVLink communication for remote control and monitoring.
   - Processes incoming MAVLink messages and executes commands.

### 6. **sample.h / sample.cpp**
   - Coordinates the sampling process, including depth adjustment, purging, and pumping.
   - Ensures that samples are collected and stored correctly.

---

## Hardware Setup
The USV is equipped with the following components:
- **Valves**: Control the flow of water into different containers.
- **Pump**: Moves water through the system.
- **Water Level Sensors**: Monitor the water level in each container.
- **Stepper Motor**: Adjusts the depth of the sampling mechanism.
- **Arduino Microcontroller**: Runs the control code.
- **MAVLink-Compatible Transceiver**: Enables communication with a ground station.

---

## How It Works
1. **Initialization**: The system initializes all components, including valves, pump, sensors, and stepper motor.
2. **MAVLink Communication**: The system listens for MAVLink commands from the ground station.
3. **Sampling Process**:
   - The stepper motor adjusts the sampling mechanism to the desired depth.
   - The system purges any residual water from the previous sample.
   - The pump is activated to fill the designated container with water.
   - Water level sensors ensure that the container does not overflow.
4. **Completion**: Once the sample is collected, the system returns to its default state and waits for the next command.

---

## Usage
1. **Upload the Code**: Upload the code to the Arduino microcontroller.
2. **Connect Hardware**: Ensure all components (valves, pump, sensors, stepper motor, MAVLink transceiver) are properly connected.
3. **Send MAVLink Commands**: Use a MAVLink-compatible ground station to send commands to the USV.
   - Example: Send a command to collect a sample at a specific depth in a specific container.
4. **Monitor Progress**: The system will provide feedback via MAVLink messages, indicating the status of the sampling process.

---

## Dependencies
- **Arduino IDE**: Required to upload and run the code.
- **MAVLink Library**: Used for MAVLink communication.
- **Arduino Standard Libraries**: Used for basic functionality (e.g., `Serial`, `digitalWrite`, `analogRead`).

---

## Contributors
This project was developed by the **OVJL1 group** as part of **Module ENGI3351**. Team members include:
- Arthur Andrewes
- Jack Morgan
- Oliver Munn
- Sebastion Royds
- Sebastian Till
- Benjamin Wass
---

## License
This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---
