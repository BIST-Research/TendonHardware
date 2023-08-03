/*
 * Author: Ben Westcott
 * Date created: 7/31/23
 */
#ifndef ML_ENCODER_H
#define ML_ENCODER_H

#include <Arduino.h>
#include <ml_motor.hpp>

/*
 * M0:
 *      enca: D40 --> PC13 --> EXTINT[13]
 *      encb: D41 --> PC12 --> EXTINT[12]
 * M1:
 *      enca: D42 --> PC15 --> EXTINT[15]
 *      encb: D43 --> PC14 --> EXTINT[14]
 * M2:
 *      enca: D44 --> PC11 --> EXTINT[11]
 *      encb: D45 --> PC10 --> EXTINT[10]
 * M3:
 *      enca: D46 --> PC06 --> EXTINT[6]
 *      encb: D47 --> PC07 --> EXTINT[9]
 * M4:
 *      enca: D48 --> PC04 --> EXTINT[4]
 *      encb: D49 --> PC05 --> EXTINT[5]
 * M5:
 *      enca: D30 --> PA23 --> EXTINT[7]
 *      encb: D51 --> PD08 --> EXTINT[3]
 * M6:
 *      enca: D52 --> PD09 --> EXTINT[4] (Conflict with PC04)
 *      encb: D53 --> PD10 --> EXTINT[5] (Conflict with PC05)
 * M7:
 *      enca: D38 --> PB15 --> EXTINT[15] (Conflict with PC15)
 *      encb: D39 --> PB14 --> EXTINT[14] (Conflict with PC14)
 * M8:
 *      enca: D8 --> PB18 --> EXTINT[2]
 *      encb: D31 --> PA22 --> EXTINT[6]
 * M9:
 *      enca: D12 --> PB00 --> EXTINT[0]
 *      encb: D29 --> PB19 --> EXTINT[3] (Conflict w/ PD08)
 * M10:
 *      enca: D26 --> PA12 --> EXTINT[12] (Conflict w/ C12)
 *      encb: D27 --> PA13 --> EXTINT[13] (Conflict w/ C13)
 * M11:
 *      enca: D22 --> PD12 --> EXTINT[7] (Conflict w/ A23)
 *      encb: D13 --> PB01 --> EXTINT[1]
 * 
 */

void encoder_extint_init(void);
void encoder_tick(ml_motor *set);

#endif