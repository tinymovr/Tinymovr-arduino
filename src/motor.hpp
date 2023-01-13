/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <helpers.hpp>

class Motor : Node
{
    public:

        Motor(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb):
            Node(_can_node_id, _send_cb, _recv_cb) {};
        float get_R(void);
        void set_R(float value);
        float get_L(void);
        void set_L(float value);
        uint8_t get_pole_pairs(void);
        void set_pole_pairs(uint8_t value);
        uint8_t get_type(void);
        void set_type(uint8_t value);
        float get_offset(void);
        void set_offset(float value);
        int8_t get_direction(void);
        void set_direction(int8_t value);
        bool get_calibrated(void);
        float get_I_cal(void);
        void set_I_cal(float value);
        uint8_t get_errors(void);

};
