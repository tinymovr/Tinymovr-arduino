/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <stall_detect.hpp>

float Stall_detect_::get_velocity(void)
{
    float value = 0;
    this->send(72, this->_data, 0, true);
    if (this->recv(72, this->_data, &(this->_dlc), this->delay_us_value)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Stall_detect_::set_velocity(float value)
{
    write_le(value, this->_data);
    this->send(72, this->_data, sizeof(float), false);
}

float Stall_detect_::get_delta_pos(void)
{
    float value = 0;
    this->send(73, this->_data, 0, true);
    if (this->recv(73, this->_data, &(this->_dlc), this->delay_us_value)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Stall_detect_::set_delta_pos(float value)
{
    write_le(value, this->_data);
    this->send(73, this->_data, sizeof(float), false);
}

float Stall_detect_::get_t(void)
{
    float value = 0;
    this->send(74, this->_data, 0, true);
    if (this->recv(74, this->_data, &(this->_dlc), this->delay_us_value)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Stall_detect_::set_t(float value)
{
    write_le(value, this->_data);
    this->send(74, this->_data, sizeof(float), false);
}



