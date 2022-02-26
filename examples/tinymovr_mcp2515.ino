
#include "Arduino.h"
#include <mcp2515.h>
#include <tinymovr.h>

MCP2515 mcp2515(10);
Tinymovr tinymovr;

// The send_cb and recv_cb functions need to be implemented
// according to the CAN bus hardware you use. Below an example
// usable with MCP2515 type breakouts
void send_cb(uint32_t arbitration_id, uint8_t *data, uint8_t data_size)
{
  struct can_frame frame;
  frame.can_id = arbitration_id;
  frame.can_dlc = 0;
  mcp2515.sendMessage(&frame);
}

bool recv_cb(uint8_t *data, uint8_t *data_size)
{
  struct can_frame frame;
  if (mcp2515.readMessage(&frame) == MCP2515::ERROR_OK) 
  {
    memcpy(data, &frame.data, frame.dlc * sizeof(uint8_t));
    return true;
  }
  return false;
}

// Perform hardware initialization at setup()
void setup()
{
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  Tinymovr.init(&send_cb, &recv_cb);
}

// Request a CAN endpoint and print it via serial
// Repeat every second
void loop() {
  uint32_t id;
  uint8_t fw_major;
  uint8_t fw_minor;
  uint8_t fw_patch;
  uint8_t temp;
  // frame contains received message
  // the data fields depend on the endpoint retrieved
  // Check out:
  // https://tinymovr.readthedocs.io/en/latest/api/guide.html#api-reference
  Tinymovr.device_info(&id, &fw_major, &fw_minor, &fw_patch, &temp);
  Serial.printf("ID: %d\n", id);
  delay(1000);
}

