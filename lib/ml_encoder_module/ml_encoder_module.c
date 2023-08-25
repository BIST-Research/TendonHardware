/*
 * Author: Jayson De La Vega
 * Date created: 8/7/23
 * 
 * Description: A motor object written using the Active Object framework
 * 
 * Modified 8/9/23 - Moved ML_Encode_dispatch() to this file and created
 *                   ML_Encoder_pin_init()
 * 
 * Modified 8/10/23- Implemented a new constructor ML_Encoder() and fixed
 *                   bugs related to callback.
 * 
 * Modified 8/16/23- Created a more optimized tick function
 */
#include <ml_encoder_module.h>
#include <FreeRTOS_SAMD51.h>

#include <Arduino.h>

// private function prototypes
static void ML_Encoder_dispatch (ML_Encoder_t * const me, Event const * const e);
static void ML_Encoder_pin_init (ML_Encoder_t * const me);
static void ML_Encoder_tick     (ML_Encoder_t * const me, uint8_t sig);

// Quadrature Encoder Matrix used to determine whether to increment or decrement encoder ticks
static int8_t QEM [16] = {0, -1,  1,  0,
                           1,  0,  0, -1,
                           -1, 0,  0,  1,
                           0,  1, -1,  0};

void ML_Encoder_extint_init()
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
        (1 << EIC_INTENSET_EXTINT(6))  | 
        //EIC_INTENSET_EXTINT(7) | 
        (1 << EIC_INTENSET_EXTINT(9))  | 
        (1 << EIC_INTENSET_EXTINT(10)) | 
        (1 << EIC_INTENSET_EXTINT(11)) | 
        (1 << EIC_INTENSET_EXTINT(12)) | 
        (1 << EIC_INTENSET_EXTINT(13)) | 
        (1 << EIC_INTENSET_EXTINT(14)) | 
        (1 << EIC_INTENSET_EXTINT(15))
    );

    NVIC_EnableIRQ(EIC_6_IRQn);
    NVIC_EnableIRQ(EIC_9_IRQn);
    NVIC_EnableIRQ(EIC_10_IRQn);
    NVIC_EnableIRQ(EIC_11_IRQn);
    NVIC_EnableIRQ(EIC_12_IRQn);
    NVIC_EnableIRQ(EIC_13_IRQn);
    NVIC_EnableIRQ(EIC_14_IRQn);
    NVIC_EnableIRQ(EIC_15_IRQn);

    NVIC_SetPriority(EIC_6_IRQn, 0xFF);
    NVIC_SetPriority(EIC_9_IRQn, 0xFF);
    NVIC_SetPriority(EIC_10_IRQn, 0xFF);
    NVIC_SetPriority(EIC_11_IRQn, 0xFF);
    NVIC_SetPriority(EIC_12_IRQn, 0xFF);
    NVIC_SetPriority(EIC_13_IRQn, 0xFF);
    NVIC_SetPriority(EIC_14_IRQn, 0xFF);
    NVIC_SetPriority(EIC_15_IRQn, 0xFF);
}

ML_Encoder_t ML_Encoder(ml_pin_settings encA, ml_pin_settings encB)
{
    ML_Encoder_t enc = {
        {},
        encA,
        encB,
        0, 0
    };

    Active_ctor(&(enc.super), (DispatchHandler)ML_Encoder_dispatch);

    return enc;
}

void ML_Encoder_start(ML_Encoder_t * const me, uint8_t priority, uint32_t queuelen)
{
    Active_start(&(me->super), priority, queuelen, 0);
}

// void ML_Encoder_ctor(ML_Encoder_t * const me)
// {
//     Active_ctor(&me->super, (DispatchHandler)&ML_Encoder_dispatch);
// }

void ML_Encoder_dispatch(ML_Encoder_t * const me, Event const * const e)
{
    switch (e->sig) {
        case INIT_SIG: {
            ML_Encoder_pin_init(me);
            break;
        }
        case TICK_SIG: {
            ML_Encoder_tick(me, e->param);
            break;
        }
        default: {
            break;
        }
    }
}

void ML_Encoder_pin_init(ML_Encoder_t * const me)
{
    // pin init function calls
    peripheral_port_init(&(me->encoder_a));
    peripheral_port_init(&(me->encoder_b));
}

void ML_Encoder_tick(ML_Encoder_t * const me, uint8_t sig)
{
    uint8_t a_phase = (uint8_t)(!logical_read(&me->encoder_a));
    uint8_t b_phase = (uint8_t)(!logical_read(&me->encoder_b));

    uint8_t current_encoded = (a_phase << 1) | b_phase;
    me->ticks += QEM[(me->last_encoded << 2) | current_encoded];
    me->last_encoded = current_encoded;
    
    (*me->callback)(me->ticks, me->observer);
}

void ML_Encoder_register_stateChangeCallback(ML_Encoder_t * const me, ML_Encoder_stateChangeCallback callback, void * instance)
{
    me->callback = callback;
    me->observer = instance;
}