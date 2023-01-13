/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <velocity.hpp>

float velocity::get_setpoint(void)
{
    float value = 0;
    this->send(20, this->_data, 0, true);
    if (this->recv(20, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void velocity::set_setpoint(float value)
{
    write_le(this->_data, value);
    this->send(20, this->_data, sizeof(float), false);
}

float velocity::get_limit(void)
{
    float value = 0;
    this->send(21, this->_data, 0, true);
    if (this->recv(21, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void velocity::set_limit(float value)
{
    write_le(this->_data, value);
    this->send(21, this->_data, sizeof(float), false);
}

float velocity::get_p_gain(void)
{
    float value = 0;
    this->send(22, this->_data, 0, true);
    if (this->recv(22, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void velocity::set_p_gain(float value)
{
    write_le(this->_data, value);
    this->send(22, this->_data, sizeof(float), false);
}

float velocity::get_i_gain(void)
{
    float value = 0;
    this->send(23, this->_data, 0, true);
    if (this->recv(23, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void velocity::set_i_gain(float value)
{
    write_le(this->_data, value);
    this->send(23, this->_data, sizeof(float), false);
}

float velocity::get_deadband(void)
{
    float value = 0;
    this->send(24, this->_data, 0, true);
    if (this->recv(24, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void velocity::set_deadband(float value)
{
    write_le(this->_data, value);
    this->send(24, this->_data, sizeof(float), false);
}

float velocity::get_increment(void)
{
    float value = 0;
    this->send(25, this->_data, 0, true);
    if (this->recv(25, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void velocity::set_increment(float value)
{
    write_le(this->_data, value);
    this->send(25, this->_data, sizeof(float), false);
}



