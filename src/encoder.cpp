/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <encoder.hpp>

float encoder::get_position_estimate(void)
{
    float value = 0;
    this->send(52, this->_data, 0, true);
    if (this->recv(52, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

float encoder::get_velocity_estimate(void)
{
    float value = 0;
    this->send(53, this->_data, 0, true);
    if (this->recv(53, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

uint8_t encoder::get_type(void)
{
    uint8_t value = 0;
    this->send(54, this->_data, 0, true);
    if (this->recv(54, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void encoder::set_type(uint8_t value)
{
    write_le(this->_data, value);
    this->send(54, this->_data, sizeof(uint8_t), false);
}

float encoder::get_bandwidth(void)
{
    float value = 0;
    this->send(55, this->_data, 0, true);
    if (this->recv(55, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void encoder::set_bandwidth(float value)
{
    write_le(this->_data, value);
    this->send(55, this->_data, sizeof(float), false);
}

bool encoder::get_calibrated(void)
{
    bool value = 0;
    this->send(56, this->_data, 0, true);
    if (this->recv(56, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

uint8_t encoder::get_errors(void)
{
    uint8_t value = 0;
    this->send(57, this->_data, 0, true);
    if (this->recv(57, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}


