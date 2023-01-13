/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#include <Watchdog.hpp>

bool Watchdog::get_enabled(void)
{
    bool value = 0;
    this->send(64, this->_data, 0, true);
    if (this->recv(64, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Watchdog::set_enabled(bool value)
{
    write_le(this->_data, value);
    this->send(64, this->_data, sizeof(bool), false);
}

bool Watchdog::get_triggered(void)
{
    bool value = 0;
    this->send(65, this->_data, 0, true);
    if (this->recv(65, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

float Watchdog::get_timeout(void)
{
    float value = 0;
    this->send(66, this->_data, 0, true);
    if (this->recv(66, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(&value, this->_data);
    }
    return value;
}

void Watchdog::set_timeout(float value)
{
    write_le(this->_data, value);
    this->send(66, this->_data, sizeof(float), false);
}



