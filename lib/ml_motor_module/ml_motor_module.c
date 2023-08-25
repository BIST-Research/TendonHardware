/*
 * Author: Jayson De La Vega
 * Date created: 8/7/23
 * 
 * Description: A motor object written using the Active Object framework
 * 
 * Modified 8/9/23 - Created ML_Motor_setDirection and ML_Motor_pin_init().
 *                   Implemented ML_Motor_pidControlLoop().
 * 
 * Modified 8/10/23- Implemented a new constructor ML_Motor and encoder ticks
 *                   callback function.
 */
#include <ml_motor_module.h>
#include <ml_active_object.h>
#include <FreeRTOS_SAMD51.h>

// private function prototypes
static void ML_Motor_dispatch           (ML_Motor_t * const me, Event const * const e);
static void ML_Motor_pin_init           (ML_Motor_t * const me);
static void ML_Motor_setSpeed           (ML_Motor_t * const me, uint32_t speed);
static void ML_Motor_setDirection       (ML_Motor_t * const me, ml_motor_dir dir);
static int32_t ML_Motor_pidControlLoop  (ML_Motor_t * const me, int32_t setpoint);
static void ML_Motor_updatePosition     (int32_t ticks, void* instance);

ML_Motor_t ML_Motor(
    ml_pin_settings ph,
    ml_pin_settings drive,
    Tcc * pwm_inst,
    uint8_t pwm_cc_num,
    float gear_ratio,
    uint8_t cpr)
{
    // Initialize the encoder object

    ML_Motor_t m = {
        {},
        ph,
        drive,

        // PID parameters - empty until user calls ML_Motor_setPIDParams()
        {},

        pwm_inst, pwm_cc_num, gear_ratio, cpr, 0
    };

    // Initialize the super class
    Active_ctor(&(m.super), (DispatchHandler)&ML_Motor_dispatch);

    return m;
}

void ML_Motor_attachEncoder(ML_Motor_t * const me, ML_Encoder_t * const enc_ptr)
{
    ML_Encoder_register_stateChangeCallback(enc_ptr, ML_Motor_updatePosition, (void *)me);      // Create a listener on encoder counts
}

void ML_Motor_setPIDParams(
    ML_Motor_t * const me,
    float K_p, float K_i, float K_d,
    uint16_t sample_time_ms, uint16_t deadband_offset)
{
    ML_PID_t pid = {K_p, K_i, K_d, sample_time_ms, deadband_offset, 0, 0, STEADY, 0};
    me->pid = pid;
}

void ML_Motor_start(ML_Motor_t * const me, uint8_t priority, uint32_t queuelen)
{
    Active_start(&(me->super), priority, queuelen, 0);
}

// void ML_Motor_ctor(ML_Motor_t * const me)
// {
//     Active_ctor(&me->super, (DispatchHandler)&ML_Motor_dispatch);

//     // ML_Encoder_register_stateChangeCallback(me->enc, ML_Motor_updatePosition, (void *)me);   // Create a listener on encoder counts
// }

static void ML_Motor_dispatch(ML_Motor_t * const me, Event const * const e)
{
    switch (e->sig) {
        case INIT_SIG: {
            ML_Motor_pin_init(me);
            break;
        }
        case SET_PWM_SIG: {

            uint16_t speed = (uint16_t)e->param;

            UINT16_MAX;

            ML_Motor_setSpeed(me, speed);
            break;
        }
        case SET_DIR_SIG: {
            ml_motor_dir dir = (ml_motor_dir)e->param;

            ML_Motor_setDirection(me, dir);
            break;
        }
        case SET_TARGET_POS_SIG: {
            int32_t target_angle = e->param;
            int32_t target_counts = target_angle * (me->cpr * me->gear_ratio) / 360;

            int32_t control_sig = ML_Motor_pidControlLoop(me, target_counts);
            me->pid.control_sig = control_sig;

            if (control_sig > 0)
            {
                ML_Motor_setDirection(me, CW);
            }
            else if (control_sig < 0)
            {
                ML_Motor_setDirection(me, CCW);
            }
            else
            {
                ML_Motor_setDirection(me, OFF);
            }
            ML_Motor_setSpeed(me, (uint32_t)abs(control_sig));

            break;
        }
        default: {
            break;
        }
    }
}

void ML_Motor_pin_init(ML_Motor_t * const me)
{
    peripheral_port_init(&(me->phase));
    peripheral_port_init(&(me->drive));

    ML_Motor_setDirection(me, OFF);
}

void ML_Motor_setSpeed(ML_Motor_t * const me, uint32_t speed)
{
    me->pwm_inst->CCBUF[me->pwm_cc_num].reg = TCC_CCBUF_CCBUF(speed);
    TCC_sync(me->pwm_inst); // TODO: Modify this synchronization event to utilize more RTOS-friendly blocking
    // while (me->pwm_inst->SYNCBUSY.reg)
}

// TODO: Optimize this function for execution speed
void ML_Motor_setDirection(ML_Motor_t * const me, ml_motor_dir dir)
{
    switch(dir)
    {
        case OFF:
            me->pwm_inst->CCBUF[me->pwm_cc_num].reg = TCC_CCBUF_CCBUF(0x00);
            TCC_sync(me->pwm_inst); // TODO: Modify this synchronization event to utilize more RTOS-friendly blocking
            break;
        case CW:
            logical_set(&me->phase);
            break;
        case CCW:
            logical_unset(&me->phase);
            break;
        default:
            break;
    }
}

int32_t ML_Motor_pidControlLoop(ML_Motor_t * const me, int32_t setpoint)
{
    ML_PID_t *my_pid = &(me->pid);

    float p_error = (setpoint - me->ticks);
    float i_error = (my_pid->integral += p_error);
    float d_error = (p_error - my_pid->prev_error);

    my_pid->prev_error = p_error;
    
    float pid = (my_pid->K_p * p_error) + (my_pid->K_i * i_error) + (my_pid->K_d * d_error);

    // Deadband offset not typically used
    // if (p_error > 0) {
    //     pid += my_pid->deadband_offset;
    // } else {
    //     pid -= my_pid->deadband_offset;
    // }

    if (pid > ML_MOTOR_MAX_SPEED) pid = ML_MOTOR_MAX_SPEED;
    if (pid < -1 * ML_MOTOR_MAX_SPEED) pid = -1 * ML_MOTOR_MAX_SPEED;

    return (int32_t)pid;
}

void ML_Motor_updatePosition(int32_t ticks, void * instance)
{
    ML_Motor_t * m = (ML_Motor_t *)instance;
    m->ticks = ticks;
}