
#include <codec.h>
#include <tinymovr.h>

uint8_t node_id = 1;
uint8_t ep_bits = 6;

uint8_t get_device_info_ep_id = 3;
uint8_t get_state_ep_id = 4;
uint8_t get_encoder_estimates_ep_id = 5;

void Tinymovr::device_info(uint32_t *device_id, uint8_t *fw_major,
    uint8_t *fw_minor, uint8_t *fw_patch, uint8_t *temp
) {
    this->send_cb(get_device_info_ep_id, this->_data, 0, true);
    if (this->recv_cb(get_device_info_ep_id, this->_data, &dlc)) 
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
    this->set_state(0);
}

void Tinymovr::calibrate()
{
    this->set_state(1);
}

void Tinymovr::cl_control()
{
    this->set_state(2);
}

void Tinymovr::position_control()
{
    this->set_state(2);
    this->set_mode(2);
}

void Tinymovr::velocity_control()
{
    this->set_state(2);
    this->set_mode(1);
}

void Tinymovr::current_control()
{
    this->set_state(2);
    this->set_mode(0);
}

void Tinymovr::get_state(uint8_t *state)
{
    this->send_cb(get_state_ep_id, this->_data, 0, true);
    if (this->recv_cb(get_state_ep_id, this->_data, &dlc)) 
    {
        read_le(state, this->_data);
    }
}

void Tinymovr::get_encoder_estimates(float *pos_estimate, float *vel_estimate)
{
    this->send_cb(get_encoder_estimates_ep_id, this->_data, 0, true);
    if (this->recv_cb(get_encoder_estimates_ep_id, this->_data, &dlc)) 
    {
        read_le(pos_estimate, this->_data);
        read_le(vel_estimate, this->_data + 4);
    }
}

void Tinymovr::get_Iq_Id_meas(float *Iq_meas, float *Id_meas)
{
    this->send_cb(get_Iq_Id_meas_ep_id, this->_data, 0, true);
    if (this->recv_cb(get_Iq_Id_meas_ep_id, this->_data, &dlc)) 
    {
        read_le(Iq_meas, this->_data);
        read_le(Id_meas, this->_data + 4);
    }
}

void Tinymovr::get_pos_setpoint(float *pos_setpoint, float *vel_ff, float *Iq_ff)
{
    int16_t vel_ff_;
    int8_t Iq_ff_;
    this->send_cb(get_vel_setpoint_ep_id, this->_data, 0, true);
    if (this->recv_cb(get_vel_setpoint_ep_id, this->_data, &dlc)) 
    {
        read_le(pos_setpoint, this->_data);
        read_le(vel_ff_, this->_data + 4);
        read_le(Iq_ff_, this->_data + 4);
        *vel_ff = (float)(vel_ff_ * scale);
        *Iq_ff = (float)(Iq_ff_ * scale);
    }
}

void Tinymovr::get_vel_setpoint(float *vel_setpoint, float *Iq_ff)
{
    this->send_cb(get_vel_setpoint_ep_id, this->_data, 0, true);
    if (this->recv_cb(get_vel_setpoint_ep_id, this->_data, &dlc)) 
    {
        read_le(vel_setpoint, this->_data);
        read_le(Iq_ff, this->_data + 4);
    }
}

void Tinymovr::get_Iq_setpoint(float *Iq_setpoint)
{
    this->send_cb(get_Iq_setpoint_ep_id, this->_data, 0, true);
    if (this->recv_cb(get_Iq_setpoint_ep_id, this->_data, &dlc)) 
    {
        read_le(Iq_setpoint, this->_data);
    }
}

void Tinymovr::set_state(uint8_t state)
{
    
}

void Tinymovr::set_pos_setpoint(float pos_setpoint, float vel_ff, float Iq_cc)
{

}

void Tinymovr::set_vel_setpoint(float vel_setpoint, float Iq_ff)
{

}

void Tinymovr::set_Iq_setpoint(float Iq_setpoint)
{

}