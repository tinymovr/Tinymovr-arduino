/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <can.hpp>

uint32_t can::get_rate(void)
{
    uint32_t value = 0;
    this->send(41, this->_data, 0, true);
    if (this->recv(41, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void can::set_rate(uint32_t value)
{
    write_le(this->_data, value);
    this->send(41, this->_data, sizeof(uint32_t), false);
}

uint32_t can::get_id(void)
{
    uint32_t value = 0;
    this->send(42, this->_data, 0, true);
    if (this->recv(42, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void can::set_id(uint32_t value)
{
    write_le(this->_data, value);
    this->send(42, this->_data, sizeof(uint32_t), false);
}



