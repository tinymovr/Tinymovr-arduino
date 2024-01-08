/*
 * This is a minimal example of the Tinymovr-Arduino library
 * functionality, using the ESP32 with MCP2551 to connect to
 * CAN bus. The example allows sending a few basic commands,
 * and supports reading back information.
 * 
 * For CAN endpoint reference check out:
 * https://tinymovr.readthedocs.io/en/latest/api/guide.html#api-reference
 */

#include "driver/gpio.h"
#include "driver/twai.h"
#include <tinymovr.hpp>

// ---------------------------------------------------------------
// REQUIRED CAN HARDWARE INTERFACE CODE
// ADAPT BELOW TO YOUR CAN ADAPTER HARDWARE

// The send_cb and recv_cb functions need to be implemented
// according to the CAN bus hardware you use. Below an example
// usable with the ESP32 TWAI peripheral

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
  twai_message_t message;
  message.identifier = arbitration_id;
  message.extd = 1;
  message.rtr = rtr;
  message.data_length_code = data_size;

  for (int i = 0; i < data_size; i++) {
    message.data[i] = data[i];
  }
  esp_err_t err = twai_transmit(&message, pdMS_TO_TICKS(200));
  if (err != ESP_OK) {
    Serial.println("Failed to queue message for transmission");
  }
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
  twai_message_t message;
  while (twai_receive(&message, pdMS_TO_TICKS(200)) == ESP_OK) {
    if ((message.identifier <= 1790 || message.identifier >= 1950) && message.rtr == false) {
      *data_size = message.data_length_code;
      *arbitration_id = message.identifier;

      for (int i = 0; i < message.data_length_code; i++) {
        data[i] = message.data[i];
      }
      return true;
    }
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
  ets_delay_us(us);
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
  
  // TWAI General Configuration
  twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(CAN_TX_PIN, CAN_RX_PIN, TWAI_MODE_NORMAL);
  g_config.clkout_io = TWAI_IO_UNUSED;   // If no clock output is required
  g_config.bus_off_io = TWAI_IO_UNUSED;  // If no bus-off notification is required
  g_config.tx_queue_len = 50;            // Length of TX queue (adjust as needed)
  g_config.rx_queue_len = 50;            // Length of RX queue (adjust as needed)

  // TWAI Timing Configuration (assuming 1Mbps)
  twai_timing_config_t t_config = TWAI_TIMING_CONFIG_1MBITS();

  // We have not been able so far to properly set the TWAI filter
  // configuration to that needed by Tinymovr. Thankfully, the ESP32
  // supports a large RX queue, which enables filtering in software.
  // Although sub-optimal, it works well.

  // TWAI Filter Configuration
  // twai_filter_config_t f_config = {
  //     .acceptance_code = 0x0,
  //     .acceptance_mask = 0x0,
  //     .single_filter = true
  // };
  // Accept all for now
  twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

  //Install TWAI driver
  if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK)
  {
    Serial.println("Failed to install TWAI driver");
    while (1);
  }

  //Start TWAI driver
  esp_err_t err = twai_start();
  if (err != ESP_OK)
  {
    Serial.println("Failed to start TWAI driver");
    while (1);
  }

  // As a final step check that the hash returned by the node
  // is the same as the hash stored by the Tinymovr library.
  // This is crucial to prevent potential mismatches in commands.
  if (tinymovr.get_protocol_hash() != avlos_proto_hash)
  {
    Serial.println("Wrong device spec!");
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
