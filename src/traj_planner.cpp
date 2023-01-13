/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <traj_planner.hpp>

float traj_planner::get_max_accel(void)
{
    float value = 0;
    this->send(58, this->_data, 0, true);
    if (this->recv(58, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void traj_planner::set_max_accel(float value)
{
    write_le(this->_data, value);
    this->send(58, this->_data, sizeof(float), false);
}

float traj_planner::get_max_decel(void)
{
    float value = 0;
    this->send(59, this->_data, 0, true);
    if (this->recv(59, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void traj_planner::set_max_decel(float value)
{
    write_le(this->_data, value);
    this->send(59, this->_data, sizeof(float), false);
}

float traj_planner::get_max_vel(void)
{
    float value = 0;
    this->send(60, this->_data, 0, true);
    if (this->recv(60, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void traj_planner::set_max_vel(float value)
{
    write_le(this->_data, value);
    this->send(60, this->_data, sizeof(float), false);
}


void traj_planner::move_to(float pos_setpoint)
{
    uint8_t data_len = 0;
    write_le(this->_data + data_len, pos_setpoint);
    data_len += sizeof(pos_setpoint);

    this->send(61, this->_data, data_len, false);
}

void traj_planner::move_to_tlimit(float pos_setpoint)
{
    uint8_t data_len = 0;
    write_le(this->_data + data_len, pos_setpoint);
    data_len += sizeof(pos_setpoint);

    this->send(62, this->_data, data_len, false);
}
uint8_t traj_planner::get_errors(void)
{
    uint8_t value = 0;
    this->send(63, this->_data, 0, true);
    if (this->recv(63, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}



