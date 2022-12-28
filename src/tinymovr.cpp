
#include <codec.h>
#include <tinymovr.h>

const uint8_t ep_bits = 6;
#define RECV_DELAY_US (160.0f)

uint8_t get_device_info_ep_id = 0x01A;
uint8_t get_state_ep_id = 0x003;
uint8_t get_encoder_estimates_ep_id = 0x009;
uint8_t get_Iq_set_est_ep_id = 0x014;
uint8_t get_pos_setpoint_ep_id = 0x00C;
uint8_t get_vel_setpoint_ep_id = 0x00D;

uint8_t set_state_ep_id = 0x007;
uint8_t set_pos_setpoint_ep_id = 0x00C;
uint8_t set_vel_setpoint_ep_id = 0x00D;
uint8_t set_Iq_setpoint_ep_id = 0x00E;
uint8_t set_limits_ep_id = 0x00F;
uint8_t get_limits_ep_id = 0x015;
uint8_t reset_ep_id = 0x016;
uint8_t move_to_pos_with_vel_limit_ep_id = 0x021;
uint8_t set_max_plan_accel_decel_ep_id = 0x022;
uint8_t get_max_plan_accel_decel_ep_id = 0x023;

void Tinymovr::device_info(uint32_t *device_id, uint8_t *fw_major,
    uint8_t *fw_minor, uint8_t *fw_patch, uint8_t *temp
) {
    this->send(get_device_info_ep_id, this->_data, 0, true);
    if (this->recv(get_device_info_ep_id, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(device_id, this->_data);
        read_le(fw_major, this->_data + 4);
        read_le(fw_minor, this->_data + 5);
        read_le(fw_patch, this->_data + 6);
        read_le(temp, this->_data + 7);
    }
}

void Tinymovr::idle()
{
    this->set_state(0, 0);
}

void Tinymovr::calibrate()
{
    this->set_state(1, 0);
}

void Tinymovr::cl_control()
{
    this->set_state(2, 0);
}

void Tinymovr::position_control()
{
    this->set_state(2, 2);
}

void Tinymovr::velocity_control()
{
    this->set_state(2, 1);
}

void Tinymovr::current_control()
{
    this->set_state(2, 0);
}

void Tinymovr::get_state(uint8_t *state, uint8_t *mode)
{
    this->send(get_state_ep_id, this->_data, 0, true);
    if (this->recv(get_state_ep_id, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(state, this->_data + 1);
        read_le(mode, this->_data + 2);
    }
}

void Tinymovr::get_encoder_estimates(float *pos_estimate, float *vel_estimate)
{
    this->send(get_encoder_estimates_ep_id, this->_data, 0, true);
    if (this->recv(get_encoder_estimates_ep_id, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(pos_estimate, this->_data);
        read_le(vel_estimate, this->_data + 4);
    }
}

void Tinymovr::get_Iq_setpoint_estimate(float *Iq_set, float *Iq_est)
{
    this->send(get_Iq_set_est_ep_id, this->_data, 0, true);
    if (this->recv(get_Iq_set_est_ep_id, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(Iq_set, this->_data);
        read_le(Iq_est, this->_data + 4);
    }
}

void Tinymovr::get_pos_setpoint(float *pos_setpoint, float *vel_ff, float *Iq_ff)
{
    int16_t vel_ff_;
    int8_t Iq_ff_;
    this->send(get_pos_setpoint_ep_id, this->_data, 0, true);
    if (this->recv(get_pos_setpoint_ep_id, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(pos_setpoint, this->_data);
        read_le(&vel_ff_, this->_data + 4);
        read_le(&Iq_ff_, this->_data + 4);
        *vel_ff = (float)(vel_ff_ * VEL_INT16_TO_FLOAT_FACTOR);
        *Iq_ff = (float)(Iq_ff_ * IQ_INT16_TO_FLOAT_FACTOR);
    }
}

void Tinymovr::get_vel_setpoint(float *vel_setpoint, float *Iq_ff)
{
    this->send(get_vel_setpoint_ep_id, this->_data, 0, true);
    if (this->recv(get_vel_setpoint_ep_id, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(vel_setpoint, this->_data);
        read_le(Iq_ff, this->_data + 4);
    }
}

void Tinymovr::set_state(uint8_t state, uint8_t mode)
{
    write_le(state, this->_data);
    write_le(mode, this->_data + 1);
    this->send(set_state_ep_id, this->_data, 2, false);
}

void Tinymovr::set_pos_setpoint(float pos_setpoint, float vel_ff, float Iq_cc)
{
    write_le(pos_setpoint, this->_data);
    write_le((int16_t)(vel_ff * VEL_FLOAT_TO_INT16_FACTOR), this->_data + 4);
    write_le((int16_t)(Iq_cc * IQ_FLOAT_TO_INT16_FACTOR), this->_data + 6);
    this->send(set_pos_setpoint_ep_id, this->_data, 8, false);
}

void Tinymovr::set_vel_setpoint(float vel_setpoint, float Iq_ff)
{
    write_le(vel_setpoint, this->_data);
    write_le(Iq_ff, this->_data + 4);
    this->send(set_vel_setpoint_ep_id, this->_data, 8, false);
}

void Tinymovr::set_Iq_setpoint(float Iq_setpoint)
{
    write_le(Iq_setpoint, this->_data);
    this->send(set_Iq_setpoint_ep_id, this->_data, 4, false);
}

void Tinymovr::get_limits(float *vel_limit, float *Iq_limit)
{
    this->send(get_limits_ep_id, this->_data, 0, true);
    if (this->recv(get_limits_ep_id, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(vel_limit, this->_data);
        read_le(Iq_limit, this->_data + 4);
    }
}

void Tinymovr::set_limits(float vel_limit, float Iq_limit)
{
    write_le(vel_limit, this->_data);
    write_le(Iq_limit, this->_data + 4);
    this->send(set_limits_ep_id, this->_data, 8, false);
}

void Tinymovr::move_to_pos_with_vel_limit(float target_pos, float vel_limit)
{
    write_le(target_pos, this->_data);
    write_le(vel_limit, this->_data + 4);
    this->send(move_to_pos_with_vel_limit_ep_id, this->_data, 8, false);
}

void Tinymovr::get_max_plan_accel_decel(float *accel, float *decel)
{
    this->send(get_max_plan_accel_decel_ep_id, this->_data, 0, true);
    if (this->recv(get_max_plan_accel_decel_ep_id, this->_data, &(this->_dlc), RECV_DELAY_US)) 
    {
        read_le(accel, this->_data);
        read_le(decel, this->_data + 4);
    }
}

void Tinymovr::set_max_plan_accel_decel(float accel, float decel)
{
    write_le(accel, this->_data);
    write_le(decel, this->_data + 4);
    this->send(set_max_plan_accel_decel_ep_id, this->_data, 8, false);
}

void Tinymovr::reset()
{
    this->send(reset_ep_id, this->_data, 0, false);
}

void Tinymovr::send(uint8_t cmd_id, uint8_t *data, uint8_t data_size, bool rtr)
{
    const uint8_t arb_id = this->get_arbitration_id(cmd_id);
    this->send_cb(arb_id, data, data_size, rtr);
}

bool Tinymovr::recv(uint8_t cmd_id, uint8_t *data, uint8_t *data_size, uint16_t delay_us)
{
    // A delay of a few 100s of us needs to be inserted
    // to ensure the response has been transmitted.
    // TODO: Better handle this using an interrupt.
    if (delay_us > 0)
    {
        delayMicroseconds(delay_us);
    }
    const uint8_t arb_id = this->get_arbitration_id(cmd_id);
    return this->recv_cb(arb_id, data, data_size);
}

uint8_t Tinymovr::get_arbitration_id(uint8_t cmd_id)
{
    return this->can_node_id << ep_bits | cmd_id;
}