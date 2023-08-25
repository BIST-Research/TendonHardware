/*
 * Author: Jayson De La Vega
 * Date created: 8/2/23
 */

#ifndef ML_TC_H
#define ML_TC_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    COUNT8_MODE, COUNT16_MODE, COUNT32_MODE
} TC_counterMode;

typedef enum
{
    PRE_16, PRE_256
} TC_prescaler;

typedef enum
{
    COUNT_UP, COUNT_DOWN
} TC_counterDir;

typedef enum
{
    MFREQ
} TC_wavegen_opt;

typedef struct
{
    Tc *instance;
    
    TC_counterMode  counterMode;
    TC_prescaler    prescaler;
    TC_counterDir   counterDir;
    TC_wavegen_opt  wavegen;

} TC_instance;

void TC_sync(Tc *instance);

void TC_set_period(Tc *instance, uint32_t value);

void TC_channel_capture_compare_set(Tc *instance, const uint8_t channel, const uint8_t value);

void TC_intenset(Tc *instance, const IRQn_Type IRQn, const uint8_t interrupt_mask, const uint32_t priority_level);

void TC_stop(Tc *instance);

void TC_retrigger(Tc *instance);

#ifdef __cplusplus
}
#endif

#endif // ML_TC_H