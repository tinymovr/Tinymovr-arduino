/*
 * This is a minimal example of the Tinymovr-Arduino library
 * functionality, using the MCP2515 adapter to connect to
 * CAN bus. The example allows sending a few basic commands,
 * and supports reading back information every second.
 * 
 * For CAN endpoint reference check out:
 * https://tinymovr.readthedocs.io/en/latest/api/guide.html#api-reference
 */

#include "Arduino.h"
#include <mcp2515.h>
#include <tinymovr.h>

// ---------------------------------------------------------------
// REQUIRED CAN HARDWARE INTERFACE CODE
// ADAPT BELOW TO YOUR CAN ADAPTER HARDWARE

// The hardware interface, in this case
// the MCP2515 chip
MCP2515 mcp2515(10);

// The send_cb and recv_cb functions need to be implemented
// according to the CAN bus hardware you use. Below an example
// usable with MCP2515 type breakouts

/*
 * Function:  send_cb 
 * --------------------
 *  Is called to send a CAN frame
 *
 *  arbitration_id: the frame arbitration id
 *  data: pointer to the data array to be transmitted
 *  data_size: the size of transmitted data
 *  rtr: if the ftame is of request transmit type (RTR)
 */
void send_cb(uint32_t arbitration_id, uint8_t *data, uint8_t data_size, bool rtr)
{
  struct can_frame frame;
  if (rtr)
  {
    frame.can_id = arbitration_id | CAN_RTR_FLAG;
  }
  else
  {
    frame.can_id = arbitration_id;
  }
  
  frame.can_dlc = data_size;
  memcpy(&frame.data, data, frame.can_dlc * sizeof(uint8_t));
  mcp2515.sendMessage(&frame);
}

/*
 * Function:  recv_cb 
 * --------------------
 *  Is called to receive a CAN frame
 *
 *  arbitration_id: the frame arbitration id
 *  data: pointer to the data array to be received
 *  data_size: pointer to the variable that will hold the size of received data
 */
bool recv_cb(uint32_t arbitration_id, uint8_t *data, uint8_t *data_size)
{
  struct can_frame frame;
  if (mcp2515.readMessage(&frame) == MCP2515::ERROR_OK) 
  {
    memcpy(data, &frame.data, frame.can_dlc * sizeof(uint8_t));
    return true;
  }
  return false;
}
// ---------------------------------------------------------------

// ---------------------------------------------------------------
// EXAMPLE CODE
// ADAPT BELOW TO YOUR PROGRAM LOGIC

// The Tinymovr object
Tinymovr tinymovr(1, &send_cb, &recv_cb);

/*
 * Function:  setup 
 * --------------------
 *  Perform hardware initialization
 */
void setup()
{
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

/*
 * Function:  loop 
 * --------------------
 * Program loop. 
 * Listen for commands coming from serial and
 * transmit to Tinymovr.
 */
void loop() 
{
  if (Serial.available() > 0) {
    uint8_t receivedChar = Serial.read();
    if (receivedChar == 'Q')
    {
      Serial.println("Received Calibration command");
      tinymovr.set_state(1, 0);
    }
    else if (receivedChar == 'A')
    {
      Serial.println("Received Closed Loop command");
      tinymovr.set_state(2, 2);
    }
    else if (receivedChar == 'Z')
    {
      Serial.println("Received Idle command");
      tinymovr.set_state(0, 0);
    }
    else if (receivedChar == 'R')
    {
      Serial.println("Received reset command");
      tinymovr.reset();
    }
    else if (receivedChar == '<')
    {
      Serial.println("Received L turn command");
      float pos_estimate;
      float vel_estimate;
      tinymovr.get_encoder_estimates(&pos_estimate, &vel_estimate);
      Serial.println(pos_estimate);
      tinymovr.set_pos_setpoint(pos_estimate - 8192.0f, 0, 0);
    }
    else if (receivedChar == '>')
    {
      Serial.println("Received R turn command");
      float pos_estimate;
      float vel_estimate;
      tinymovr.get_encoder_estimates(&pos_estimate, &vel_estimate);
      Serial.println(pos_estimate);
      tinymovr.set_pos_setpoint(pos_estimate + 8192.0f, 0, 0);
    }
    else if (receivedChar == 'I')
    {
      // Print board information
      uint32_t id;
      uint8_t fw_major;
      uint8_t fw_minor;
      uint8_t fw_patch;
      uint8_t temp;
      uint8_t state;
      uint8_t mode;
      tinymovr.device_info(&id, &fw_major, &fw_minor, &fw_patch, &temp);
      tinymovr.get_state(&state, &mode);
      Serial.print("Device ID: ");
      Serial.print(id);
      Serial.print(", Firmware version: ");
      Serial.print(fw_major);
      Serial.print(".");
      Serial.print(fw_minor);
      Serial.print(".");
      Serial.print(fw_patch);
      Serial.print(", Temp:");
      Serial.print(temp);
      Serial.print(", State:");
      Serial.print(state);
      Serial.print(", Mode:");
      Serial.print(mode);
      Serial.print("\n");

      float pos_estimate;
      float vel_estimate;
      tinymovr.get_encoder_estimates(&pos_estimate, &vel_estimate);
      Serial.print("Position estimate: ");
      Serial.print(pos_estimate);
      Serial.print(", Velocity estimate: ");
      Serial.print(vel_estimate);
      Serial.print("\n");

      float Iq_setpoint;
      float Iq_estimate;
      tinymovr.get_Iq_set_est(&Iq_setpoint, &Iq_estimate);
      Serial.print("Iq estimate: ");
      Serial.print(Iq_estimate);
      Serial.print(", Iq setpoint: ");
      Serial.print(Iq_setpoint);
      Serial.print("\n");
      Serial.println("---");
    }
  }
  delay(50);
}
// ---------------------------------------------------------------
