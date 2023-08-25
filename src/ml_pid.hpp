// /*
//  * Author: Jayson De La Vega
//  * Date created: 8/1/23
//  * 
//  * Modified 8/3/23 - Fixed type conversion errors
//  */

// #ifndef ML_PID_H
// #define ML_PID_H

// #include <Arduino.h>

// #define ML_PID_SETTLING_TIME_MS  1000   // TODO: Need to "design" this value
// #define ML_PID_ERR_THRESHOLD     1

// typedef struct
// {
//     float kp;
//     float ki;
//     float kd;

//     uint16_t sample_time_ms;
//     uint16_t deadband_offset;

//     float integral;
//     unsigned long last_sample_time;
//     float prev_error;

//     ml_pid_state state;
//     unsigned long settling_timer;

// } ml_pid_controller;


// void    pid_set_params(ml_pid_controller* pid, float kp, float ki, float kd, uint8_t sample_time_ms, uint8_t deadband_offset);
// void    pid_reset_integral(ml_pid_controller* pid);
// int32_t pid_compute_control_signal(ml_pid_controller* pid, int16_t setpoint, int16_t current_position);
// bool    pid_steady_state(ml_pid_controller* pid);

// #endif