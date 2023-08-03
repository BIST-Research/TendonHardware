/*
 * Author: Jayson De La Vega
 * Date created: 8/1/23
 */

#ifndef ML_PID_H
#define ML_PID_H

#include <Arduino.h>

#define ML_PID_SETTLING_TIME_MS  500
#define ML_PID_ERR_THRESHOLD     0.5   

typedef enum
{
    STEADY, RISE, SETTLING 
} ml_pid_state;

typedef struct
{
    float kp;
    float ki;
    float kd;

    uint8_t sample_time_ms;
    uint8_t deadband_offset;

    float integral;
    float last_sample_time;
    float prev_error;

    ml_pid_state state;
    unsigned long settling_timer;

} ml_pid_controller;


void    pid_set_params(ml_pid_controller* pid, float kp, float ki, float kd, uint8_t sample_time_ms, uint8_t deadband_offset);
void    pid_reset_integral(ml_pid_controller* pid);
int32_t pid_compute_control_signal(ml_pid_controller* pid, uint16_t setpoint, uint16_t current_position);
bool    pid_steady_state(ml_pid_controller* pid);

#endif