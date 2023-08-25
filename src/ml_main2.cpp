// /*
// #include <header/sine_tables.hpp>
// #include <header/ml_port.hpp>
// #include <header/ml_clocks.hpp>
// #include <header/ml_adc.hpp>
// #include <header/ml_dmac.hpp>
// #include <header/ml_tcc.hpp>
// #include <header/ml_ac.hpp>
// */

// #include <ml_clocks.h>
// #include <ml_motor.hpp>
// #include <ml_tcc.h>
// #include <ml_eic.h>
// #include <ml_encoder.hpp>

// #define N_MOTORS (12)

// #define NUM_POSITIONS   3


// // TODO: Need to tune each motor to find parameters
// ml_motor stack_pin_map[N_MOTORS] = 
// {
//     {
//         // D40 --> PC13 --> EXTINT[13]
//         {PORT_GRP_C, 13, PF_A, PP_ODD, INPUT_PULL_UP, DRIVE_OFF},
//         // D41 --> PC12 --> EXTINT[12]
//         {PORT_GRP_C, 12, PF_A, PP_EVEN, INPUT_PULL_UP, DRIVE_OFF},
//         // D21 --> PB21
//         {PORT_GRP_B, 21, PF_B, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},
//         // D25 --> PC16
//         {PORT_GRP_C, 16, PF_F, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},

//         {2000, 0, 0, 100, 0, 0, 0, 0, STEADY, 0},

//         TCC0, 0, ML_HPCB_LV_75P1, ML_ENC_CPR, 0, 0
//     },

//     {
//         // D42 --> PC15 --> EXTINT[15]
//         {PORT_GRP_C, 15, PF_A, PP_ODD, INPUT_PULL_UP, DRIVE_OFF},
//         // D43 --> PC14 --> EXTINT[14]
//         {PORT_GRP_C, 14, PF_A, PP_EVEN, INPUT_PULL_UP, DRIVE_OFF},
//         // D20 --> PB20
//         {PORT_GRP_B, 20, PF_B, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},
//         // D24 --> PC17
//         {PORT_GRP_C, 17, PF_F, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},

//         {2000, 0, 0, 0, 0, 0, 0, 0, STEADY, 0},

//         TCC0, 1, ML_HPCB_LV_75P1, ML_ENC_CPR, 0, 0
//     },

//     {
//         // D44 --> PC11 --> EXTINT[11]
//         {PORT_GRP_C, 11, PF_A, PP_ODD, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D45 --> PC10 --> EXTINT[10]
//         {PORT_GRP_C, 10, PF_A, PP_EVEN, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D19 --> PB13
//         {PORT_GRP_B, 13, PF_B, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},
//         // D2 --> PC18
//         {PORT_GRP_C, 18, PF_F, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},

//         {2000, 0, 0, 0, 0, 0, 0, 0, STEADY, 0},

//         TCC0, 2, ML_HPCB_LV_75P1, ML_ENC_CPR, 0, 0
//     },

//     {
//         // D46 --> PC06 --> EXTINT[6]
//         {PORT_GRP_C, 6, PF_A, PP_EVEN, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D47 --> PC07 --> EXTINT[9]
//         {PORT_GRP_C, 7, PF_A, PP_ODD, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D18 --> PB12
//         {PORT_GRP_B, 12, PF_B, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},
//         // D3 --> PC19
//         {PORT_GRP_C, 19, PF_F, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},

//         {2000, 0, 0, 0, 0, 0, 0, 0, STEADY, 0},

//         TCC0, 3, ML_HPCB_LV_75P1, ML_ENC_CPR, 0, 0
//     },

//     {
//         // D48 --> PC04 --> EXTINT[4]
//         {PORT_GRP_C, 4, PF_A, PP_EVEN, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D49 --> PC05 --> EXTINT[5]
//         {PORT_GRP_C, 5, PF_A, PP_ODD, INPUT_PULL_DOWN, DRIVE_OFF}, 
//         // D17 --> PC23
//         {PORT_GRP_C, 23, PF_B, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},
//         // D4 --> PC20
//         {PORT_GRP_C, 20, PF_F, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},

//         {2000, 0, 0, 0, 0, 0, 0, 0, STEADY, 0},

//         TCC0, 4, ML_HPCB_LV_75P1, ML_ENC_CPR, 0, 0
//     },

//     {
//         // D30 --> PA23 --> EXTINT[7]
//         {PORT_GRP_A, 23, PF_A, PP_ODD, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D51 --> PD08 --> EXTINT[3]
//         {PORT_GRP_D, 8, PF_A, PP_EVEN, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D16 --> PC22
//         {PORT_GRP_C, 22, PF_B, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},
//         // D5 --> PC21
//         {PORT_GRP_C, 21, PF_F, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},

//         {2000, 0, 0, 0, 0, 0, 0, 0, STEADY, 0},

//         TCC0, 5, ML_HPCB_LV_75P1, ML_ENC_CPR, 0, 0
//     },

//     /*****************************************/

//     {
//         // D52 --> PD09 --> EXTINT[4] (Conflict with PC04)
//         {PORT_GRP_D, 9, PF_B, PP_ODD, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D53 --> PD10 --> EXTINT[5] (Conflict with PC05)
//         {PORT_GRP_D, 10, PF_B, PP_EVEN, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D15 --> PB17
//         {PORT_GRP_B, 17, PF_B, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},
//         // D37 --> PA16
//         {PORT_GRP_A, 16, PF_F, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},

//         {2000, 0, 0, 0, 0, 0, 0, 0, STEADY, 0},

//         TCC1, 0, ML_HPCB_LV_75P1, ML_ENC_CPR, 0, 0
//     },

//     {
//         // D38 --> PB15 --> EXTINT[15] (Conflict with PC15)
//         {PORT_GRP_B, 15, PF_B, PP_ODD, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D39 --> PB14 --> EXTINT[14] (Conflict with PC14)
//         {PORT_GRP_B, 14, PF_B, PP_EVEN, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D14 --> PB16
//         {PORT_GRP_B, 16, PF_B, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},
//         // D36 --> PA17
//         {PORT_GRP_A, 17, PF_F, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},

//         {2000, 0, 0, 0, 0, 0, 0, 0, STEADY, 0},

//         TCC1, 1, ML_HPCB_LV_75P1, ML_ENC_CPR, 0, 0
//     },

//     {
//         // D8 --> PB18 --> EXTINT[2]
//         {PORT_GRP_D, 18, PF_B, PP_EVEN, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D31 --> PA22 --> EXTINT[6]
//         {PORT_GRP_A, 22, PF_B, PP_EVEN, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D0 --> PB25
//         {PORT_GRP_B, 25, PF_B, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},
//         // D35 --> PA18
//         {PORT_GRP_A, 18, PF_F, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},

//         {2000, 0, 0, 0, 0, 0, 0, 0, STEADY, 0},

//         TCC1, 2, ML_HPCB_LV_75P1, ML_ENC_CPR, 0, 0
//     },

//     {

//         // D12 --> PB00 --> EXTINT[0]
//         {PORT_GRP_A, 0, PF_B, PP_EVEN, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D29 --> PB19 --> EXTINT[3] (Conflict w/ PD08)
//         {PORT_GRP_B, 19, PF_B, PP_ODD, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D1 --> PB24
//         {PORT_GRP_B, 24, PF_B, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},
//         // D34 --> PA19
//         {PORT_GRP_A, 19, PF_F, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},

//         {2000, 0, 0, 0, 0, 0, 0, 0, STEADY, 0},

//         TCC1, 3, ML_HPCB_LV_75P1, ML_ENC_CPR, 0, 0
//     },

//     {
//         // D26 --> PA12 --> EXTINT[12] (Conflict w/ C12)
//         {PORT_GRP_A, 12, PF_B, PP_EVEN, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D27 --> PA13 --> EXTINT[13] (Conflict w/ C13)
//         {PORT_GRP_A, 13, PF_B, PP_ODD, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D6 --> PD20
//         {PORT_GRP_D, 20, PF_B, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},
//         // D33 --> PA20
//         {PORT_GRP_A, 20, PF_F, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},

//         {2000, 0, 0, 0, 0, 0, 0, 0, STEADY, 0},

//         TCC1, 4, ML_HPCB_LV_75P1, ML_ENC_CPR, 0, 0
//     },

//     {
//         // D22 --> PD12 --> EXTINT[7] (Conflict w/ A23)
//         {PORT_GRP_D, 12, PF_B, PP_EVEN, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D13 --> PB01 --> EXTINT[1]
//         {PORT_GRP_A, 1, PF_B, PP_ODD, INPUT_PULL_DOWN, DRIVE_OFF},
//         // D7 --> PD21
//         {PORT_GRP_D, 21, PF_B, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},
//         // D32 --> PA21
//         {PORT_GRP_A, 21, PF_F, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},

//         {2000, 0, 0, 0, 0, 0, 0, 0, STEADY, 0},

//         TCC1, 5, ML_HPCB_LV_75P1, ML_ENC_CPR, 0, 0
//     }
// };

// uint32_t positions[NUM_POSITIONS] = {0, 90, 180};


// void dstack_a_init(void)
// {
//     ML_SET_GCLK7_PCHCTRL(TCC0_GCLK_ID);

//     TCC_DISABLE(TCC0);
//     TCC_SWRST(TCC0);
//     TCC_sync(TCC0);

//     TCC0->CTRLA.reg = 
//     (
//         TCC_CTRLA_PRESCALER_DIV2 | 
//         TCC_CTRLA_PRESCSYNC_PRESC
//     );

//     TCC0->WAVE.reg |= TCC_WAVE_WAVEGEN_NPWM;

//     TCC_set_period(TCC0, 6000);

//     // default output matrix configuration (pg. 1829)
//     TCC0->WEXCTRL.reg |= TCC_WEXCTRL_OTMX(0x00);

//     for(uint8_t i=0; i < 6; i++)
//     {
//         TCC0->CC[i].reg |= TCC_CC_CC(6000/2);
//     }

//     /*
//      * Peripheral function "F"
//      *
//      * CC0 -> PC16 (D25), 
//      * CC1 -> PC17 (D24)
//      * CC2 -> PC18 (D2)
//      * CC3 -> PC19 (D3)
//      * CC4 -> PC20 (D4)
//      * CC5 -> PC21 (D5)
//      */
// }

// void dstack_b_init(void)
// {
//     //ML_SET_GCLK7_PCHCTRL(TCC0_GCLK_ID);

//     TCC_DISABLE(TCC1);
//     TCC_SWRST(TCC1);
//     TCC_sync(TCC1);

//     TCC1->CTRLA.reg = 
//     (
//         TCC_CTRLA_PRESCALER_DIV2 | 
//         TCC_CTRLA_PRESCSYNC_PRESC
//     );

//     TCC1->WAVE.reg |= TCC_WAVE_WAVEGEN_NPWM;

//     TCC_set_period(TCC1, 6000);

//     // default output matrix configuration (pg. 1829)
//     TCC1->WEXCTRL.reg |= TCC_WEXCTRL_OTMX(0x00);

//     for(uint8_t i=0; i < 6; i++)
//     {
//         TCC1->CC[i].reg |= TCC_CC_CC(6000/2);
//     }

//     /*
//      * Peripheral function "F"
//      *
//      * CC0 -> PA16 (D37), 
//      * CC1 -> PA17 (D36)
//      * CC2 -> PA18 (D35)
//      * CC3 -> PA19 (D34)
//      * CC4 -> PA20 (D33)
//      * CC5 -> PA21 (D32)
//      */
// }



// void setup(void)
// {

//     //Serial.begin(9600);
//     //while(!Serial);

//     MCLK_init();
//     GCLK_init();

//     dstack_a_init();
//     TCC_ENABLE(TCC0);
//     TCC_sync(TCC0);

//     dstack_b_init();
//     TCC_ENABLE(TCC1);
//     TCC_sync(TCC1);

//     eic_init();
//     encoder_extint_init();
//     eic_enable();

//     for(uint8_t i=0; i < N_MOTORS; i++)
//     {
//         peripheral_port_init(&stack_pin_map[i].encoder_a);
//         peripheral_port_init(&stack_pin_map[i].encoder_b);
//         peripheral_port_init(&stack_pin_map[i].phase);
//         peripheral_port_init(&stack_pin_map[i].drive);

//         if(i % 2 == 0)
//         {
//             motor_set_speed(&stack_pin_map[i], 5500);
//         } else
//         {
//             motor_set_speed(&stack_pin_map[i], 5500);
//         }

//         // logical_set(&stack_pin_map[i].phase);
//         motor_set_direction(&stack_pin_map[i], OFF);
//     }

//     //logical_set(&stack_pin_map[0].phase);

//     //logical_toggle(&stack_pin_map[1].phase);

//     //logical_set(&stack_pin_map[2].phase);
//     //logical_unset(&stack_pin_map[2].phase);

//     //ml_pin_settings tmp = stack_pin_map[0].phase;
//     //PORT->Group[tmp.group].OUTSET.reg |= (1 << PORT_OUTSET_OUTSET(tmp.pin));
// }

// static boolean extint_10_intflag = false;
// static boolean extint_11_intflag = false;
// static boolean extint_12_intflag = false;
// static boolean extint_13_intflag = false;
// static boolean extint_14_intflag = false;
// static boolean extint_15_intflag = false;

// void loop(void)
// {
//     static byte position_idx = 1;

//     if(extint_10_intflag)
//     {
//         encoder_tick(&stack_pin_map[2]);
//         extint_10_intflag = false;
//     }

//     if(extint_11_intflag)
//     {
//         encoder_tick(&stack_pin_map[2]);
//         extint_11_intflag = false;
//     }

//     if(extint_12_intflag)
//     {
//         encoder_tick(&stack_pin_map[0]);
//         extint_12_intflag = false;
//     }

//     if(extint_13_intflag)
//     {
//         encoder_tick(&stack_pin_map[0]);
//         extint_13_intflag = false;
//     }

//     if(extint_14_intflag)
//     {
//         encoder_tick(&stack_pin_map[1]);
//         extint_14_intflag = false;
//     }

//     if(extint_15_intflag)
//     {
//         encoder_tick(&stack_pin_map[1]);
//         extint_15_intflag = false;
//     }

//     motor_pid_control_loop(&stack_pin_map[0], positions[position_idx]);
//     // motor_pid_control_loop(&stack_pin_map[1], positions[position_idx]);
//     // motor_pid_control_loop(&stack_pin_map[2], positions[position_idx]);

//     // bool isSteady = pid_steady_state(&stack_pin_map[0].pid_ctrl);
    
//     // if (isSteady)
//     // {
//     //     position_idx = (position_idx + 1) % NUM_POSITIONS;
//     // }
// }

// void EIC_10_Handler(void)
// {
//     EIC_CLR_INTFLAG(10);
//     extint_10_intflag = true;
// }

// void EIC_11_Handler(void)
// {
//     EIC_CLR_INTFLAG(11);
//     extint_11_intflag = true;
// }

// void EIC_12_Handler(void)
// {
//     EIC_CLR_INTFLAG(12);
//     extint_12_intflag = true;
// }

// void EIC_13_Handler(void)
// {
//     EIC_CLR_INTFLAG(13);
//     extint_13_intflag = true;
// }

// void EIC_14_Handler(void)
// {
//     EIC_CLR_INTFLAG(14);
//     extint_14_intflag = true;
// }

// void EIC_15_Handler(void)
// {
//     EIC_CLR_INTFLAG(15);
//     extint_15_intflag = true;
// }