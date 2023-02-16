
#pragma once

#include <Arduino.h>

#define VEL_FLOAT_TO_INT16_FACTOR (0.1f)
#define VEL_INT16_TO_FLOAT_FACTOR (1.0f/VEL_FLOAT_TO_INT16_FACTOR)
#define IQ_FLOAT_TO_INT16_FACTOR (100.0f)
#define IQ_INT16_TO_FLOAT_FACTOR (1.0f/IQ_FLOAT_TO_INT16_FACTOR)

typedef enum ControlState
{
    STATE_IDLE = 0,
    STATE_CALIBRATE = 1,
    STATE_CL_CONTROL = 2
} ControlState;

typedef enum ControlMode
{
    CTRL_CURRENT = 0,
    CTRL_VELOCITY = 1,
    CTRL_POSITION = 2,
    CTRL_TRAJECTORY = 3
} ControlMode;


typedef void (*send_callback)(uint32_t arbitration_id, uint8_t *data, uint8_t dlc, bool rtr);
typedef bool (*recv_callback)(uint32_t arbitration_id, uint8_t *data, uint8_t *dlc);

class Tinymovr
{
  public:

    Tinymovr(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb):
      can_node_id(_can_node_id), send_cb(_send_cb), recv_cb(_recv_cb) {};
    
    void device_info(
      uint32_t *device_id,
      uint8_t *fw_major,
      uint8_t *fw_minor,
      uint8_t *fw_patch,
      uint8_t *temp
    );

    void idle();
    void calibrate();
    void cl_control();

    void position_control();
    void velocity_control();
    void current_control();

    void get_state(uint8_t *state, uint8_t *mode);
    void get_encoder_estimates(float *pos_estimate, float *vel_estimate);
    void get_Iq_setpoint_estimate(float *Iq_meas, float *Iq_set);
    void get_setpoints(float *pos_setpoint, float *vel_setpoint);
    void set_state(uint8_t state, uint8_t mode);
    void set_mode(uint8_t mode);
    void set_pos_setpoint(float pos_setpoint, float vel_ff, float Iq_ff);
    void set_vel_setpoint(float vel_setpoint, float Iq_ff);
    void set_Iq_setpoint(float Iq_setpoint);
    void get_limits(float *vel_limit, float *Iq_limit);
    void set_limits(float vel_limit, float Iq_limit);
    void move_to_pos_with_vel_limit(float target_pos, float vel_limit);
    void get_max_plan_accel_decel(float *accel, float *decel);
    void set_max_plan_accel_decel(float accel, float decel);

    void reset();

  private:
    uint8_t can_node_id;
    send_callback send_cb;
    recv_callback recv_cb;
    uint8_t _data[8];
    uint8_t _dlc;

    void send(uint8_t cmd_id, uint8_t *data, uint8_t data_size, bool rtr);
    bool recv(uint8_t cmd_id, uint8_t *data, uint8_t *data_size, uint16_t delay_us);
    uint8_t get_arbitration_id(uint8_t cmd_id);
};
