
#pragma once

#include <Arduino.h>

typedef void (*send_callback)(uint32_t arbitration_id, uint8_t *data, uint8_t dlc, bool rtr);
typedef bool (*recv_callback)(uint32_t arbitration_id, uint8_t *data, uint8_t *dlc);

class Tinymovr
{
  public:

    Tinymovr(uint8_t _can_node_id, send_callback _send_cb, recv_callback _recv_cb):
      can_node_id(_can_node_id), send_cb(_send_cb), recv_cb(_recv_cb);
    
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

    void get_state(uint8_t *state);
    void get_mode(uint8_t *mode);
    void get_encoder_estimates(float *pos_estimate, float *vel_estimate);
    void get_Iq_Id_meas(float *Iq_meas, float *Id_meas);
    void get_pos_setpoint(float *pos_setpoint, float *vel_ff, float *Iq_ff);
    void get_vel_setpoint(float *vel_setpoint, float *Iq_ff);
    void get_Iq_setpoint(float *Iq_setpoint);
    void set_state(uint8_t state);
    void set_mode(uint8_t mode);
    void set_pos_setpoint(float pos_setpoint, float vel_ff, float Iq_ff);
    void set_vel_setpoint(float vel_setpoint, float Iq_ff);
    void set_Iq_setpoint(float Iq_setpoint);

  private:
    uint8_t can_node_id;
    send_callback send_cb;
    recv_callback recv_cb;
    uint8_t _data[8];
};
