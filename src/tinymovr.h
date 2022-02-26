
#pragma once

#include <cstdint>

typedef void (*send_callback)(uint32_t arbitration_id, uint8_t *data, uint8_t dlc);
typedef bool (*recv_callback)(uint32_t *arbitration_id, uint8_t *data, uint8_t *dlc);

class Tinymovr
{
  public:
    void init(send_callback send_cb, recv_callback recv_cb);
    void device_info(
      uint32_t *device_id,
      uint8_t *fw_major,
      uint8_t *fw_minor,
      uint8_t *fw_patch,
      uint8_t *temp
    );
  private:
    send_callback _send_cb;
    recv_callback _recv_cb;
    uint8_t _data[8];
};
