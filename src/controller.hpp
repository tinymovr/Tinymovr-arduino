/*
* This file was automatically generated using Avlos.
* https://github.com/tinymovr/avlos
*
* Any changes to this file will be overwritten when
* content is regenerated.
*/

#pragma once

#include <helpers.hpp>
#include <position.hpp>
#include <velocity.hpp>
#include <current.hpp>
#include <voltage.hpp>

class Controller : Node
{
    public:

        Controller(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb):
            Node(_can_node_id, _send_cb, _recv_cb)
            , position(_can_node_id, _send_cb, _recv_cb)
            , velocity(_can_node_id, _send_cb, _recv_cb)
            , current(_can_node_id, _send_cb, _recv_cb)
            , voltage(_can_node_id, _send_cb, _recv_cb) {};
        uint8_t get_state(void);
        void set_state(uint8_t value);
        uint8_t get_mode(void);
        void set_mode(uint8_t value);
        uint8_t get_warnings(void);
        uint8_t get_errors(void);
        position position;
        velocity velocity;
        current current;
        voltage voltage;
        void calibrate();
        void idle();
        void position_mode();
        void velocity_mode();
        void current_mode();
        float set_pos_vel_setpoints(float pos_setpoint, float vel_setpoint);

};
