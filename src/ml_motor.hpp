/*
 * Author: Ben Westcott
 * Date created: 7/29/23
 */

#ifndef ML_MOTOR_H
#define ML_MOTOR_H

#include <Arduino.h>
#include <ml_port.h>
#include <ml_tcc.h>
#include <ml_pid.hpp>

#define ML_HPCB_LV_75P1     (75.81)
#define ML_HPCB_LV_100P1    (100.37)
#define ML_HPCB_LV_150P1    (150.58)
#define ML_HPCB_LV_210P1    (210.59)

#define ML_ENC_CPR      (12)

#define ML_MOTOR_MAX_PERIOD (6000)
#define ML_MOTOR_MAX_SPEED  (ML_MOTOR_MAX_PERIOD - 10)

typedef struct
{
    const ml_pin_settings encoder_a;
    const ml_pin_settings encoder_b;
    const ml_pin_settings phase;
    const ml_pin_settings drive;
    ml_pid_controller pid_ctrl;

    Tcc *pwm_inst;
    const uint8_t pwm_cc_num;
    const float gear_ratio;
    const uint8_t cpr;
    
    uint16_t ticks;
    uint8_t last_encoded;

} ml_motor;

typedef enum
{
    CW, CCW, OFF
} ml_motor_dir;


void motor_set_speed(ml_motor *motor, uint16_t speed);
void motor_set_direction(ml_motor *motor, ml_motor_dir dir);
void motor_pid_control_loop(ml_motor *motor, uint16_t setpoint);

#endif