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

class Scheduler : Node
{
    public:

        Scheduler(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb):
            Node(_can_node_id, _send_cb, _recv_cb) {};
        uint32_t get_total(void);
        uint32_t get_busy(void);
        uint8_t get_errors(void);

};
