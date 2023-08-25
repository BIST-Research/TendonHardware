/*
 * Author: Jayson De La Vega
 * Date created: 8/7/23
 * 
 * Description: A motor object written using the Active Object framework
 * 
 * Modified 8/9/23 - Moved ML_Motor_Dispatch() to ml_motor_module.c
 * 
 * Modified 8/10/23- Implemented a new constructor ML_Motor and encoder ticks
 *                   callback function.
 */
#ifndef ML_MOTOR_MODULE_H
#define ML_MOTOR_MODULE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <ml_active_object.h>
#include <ml_encoder_module.h>
#include <ml_port.h>
#include <ml_tcc.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define ML_HPCB_LV_75P1     (75.81)
#define ML_HPCB_LV_100P1    (100.37)
#define ML_HPCB_LV_150P1    (150.58)
#define ML_HPCB_LV_210P1    (210.59)

#define ML_ENC_CPR      (12)

#define ML_MOTOR_MAX_PERIOD (6000)
#define ML_MOTOR_MAX_SPEED  (ML_MOTOR_MAX_PERIOD - 10)

typedef enum {
    SET_PWM_SIG = USER_SIG,
    SET_DIR_SIG,
    SET_TARGET_POS_SIG
} Motor_EventSignals;

typedef enum
{
    CW, CCW, OFF
} ml_motor_dir;

typedef enum
{
    RISE, SETTLING, STEADY
} ml_pid_state;

typedef struct {
    float     K_p, K_i, K_d;
    uint16_t  sample_time_ms;
    uint16_t  deadband_offset;

    float           integral;
    float           prev_error;

    ml_pid_state    state;

    int32_t         control_sig;
} ML_PID_t;

typedef struct {
    Active super;

    // private data
    ml_pin_settings         phase;
    ml_pin_settings         drive;
    ML_PID_t                pid;

    Tcc                     *pwm_inst;
    uint8_t                 pwm_cc_num;
    float                   gear_ratio;
    uint8_t                 cpr;

    int16_t                 ticks;
    
} ML_Motor_t;

// task stack
// static Event *ml_motor_queue[10];
// static ML_Motor_t motor;
// Active *AO_ML_Motor = &motor.super;

/**
 * @brief Constructs a motor active object. Calling this function does not start a motor task.
 *        To start the motor task, you must call Active_start() using the motor object's super class.
 */
// void ML_Motor_ctor(ML_Motor_t * me);

/**
 * @brief Constructs a motor active object. Calling this function does not start a motor task.
 *        To start the motor task, you must call Active_start() using the motor object's super class.
 * 
 * @return A motor object
 * 
 * @param ph A ml_pin_settings object for the motor's phase pin
 * @param drive A ml_pin_settings object for the motor's pwm pin
 * @param pwm_inst A pointer to the TCC instance used to control the motor PWM
 * @param gear_ratio The motor gearbox's gear ratio
 * @param cpr The counts per revolution of the motor's encoder
 */
ML_Motor_t ML_Motor(
    ml_pin_settings ph,
    ml_pin_settings drive,
    Tcc * pwm_inst,
    uint8_t pwm_cc_num,
    float gear_ratio,
    uint8_t cpr);

/**
 * @brief Creates an observer on the encoder tick value of the specified encoder.
 * 
 * @param me A pointer to the motor object that listens to encoder ticks.
 * @param enc_ptr A pointer to the encoder object that publishes its encoder ticks.
 */
void ML_Motor_attachEncoder(ML_Motor_t * const me, ML_Encoder_t * const enc_ptr);

/**
 * @brief Sets the PID control parameters of the motor object
 * 
 * @param me A pointer to the motor object to be modified.
 * @param K_p P gain.
 * @param K_i I gain.
 * @param K_d D gain.
 * @param sample_time_ms The sample time of the PID controller in ms.
 * @param deadband_offset The deadband_offset of the PID controller
 */
void ML_Motor_setPIDParams(
    ML_Motor_t * const me,
    float K_p, float K_i, float K_d,
    uint16_t sample_time_ms, uint16_t deadband_offset);

/**
 * @brief Starts a motor active object task
 * 
 * @param me A pointer to the motor object to start
 * @param priority The The FreeRTOS priority initially assigned to this task
 * @param queuelen The length of the task's event queue 
 */
void ML_Motor_start(ML_Motor_t * const me, uint8_t priority, uint32_t queuelen);

#ifdef __cplusplus
}
#endif

#endif