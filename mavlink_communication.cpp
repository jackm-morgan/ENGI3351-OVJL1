#include "mavlink_communication.h"

int CONTAINER_COUNTER = 1;  // Counter to track the current container

// Initialize MAVLink communication
void setupMavlink() {
  // Initialization code for MAVLink communication (if needed)
}

// Handle incoming MAVLink messages
void handleMavlinkCommunication() {
  mavlink_message_t msg;
  mavlink_status_t status;

  // Process incoming serial data
  while (Serial.available() > 0) {
    uint8_t c = Serial.read();

    // Parse the incoming MAVLink message
    if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {
      switch (msg.msgid) {
        case MAVLINK_MSG_ID_RC_CHANNELS_RAW:
          // Decode the RC channels raw message
          mavlink_rc_channels_raw_t rc_channels_raw;
          mavlink_msg_rc_channels_raw_decode(&msg, &rc_channels_raw);

          // Extract RC channel values
          uint16_t rc6 = rc_channels_raw.chan6_raw;
          uint16_t rc7 = rc_channels_raw.chan7_raw;
          uint16_t rc8 = rc_channels_raw.chan8_raw;

          // Check if the RC6 channel is set to 1880 (container selection)
          if (rc6 == 1880) {
            CONTAINER_COUNTER = 1;  // Reset container counter
          }

          // Check if the RC7 channel is set to 2000 (trigger sampling)
          if (rc7 == 2000) {
            if (CONTAINER_COUNTER <= 4) {
              // Calculate the sampling depth based on RC8 channel
              float depth = ((float)rc8 - 1000) * 0.8;
              sample(CONTAINER_COUNTER, depth);  // Perform sampling
              CONTAINER_COUNTER++;              // Move to the next container
            }
          }
          break;
        default:
          break;
      }
    }
  }
}
