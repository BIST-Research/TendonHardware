/*
 * Author: Jayson De La Vega
 * Date created: 8/1/23
 * 
 * Modified 8/3/23 - Fixed type conversion errors
 */

#ifndef ML_PID_ASYNC_H
#define ML_PID_ASYNC_H

#include <Arduino.h>

#define ML_PID_SETTLING_TIME_MS  1000   // TODO: Need to "design" this value
#define ML_PID_ERR_THRESHOLD     1

typedef enum
{
    STEADY, RISE, SETTLING 
} ml_pid_state;

typedef struct
{
    float kp;
    float ki;
    float kd;

    uint16_t sample_time_ms;
    uint16_t deadband_offset;

    float integral;
    unsigned long last_sample_time;
    float prev_error;

    ml_pid_state state;
    unsigned long settling_timer;

} ml_pid_async;


void    pid_set_params_async        (ml_pid_async* pid, float kp, float ki, float kd, uint8_t sample_time_ms, uint8_t deadband_offset);
void    pid_reset_integral_async    (ml_pid_async* pid);
int32_t pid_compute_signal_async    (ml_pid_async* pid, int16_t setpoint, int16_t current_position);
bool    pid_steady_state_async      (ml_pid_async* pid);

#endif