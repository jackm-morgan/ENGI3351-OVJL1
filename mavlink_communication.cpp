#include "mavlink_communication.h"

int container_counter = 1;

void setupMavlink() {
  // Initialization code for MAVLink communication
}

void handleMavlinkCommunication() {
  mavlink_message_t msg;
  mavlink_status_t status;

  while (Serial.available() > 0) {
    uint8_t c = Serial.read();

    if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {
      switch (msg.msgid) {
        case MAVLINK_MSG_ID_RC_CHANNELS_RAW:
          mavlink_rc_channels_raw_t rc_channels_raw;
          mavlink_msg_rc_channels_raw_decode(&msg, &rc_channels_raw);

          uint16_t rc6 = rc_channels_raw.chan6_raw;
          uint16_t rc7 = rc_channels_raw.chan7_raw;
          uint16_t rc8 = rc_channels_raw.chan8_raw;

          if (rc6 == 1880) {
            container_counter = 1;
          }
          if (rc7 == 2000) {
            if (container_counter <= 4) {
              float depth = ((float)rc8 - 1000) * 0.8;
              sample(container_counter, depth);
              container_counter++;
            }
          }
          break;
        default:
          break;
      }
    }
  }
}
