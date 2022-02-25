#include <mcp2515.h>

MCP2515 mcp2515(10);

uint8_t node_id = 1;
uint8_t ep_bits = 6;

uint8_t device_info_ep_id = 3;

template<typename T>
inline size_t read_le(T* value, const uint8_t* buffer);

void setup() {
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  Serial.begin(115200);
}

void loop() {
  // Send/receive a device info message every 1s
  struct can_frame frame;
  frame.can_id = (node_id << ep_bits) | device_info_ep_id | CAN_RTR_FLAG;
  frame.can_dlc = 0;

  mcp2515.sendMessage(&frame);

  if (mcp2515.readMessage(&frame) == MCP2515::ERROR_OK) {
    // frame contains received message
    // the data fields depend on the endpoint retrieved
    // Check out:
    // https://tinymovr.readthedocs.io/en/latest/api/guide.html#api-reference
    uint32_t id;
    uint8_t fw_major;
    uint8_t fw_minor;
    uint8_t fw_patch;
    uint8_t temp;
    read_le(&id, frame.data);
    read_le(&fw_major, frame.data + 4);
    read_le(&fw_minor, frame.data + 5);
    read_le(&fw_patch, frame.data + 6);
    read_le(&temp, frame.data + 7);

    Serial.print("Device ID: ");
    Serial.println(id);
  }

  delay(1000);
}

template<>
inline size_t read_le<uint8_t>(uint8_t* value, const uint8_t* buffer) {
    *value = buffer[0];
    return 1;
}

template<>
inline size_t read_le<uint16_t>(uint16_t* value, const uint8_t* buffer) {
    *value = (static_cast<uint16_t>(buffer[0]) << 0) |
             (static_cast<uint16_t>(buffer[1]) << 8);
    return 2;
}

template<>
inline size_t read_le<int16_t>(int16_t* value, const uint8_t* buffer) {
    *value = (static_cast<int16_t>(buffer[0]) << 0) |
             (static_cast<int16_t>(buffer[1]) << 8);
    return 2;
}

template<>
inline size_t read_le<int32_t>(int32_t* value, const uint8_t* buffer) {
    *value = (static_cast<int32_t>(buffer[0]) << 0) |
             (static_cast<int32_t>(buffer[1]) << 8) |
             (static_cast<int32_t>(buffer[2]) << 16) |
             (static_cast<int32_t>(buffer[3]) << 24);
    return 4;
}

template<>
inline size_t read_le<uint32_t>(uint32_t* value, const uint8_t* buffer) {
    *value = (static_cast<uint32_t>(buffer[0]) << 0) |
             (static_cast<uint32_t>(buffer[1]) << 8) |
             (static_cast<uint32_t>(buffer[2]) << 16) |
             (static_cast<uint32_t>(buffer[3]) << 24);
    return 4;
}

template<>
inline size_t read_le<float>(float* value, const uint8_t* buffer) {
    // static_assert(CHAR_BIT * sizeof(float) == 32, "32 bit floating point expected");
    // static_assert(std::numeric_limits<float>::is_iec559, "IEEE 754 floating point expected");
    return read_le(reinterpret_cast<uint32_t*>(value), buffer);
}
