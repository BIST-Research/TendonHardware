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

void TC_sync(Tc *instance);

void TC_set_period(Tc *instance, uint32_t value);

void TC_channel_capture_compare_set(Tc *instance, const uint8_t channel, const uint8_t value);

void TC_intenset(Tc *instance, const IRQn_Type IRQn, const uint8_t interrupt_mask, const uint32_t priority_level);

#ifdef __cplusplus
}
#endif

#endif // ML_TC_H