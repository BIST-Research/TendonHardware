/*
 * Authors: Ben Westcott, Jayson D
 * Date created: 7/31/23
 */

#include <ml_encoder.hpp>

void encoder_extint_init(void)
{
    EIC->CONFIG[0].reg = 
    (
        EIC_CONFIG_FILTEN0 |
        EIC_CONFIG_FILTEN1 |
        EIC_CONFIG_FILTEN2 |
        EIC_CONFIG_FILTEN3 |
        EIC_CONFIG_FILTEN4 |
        EIC_CONFIG_FILTEN5 |
        EIC_CONFIG_FILTEN6 |
        EIC_CONFIG_FILTEN7        
    );

    EIC->CONFIG[0].reg |= 
    (
        EIC_CONFIG_SENSE0_BOTH |
        EIC_CONFIG_SENSE1_BOTH |
        EIC_CONFIG_SENSE2_BOTH |
        EIC_CONFIG_SENSE3_BOTH |
        EIC_CONFIG_SENSE4_BOTH |
        EIC_CONFIG_SENSE5_BOTH |
        EIC_CONFIG_SENSE6_BOTH |
        EIC_CONFIG_SENSE7_BOTH
    );

    EIC->CONFIG[1].reg = 
    (
        EIC_CONFIG_FILTEN0 |
        EIC_CONFIG_FILTEN1 |
        EIC_CONFIG_FILTEN2 |
        EIC_CONFIG_FILTEN3 |
        EIC_CONFIG_FILTEN4 |
        EIC_CONFIG_FILTEN5 |
        EIC_CONFIG_FILTEN6 |
        EIC_CONFIG_FILTEN7        
    );

    EIC->CONFIG[1].reg |= 
    (
        EIC_CONFIG_SENSE0_BOTH |
        EIC_CONFIG_SENSE1_BOTH |
        EIC_CONFIG_SENSE2_BOTH |
        EIC_CONFIG_SENSE3_BOTH |
        EIC_CONFIG_SENSE4_BOTH |
        EIC_CONFIG_SENSE5_BOTH |
        EIC_CONFIG_SENSE6_BOTH |
        EIC_CONFIG_SENSE7_BOTH
    );

    EIC->INTENSET.reg = 
    (
        //EIC_INTENSET_EXTINT(0) | 
        //EIC_INTENSET_EXTINT(1) | 
        //EIC_INTENSET_EXTINT(2) | 
        //EIC_INTENSET_EXTINT(3) | 
        //EIC_INTENSET_EXTINT(4) | 
        //EIC_INTENSET_EXTINT(5) | 
        //EIC_INTENSET_EXTINT(6) | 
        //EIC_INTENSET_EXTINT(7) | 
        //EIC_INTENSET_EXINT(8) | 
        //EIC_INTENSET_EXTINT(9) | 
        //EIC_INTENSET_EXTINT(10) | 
        //EIC_INTENSET_EXTINT(11) | 
        EIC_INTENSET_EXTINT(12) | 
        EIC_INTENSET_EXTINT(13)  
        //EIC_INTENSET_EXTINT(14) | 
        //EIC_INTENSET_EXTINT(15)
    );
}

void encoder_tick(ml_motor *set)
{
    uint8_t a_phase = (uint8_t)logical_read(&set->encoder_a);
    uint8_t b_phase = (uint8_t)logical_read(&set->encoder_b);

    uint8_t current_encoded = (a_phase << 1) | b_phase;
    uint8_t sum = (set->last_encoded << 2) | current_encoded;

    switch(sum)
    {
        case 0b0001:
        case 0b0111:
        case 0b1110:
        case 0b1000:
        set->ticks--;
        break;
        case 0b0010:
        case 0b1011:
        case 0b1101:
        case 0b0100:
        set->ticks++;
        break;
    }
    set->last_encoded = current_encoded;
    
}




