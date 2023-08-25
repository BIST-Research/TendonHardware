// /*
//  * Author: Ben Westcott, Jayson De La Vega
//  * Date created: 7/29/23
//  * 
//  * Modified 8/1/23 - added PID control loop functionality
//  */

// #include <ml_motor.hpp>
// #include <ml_pid.hpp>

// void motor_set_speed(ml_motor *motor, uint16_t speed)
// {
//     motor->pwm_inst->CCBUF[motor->pwm_cc_num].reg = TCC_CCBUF_CCBUF(speed);
//     TCC_sync(motor->pwm_inst);
// }

// void motor_set_direction(ml_motor *motor, ml_motor_dir dir)
// {
//     if(dir == OFF)
//     {
//         motor->pwm_inst->CCBUF[motor->pwm_cc_num].reg = TCC_CCBUF_CCBUF(0x00);
//         TCC_sync(motor->pwm_inst);
//     } 
//     else if(dir == CW)
//     {
//         logical_set(&motor->phase);
//     } 
//     else
//     {
//         logical_unset(&motor->phase);
//     }
// }

// void motor_pid_control_loop(ml_motor *motor, uint16_t setpoint)
// {
//     uint16_t target_counts = setpoint * ((motor->cpr * motor->gear_ratio) / 360);
    
//     int32_t control_signal = pid_compute_control_signal(&(motor->pid_ctrl), target_counts, motor->ticks);


//     if (control_signal > 0)
//     {
//         motor_set_direction(motor, CW);
//     }
//     else if (control_signal < 0)
//     {
//         motor_set_direction(motor, CCW);
//     }
//     else
//     {
//         motor_set_direction(motor, OFF);
//     }
//     motor_set_speed(motor, abs(control_signal));
// }