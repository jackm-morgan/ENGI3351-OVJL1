#include <mavlink.h>
//#include <SoftwareSerial.h>

// Define SoftwareSerial pins for Pixhawk communication
//SoftwareSerial pixhawkSerial(10, 11); // RX (Arduino) -> TX (Pixhawk), TX (Arduino) -> RX (Pixhawk)

#define VALVE_1 6
#define VALVE_2 10
#define VALVE_3 8 
#define VALVE_4 11
#define VALVE_PURGE 7
#define PUMP 9
#define SM_DIR_PIN 5
#define SM_STEP_PIN 4
const int WL_SENS_1 = A5;
const int WL_SENS_2 = A4;
const int WL_SENS_3 = A3;
const int WL_SENS_4 = A2;
const int WL_THRESH = 200; // 680 good
const int MAX_PUMP_TIME = 10000; // 15 secs. 10 SECS = 640 on WL sensor
const int PURGE_TIME = 10000; // 10 secs
int CONTAINER_COUNTER = 1;

void purge(){
  default_state();
  digitalWrite(PUMP, HIGH);
  delay(PURGE_TIME); // 10 sec purge
  digitalWrite(PUMP, LOW);
}


void config_valves(int container){
  switch(container){
    case 1:
      digitalWrite(VALVE_1, HIGH);
      digitalWrite(VALVE_2, LOW); 
      digitalWrite(VALVE_3, LOW); 
      digitalWrite(VALVE_4, LOW); 
      digitalWrite(VALVE_PURGE, LOW);
      break;
    case 2:
      digitalWrite(VALVE_2, LOW);
      digitalWrite(VALVE_2, HIGH); 
      digitalWrite(VALVE_3, LOW); 
      digitalWrite(VALVE_4, LOW); 
      digitalWrite(VALVE_PURGE, LOW);
      break;
    case 3:
      digitalWrite(VALVE_2, LOW);
      digitalWrite(VALVE_2, LOW); 
      digitalWrite(VALVE_3, HIGH); 
      digitalWrite(VALVE_4, LOW);
      digitalWrite(VALVE_PURGE, LOW);  
      break;
    case 4:
      digitalWrite(VALVE_2, LOW);
      digitalWrite(VALVE_2, LOW); 
      digitalWrite(VALVE_3, LOW); 
      digitalWrite(VALVE_4, HIGH); 
      digitalWrite(VALVE_PURGE, LOW); 
      break;     
    default:
      // ERROR
      default_state();
  }
}


int get_water_level(int container){
  int sensorValue = 1000;
  switch(container){
    case 1:
      sensorValue = analogRead(WL_SENS_1);
    case 2:
      sensorValue = analogRead(WL_SENS_2);    
    case 3:
      sensorValue = analogRead(WL_SENS_3);
    case 4:
      sensorValue = analogRead(WL_SENS_4);

  }
  Serial.println(sensorValue);
  return sensorValue;
}


void pump_to_container(int container){
  config_valves(container);
  digitalWrite(PUMP, HIGH);
  unsigned long startTime = millis();
  while (get_water_level(container) <= WL_THRESH){
    if (millis() - startTime > MAX_PUMP_TIME) {  
      Serial.println("Pump timeout, stopping to prevent overflow.");
      break;
    }
    delay(10);
  }
  digitalWrite(PUMP, LOW);
}


void spool_down_mm(float depth){ //800 IS MAX
  // 360Deg approx 125mm
  // negative rotation up, positive down
  float deg_depth_factor = 3.1218781219;
  float deg = depth * deg_depth_factor;
  int dir = (deg > 0)? HIGH:LOW;
  float speed = 0.05;
  digitalWrite(SM_DIR_PIN,dir); 
 
  int steps = abs(deg)*(4.5);
  float usDelay = (1/speed) * 60;
 
  for(int i=0; i < steps; i++){ 
    digitalWrite(SM_STEP_PIN, HIGH); 
    delayMicroseconds(usDelay); 
 
    digitalWrite(SM_STEP_PIN, LOW); 
    delayMicroseconds(usDelay); 
  }
} 


void sample(int container, int depth){
  default_state();
  spool_down_mm(depth);
  purge();
  pump_to_container(container);
  default_state();
  spool_down_mm(-depth);
  Serial.print("Sampling Complete in Container [");
  Serial.print(container);
  Serial.println("]");
}


void default_state(){
  // default state (Purge state)
  // all pumps closed, bar purge valve, pump off/
  digitalWrite(PUMP, LOW);
  digitalWrite(VALVE_1, LOW);
  digitalWrite(VALVE_2, LOW);
  digitalWrite(VALVE_4, LOW);
  digitalWrite(VALVE_PURGE, HIGH); 
}

void setup() {
Serial.begin(57600);
//Serial.println("Arduino ready to receive GPS data from Pixhawk");
//pixhawkSerial.begin(57600);
  pinMode(VALVE_1, OUTPUT);
  pinMode(VALVE_2, OUTPUT);
  pinMode(VALVE_3, OUTPUT);
  pinMode(VALVE_4, OUTPUT);
  pinMode(VALVE_PURGE, OUTPUT);
  pinMode(PUMP, OUTPUT);
  pinMode(SM_DIR_PIN, OUTPUT); 
  pinMode(SM_STEP_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  default_state();
delay(1000);
}



void loop() {


// MAVLink
  /* The default UART header for your MCU */ 
  int sysid = 1;                   ///< ID 20 for this airplane. 1 PX, 255 ground station
  int compid = 158;                ///< The component sending the message
  int type = MAV_TYPE_QUADROTOR;   ///< This system is an airplane / fixed wing
 
  // Define the system type, in this case an airplane -> on-board controller
  // uint8_t system_type = MAV_TYPE_FIXED_WING;
  uint8_t system_type = MAV_TYPE_GENERIC;
  uint8_t autopilot_type = MAV_AUTOPILOT_INVALID;
 
  uint8_t system_mode = MAV_MODE_PREFLIGHT; ///< Booting up
  uint32_t custom_mode = 0;                 ///< Custom mode, can be defined by user/adopter
  uint8_t system_state = MAV_STATE_STANDBY; ///< System ready for flight
  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  mavlink_status_t status;
 
  // Pack the message
  //mavlink_msg_heartbeat_pack(sysid,compid, &msg, type, autopilot_type, system_mode, custom_mode, system_state);
  mavlink_msg_heartbeat_pack(1,0, &msg, type, autopilot_type, system_mode, custom_mode, system_state);
 
  // Copy the message to the send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
 
Serial.write(buf, len);

  const int  maxStreams = 2;
  const uint8_t MAVStreams[maxStreams] = {MAV_DATA_STREAM_EXTENDED_STATUS, MAV_DATA_STREAM_RC_CHANNELS};
  const uint16_t MAVRates[maxStreams] = {0x00,0x0F};

    
  for (int i=0; i < maxStreams; i++) {
    mavlink_msg_request_data_stream_pack(2, 200, &msg, 1, 0, MAVStreams[i], MAVRates[i], 1);
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);


   Serial.write(buf, len);

  }

while (Serial.available() > 0) {
uint8_t c = Serial.read();

//debugging
   //Serial.print("Received byte: ");
   //Serial.println(c, HEX);  // Print each byte in hex format

if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {
  //Serial.println("mavlink_parse_char returned TRUE: A complete message was parsed.");

switch (msg.msgid) {
        case MAVLINK_MSG_ID_HEARTBEAT:
          //Serial.println("HEARTBEAT!!!!!!!!");
          break;
        case MAVLINK_MSG_ID_SYS_STATUS:
          //Serial.println("SYS_STATUS");
          break;
        case MAVLINK_MSG_ID_GPS_RAW_INT:
          //Serial.println("GPS_RAW_INT");
          break;
        case MAVLINK_MSG_ID_ATTITUDE:
          //Serial.println("ATTITUDE");
          break;
        case MAVLINK_MSG_ID_COMMAND_LONG:
          //Serial.println("COMMAND_LONG");
          break;
        case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
          //Serial.println("GLOBAL POS");
          break;
        case MAVLINK_MSG_ID_VFR_HUD:
          //Serial.println("VFR_HUD");
          break; 
          case MAVLINK_MSG_ID_MISSION_CURRENT:
          //Serial.println("CURRENT TARGET");
          break;
          case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:
          //Serial.println("SERVO OP");
          //Serial.println(msg.msgid);
          break;
          case MAVLINK_MSG_ID_STATUSTEXT:
          //Serial.println("STATUSTEXT");
          break;       
          case MAVLINK_MSG_ID_PARAM_VALUE:
          //Serial.println("PARAMID");
          break;  
          case MAVLINK_MSG_ID_RC_CHANNELS_RAW:
          //Serial.println("RC!");
          // Declare a structure to hold the decoded message data
    mavlink_rc_channels_raw_t rc_channels_raw;

    // Decode the message into the structure
    mavlink_msg_rc_channels_raw_decode(&msg, &rc_channels_raw);

    // Access the raw values of the RC channels
    uint16_t chan1_raw = rc_channels_raw.chan1_raw; // Throttle
    uint16_t chan2_raw = rc_channels_raw.chan2_raw; // Roll
    uint16_t chan3_raw = rc_channels_raw.chan3_raw; // Pitch
    uint16_t chan4_raw = rc_channels_raw.chan4_raw; // Yaw
    uint16_t chan5_raw = rc_channels_raw.chan5_raw; // Auxiliary 1
    uint16_t chan6_raw = rc_channels_raw.chan6_raw; // Auxiliary 2
    uint16_t chan7_raw = rc_channels_raw.chan7_raw; // Auxiliary 3
    uint16_t chan8_raw = rc_channels_raw.chan8_raw; // Auxiliary 4
    uint8_t rssi = rc_channels_raw.rssi;            // RSSI


    //uint8_t channel_count = rc_channels_raw.channel_count;

    uint16_t rc6 = rc_channels_raw.chan6_raw;
    uint16_t rc7 = rc_channels_raw.chan7_raw;
    uint16_t rc8 = rc_channels_raw.chan8_raw;
    if (rc6 == 1880){
      CONTAINER_COUNTER = 1;
    }
    if (rc7 == 2000){
      // MAKE A PURGE SWITCH
      if (CONTAINER_COUNTER <= 4){
        digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
        delay(500);                      // wait for a second
        digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
        delay(500);                      // wait for a second
      //Serial.println("2000 registered \n");
      //Serial.println(rc8);
      float depth = ((float)rc8-1000)*0.8; // depth in mm to sample
      //Serial.println(depth);
      //sample(CONTAINER_COUNTER, depth); // container, depth
      //Serial.println("Taking Sample");
      //delay(5000);
      //Serial.print("Sample Taken at depth ");
      //Serial.print(depth);
      //Serial.print(" In container ");
      //Serial.println(CONTAINER_COUNTER);
      sample(CONTAINER_COUNTER, depth);
      CONTAINER_COUNTER = CONTAINER_COUNTER + 1;
      }
      else{
      //Serial.println("Max Samples Taken.");
      }

    }
          break; 
        default:
          //Serial.println(msg.msgid);
          break;
      }
}  
}
}
