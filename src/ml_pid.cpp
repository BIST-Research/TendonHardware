/*
 * Author: Jayson De La Vega
 * Date created: 8/1/23
 * 
 * Modified 8/3/23 - Added PID FSM for steady state detection
 */

#include <ml_pid.hpp>
#include <ml_motor.hpp>

void pid_set_params(ml_pid_controller* pid, float kp, float ki, float kd, uint8_t sample_time_ms, uint8_t deadband_offset) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->sample_time_ms = sample_time_ms;
    pid->deadband_offset = deadband_offset;

}

void pid_reset_integral(ml_pid_controller* pid) {
    pid->integral = 0;
}

int32_t pid_compute_control_signal(ml_pid_controller* pid, uint16_t setpoint, uint16_t current_position) {
    float control_signal = 0;

    unsigned long current_time = millis();
    unsigned long _dt = current_time - pid->last_sample_time;

    if (_dt >= (unsigned long)pid->sample_time_ms) {
        float p_error = (setpoint - current_position);
        float d_error = (p_error - pid->prev_error);
        pid->integral += p_error;
        pid->prev_error = p_error;

        control_signal = (pid->kp * p_error) + (pid->ki * pid->integral) + (pid->kd * d_error);

        if (p_error > 0) {
            control_signal += pid->deadband_offset;
        } else {
            control_signal -= pid->deadband_offset;
        }

        pid->last_sample_time = millis();

        if (control_signal >= ML_MOTOR_MAX_SPEED)
            control_signal = ML_MOTOR_MAX_SPEED;
        else if (control_signal <= -1 * ML_MOTOR_MAX_SPEED)
            control_signal = -1 * ML_MOTOR_MAX_SPEED;
    }

    return (int32_t)control_signal;
}

bool pid_steady_state(ml_pid_controller* pid)
{
    ml_pid_state s = pid->state;

    switch(s)
    {
        case STEADY:
            if (pid->prev_error >= ML_PID_ERR_THRESHOLD)
                s = RISE;
            break;
        case RISE:
            if (pid-> prev_error >= ML_PID_ERR_THRESHOLD)
            {
                s = SETTLING;
                pid->settling_timer = millis();
            }
            break;
        case SETTLING:
            if (pid->prev_error >= ML_PID_ERR_THRESHOLD)
                s = RISE;
            if (millis() - pid->settling_timer >= ML_PID_SETTLING_TIME_MS)
                s = STEADY;
    }

    pid->state = s;
    return s == STEADY;
}