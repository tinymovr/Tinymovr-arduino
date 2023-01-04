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

class watchdog : Node
{
    public:

        watchdog(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb):
            Node(_can_node_id, _send_cb, _recv_cb) {};
        bool get_enabled(void);
        void set_enabled(bool value);
        bool get_triggered(void);
        float get_timeout(void);
        void set_timeout(float value);

};
