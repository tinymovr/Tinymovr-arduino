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

class current : Node
{
    public:

        current(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb):
            Node(_can_node_id, _send_cb, _recv_cb) {};
        float get_Iq_setpoint(void);
        void set_Iq_setpoint(float value);
        float get_Id_setpoint(void);
        float get_Iq_limit(void);
        void set_Iq_limit(float value);
        float get_Iq_estimate(void);
        float get_bandwidth(void);
        void set_bandwidth(float value);
        float get_Iq_p_gain(void);
        float get_max_Ibus_regen(void);
        void set_max_Ibus_regen(float value);
        float get_max_Ibrake(void);
        void set_max_Ibrake(float value);

};
