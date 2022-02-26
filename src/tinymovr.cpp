
#include <codec.h>
#include <tinymovr.h>

uint8_t node_id = 1;
uint8_t ep_bits = 6;

uint8_t device_info_ep_id = 3;

void Tinymovr::init(send_callback send_cb, recv_callback recv_cb)
{
    this->_send_cb = send_cb;
    this->_recv_cb = recv_cb;
}

void Tinymovr::device_info(uint32_t *device_id, uint8_t *fw_major,
    uint8_t *fw_minor, uint8_t *fw_patch, uint8_t *temp
) {
    uint32_t can_id = (node_id << ep_bits) | device_info_ep_id | CAN_RTR_FLAG;
    uint8_t dlc = 0;

    this->_send_cb(can_id, this->_data, dlc);
    if (this->_recv_cb(&can_id, this->_data, &dlc)) 
    {
        read_le(device_id, this->_data);
        read_le(fw_major, this->_data + 4);
        read_le(fw_minor, this->_data + 5);
        read_le(fw_patch, this->_data + 6);
        read_le(temp, this->_data + 7);
    }
}