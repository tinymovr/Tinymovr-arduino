/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <device.hpp>

uint32_t Device::get_protocol_hash(void)
{
    uint32_t value = 0;
    this->send(0, this->_data, 0, true);
    if (this->recv(0, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

uint32_t Device::get_uid(void)
{
    uint32_t value = 0;
    this->send(1, this->_data, 0, true);
    if (this->recv(1, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Device::get_Vbus(void)
{
    float value = 0;
    this->send(2, this->_data, 0, true);
    if (this->recv(2, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Device::get_Ibus(void)
{
    float value = 0;
    this->send(3, this->_data, 0, true);
    if (this->recv(3, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Device::get_power(void)
{
    float value = 0;
    this->send(4, this->_data, 0, true);
    if (this->recv(4, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Device::get_temp(void)
{
    float value = 0;
    this->send(5, this->_data, 0, true);
    if (this->recv(5, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

bool Device::get_calibrated(void)
{
    bool value = 0;
    this->send(6, this->_data, 0, true);
    if (this->recv(6, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

uint8_t Device::get_errors(void)
{
    uint8_t value = 0;
    this->send(7, this->_data, 0, true);
    if (this->recv(7, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Device::save_config()
{
    this->send(8, this->_data, 0, true);
}

void Device::erase_config()
{
    this->send(9, this->_data, 0, true);
}

void Device::reset()
{
    this->send(10, this->_data, 0, true);
}



