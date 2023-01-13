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

class Can : Node
{
    public:

        Can(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb):
            Node(_can_node_id, _send_cb, _recv_cb) {};
        uint32_t get_rate(void);
        void set_rate(uint32_t value);
        uint32_t get_id(void);
        void set_id(uint32_t value);

};
