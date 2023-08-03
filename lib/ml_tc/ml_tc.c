/*
 * Author: Jayson De La Vega
 * Date created: 8/3/23
 */
#include <ml_tc.h>

TC0_init(void)
{

}

void TC_sync(Tc *instance)
{
    while(instance->COUNT16.SYNCBUSY.reg);
}

void TC_set_period(Tc *instance, uint32_t value);

void TC_channel_capture_compare_set(Tc *instance, const uint8_t channel, const uint8_t value);

void TC_intenset(Tc *instance, const IRQn_Type IRQn, const uint8_t interrupt_mask, const uint32_t priority_level);

void TC0_init(void)
{
    //disable TC
    
}