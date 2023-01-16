/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <current.hpp>

float Current_::get_Iq_setpoint(void)
{
    float value = 0;
    this->send(26, this->_data, 0, true);
    if (this->recv(26, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Current_::set_Iq_setpoint(float value)
{
    write_le(value, this->_data);
    this->send(26, this->_data, sizeof(float), false);
}

float Current_::get_Id_setpoint(void)
{
    float value = 0;
    this->send(27, this->_data, 0, true);
    if (this->recv(27, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Current_::get_Iq_limit(void)
{
    float value = 0;
    this->send(28, this->_data, 0, true);
    if (this->recv(28, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Current_::set_Iq_limit(float value)
{
    write_le(value, this->_data);
    this->send(28, this->_data, sizeof(float), false);
}

float Current_::get_Iq_estimate(void)
{
    float value = 0;
    this->send(29, this->_data, 0, true);
    if (this->recv(29, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Current_::get_bandwidth(void)
{
    float value = 0;
    this->send(30, this->_data, 0, true);
    if (this->recv(30, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Current_::set_bandwidth(float value)
{
    write_le(value, this->_data);
    this->send(30, this->_data, sizeof(float), false);
}

float Current_::get_Iq_p_gain(void)
{
    float value = 0;
    this->send(31, this->_data, 0, true);
    if (this->recv(31, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Current_::get_max_Ibus_regen(void)
{
    float value = 0;
    this->send(32, this->_data, 0, true);
    if (this->recv(32, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Current_::set_max_Ibus_regen(float value)
{
    write_le(value, this->_data);
    this->send(32, this->_data, sizeof(float), false);
}

float Current_::get_max_Ibrake(void)
{
    float value = 0;
    this->send(33, this->_data, 0, true);
    if (this->recv(33, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Current_::set_max_Ibrake(float value)
{
    write_le(value, this->_data);
    this->send(33, this->_data, sizeof(float), false);
}



