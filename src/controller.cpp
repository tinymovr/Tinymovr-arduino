/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <Controller.hpp>

uint8_t Controller::get_state(void)
{
    uint8_t value = 0;
    this->send(14, this->_data, 0, true);
    if (this->recv(14, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Controller::set_state(uint8_t value)
{
    write_le(this->_data, value);
    this->send(14, this->_data, sizeof(uint8_t), false);
}

uint8_t Controller::get_mode(void)
{
    uint8_t value = 0;
    this->send(15, this->_data, 0, true);
    if (this->recv(15, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Controller::set_mode(uint8_t value)
{
    write_le(this->_data, value);
    this->send(15, this->_data, sizeof(uint8_t), false);
}

uint8_t Controller::get_warnings(void)
{
    uint8_t value = 0;
    this->send(16, this->_data, 0, true);
    if (this->recv(16, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

uint8_t Controller::get_errors(void)
{
    uint8_t value = 0;
    this->send(17, this->_data, 0, true);
    if (this->recv(17, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}


void Controller::calibrate()
{
    this->send(35, this->_data, 0, true);
}

void Controller::idle()
{
    this->send(36, this->_data, 0, true);
}

void Controller::position_mode()
{
    this->send(37, this->_data, 0, true);
}

void Controller::velocity_mode()
{
    this->send(38, this->_data, 0, true);
}

void Controller::current_mode()
{
    this->send(39, this->_data, 0, true);
}

float Controller::set_pos_vel_setpoints(float pos_setpoint, float vel_setpoint)
{
    uint8_t data_len = 0;
    write_le(this->_data + data_len, pos_setpoint);
    data_len += sizeof(pos_setpoint);
    write_le(this->_data + data_len, vel_setpoint);
    data_len += sizeof(vel_setpoint);

    this->send(40, this->_data, data_len, false);
}


