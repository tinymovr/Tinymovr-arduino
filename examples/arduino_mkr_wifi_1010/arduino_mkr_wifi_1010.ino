/*
 * This is a minimal example of the Tinymovr-Arduino library
 * functionality, using the Arduino MKR1010 with the Arduino
 * MKR CAN Bus Shield to connect to CAN bus. The example allows
 * sending a few basic commands, and supports reading back 
 * information.
 * 
 * For CAN endpoint reference check out:
 * https://tinymovr.readthedocs.io/en/latest/api/guide.html#api-reference
 */

/* !!! USE ONLY THE "CAN Adafruit Fork Library"             !!!
   !!! IT IS THE ONLY ONE WITH PROPER FILTER IMPLEMENTATION !!! */

#include "Arduino.h"
#include <CAN.h>  // "CAN Adafruit Fork" library
#include <tinymovr.hpp>

// ---------------------------------------------------------------
// REQUIRED CAN HARDWARE INTERFACE CODE
// ADAPT BELOW TO YOUR CAN ADAPTER HARDWARE

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
 *  rtr: if the frame is of request transmit type (RTR)
 */
void send_cb(uint32_t arbitration_id, uint8_t *data, uint8_t data_size, bool rtr)
{
  CAN.beginExtendedPacket(arbitration_id, data_size, rtr);
  for (int i=0; i<data_size; i++)
  {
    CAN.write(data[i]);
  }
  CAN.endPacket();
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
bool recv_cb(uint32_t *arbitration_id, uint8_t *data, uint8_t *data_size)
{
  int packetSize = CAN.parsePacket();
  if (packetSize > 0) {
    *data_size = packetSize;
    for (int i = 0; i < packetSize; i++) {
      int r = CAN.read();
      if (r == -1) return false;
      data[i] = (uint8_t)r;
    }
    *arbitration_id = CAN.packetId();
    return true;
  }
  return false;
}

/*
 * Function:  delay_us_cb 
 * --------------------
 *  Is called to perform a delay
 *
 *  us: the microseconds to wait for
 */
void delay_us_cb(uint32_t us)
{
  delayMicroseconds(us);
}
// ---------------------------------------------------------------

// ---------------------------------------------------------------
// EXAMPLE CODE
// ADAPT BELOW TO YOUR PROGRAM LOGIC

// The Tinymovr object
Tinymovr tinymovr(1, &send_cb, &recv_cb, &delay_us_cb, 100);

/*
 * Function:  setup 
 * --------------------
 *  Perform hardware initialization
 */
void setup()
{
  Serial.begin(115200);
  while (!Serial);

  // start the CAN bus at 1Mbps
  if (!CAN.begin(1000E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  // NOTE: You NEED to enable filtering using this pattern,
  // otherwise the library will not function correctly,
  // especially with a lot of Tinymovr units on the bus
  if (!CAN.filterExtended(0x0, 0x700))
  {
    Serial.println("Setting CAN filters failed!");
    while (1);
  }
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
      tinymovr.controller.set_state(1);
    }
    else if (receivedChar == 'A')
    {
      Serial.println("Received Closed Loop command");
      tinymovr.controller.set_state(2);
      tinymovr.controller.set_mode(2);
    }
    else if (receivedChar == 'Z')
    {
      Serial.println("Received Idle command");
      tinymovr.controller.set_state(0);
    }
    else if (receivedChar == 'R')
    {
      Serial.println("Received reset command");
      tinymovr.reset();
    }
    else if (receivedChar == '<')
    {
      Serial.println("Received L turn command");
      float pos_estimate = tinymovr.encoder.get_position_estimate();
      Serial.println(pos_estimate);
      tinymovr.controller.position.set_setpoint(pos_estimate - 8192.0f);
    }
    else if (receivedChar == '>')
    {
      Serial.println("Received R turn command");
      float pos_estimate = tinymovr.encoder.get_position_estimate();
      Serial.println(pos_estimate);
      tinymovr.controller.position.set_setpoint(pos_estimate + 8192.0f);
    }
    else if (receivedChar == 'I')
    {
      // Print board information
      Serial.print("Device ID: ");
      Serial.print(tinymovr.comms.can.get_id());
      Serial.print(", Temp:");
      Serial.print(tinymovr.get_temp());
      Serial.print(", State:");
      Serial.print(tinymovr.controller.get_state());
      Serial.print(", Mode:");
      Serial.print(tinymovr.controller.get_mode());
      Serial.print("\n");
      Serial.print("Position estimate: ");
      Serial.print(tinymovr.encoder.get_position_estimate());
      Serial.print(", Velocity estimate: ");
      Serial.print(tinymovr.encoder.get_velocity_estimate());
      Serial.print("\n");
      Serial.print("Iq estimate: ");
      Serial.print(tinymovr.controller.current.get_Iq_estimate());
      Serial.print(", Iq setpoint: ");
      Serial.print(tinymovr.controller.current.get_Iq_setpoint());
      Serial.print("\n");
      Serial.println("---");
    }
  }
  delay(50);
}
// ---------------------------------------------------------------
