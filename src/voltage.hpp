/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <cstdint>
#include <helpers.hpp>

class Voltage : Node
{
    public:

        Voltage(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb):
            Node(_can_node_id, _send_cb, _recv_cb) {};
        float get_Vq_setpoint(void);

};
