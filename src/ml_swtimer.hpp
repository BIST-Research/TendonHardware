/*
 * Author: Ben Westcott
 * Date created: 7/29/23
 */
#ifndef ML_SWTIMER_H
#define ML_SWTIMER_H

#include <Arduino.h>
#include <ml_port.h>
#include <ml_tc.h>
typedef struct
{
    Tc *swtimer_inst;

} ml_swtimer;

uint64_t swtimer_elapsed_ms(ml_swtimer* timer);

#endif