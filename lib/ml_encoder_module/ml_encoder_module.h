/*
 * Author: Jayson De La Vega
 * Date created: 8/7/23
 * 
 * Description: An encoder object written using the Active Object framework
 * 
 * Modified 8/9/23 - Moved ML_Encoder_dispatch() to ml_encoder_module.c
 *                   to make it private
 * 
 * Modified 8/10/23- Implemented a new constructor ML_Encoder() and fixed
 *                   bugs related to callback.
 */
#ifndef ML_ENCODER_MODULE_H
#define ML_ENCODER_MODULE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <ml_active_object.h>
#include <ml_port.h>
#include <ml_tcc.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum {
    TICK_SIG = USER_SIG,
} Encoder_EventSignals;

typedef void (*ML_Encoder_stateChangeCallback)(int32_t count, void * instance);

typedef struct {
    Active super;

    // private data
    ml_pin_settings encoder_a;
    const ml_pin_settings encoder_b;

    int16_t ticks;
    int8_t last_encoded;
    
    // Observer
    ML_Encoder_stateChangeCallback callback;
    void*                          observer;
} ML_Encoder_t;

// task stack
// static Event *ml_encoder_queue[10];
// static ML_Encoder_t encoder;
// Active *AO_ML_Encoder = &encoder.super;

/**
 * @brief Enables all external interrupts for encoders. You must call this function to use pin external interrupts.
 */
void ML_Encoder_extint_init();

// /**
//  * @brief Constructs an encoder active object. Calling this function does not start an encoder task.
//  *         To start the encoder task, you must call Active_start() using the encoder object's super class.
//  * 
//  * @param me A pointer to the ML_Encoder active object
//  */
// void ML_Encoder_ctor(ML_Encoder_t * const me);

/**
 * @brief Constructs an encoder active object. Calling this function does not start an encoder task.
 *          To start the encoder task, you must call ML_Encoder_start().
 * 
 * @param encA A ml_pin_settings object for the encoder's phase A pin
 * @param encB A ml_pin_settings object for the encoder's phase B pin
 */
ML_Encoder_t ML_Encoder(ml_pin_settings encA, ml_pin_settings encB);

/**
 * @brief Provides a method to register a single external observer of the encoder state 
 * 
 * @param me A pointer to the ML_Encoder active object
 * @param callback A pointer to the callback function
 * @param instance An optional pointer to the active object that observes the state of the encoder
 */ 
void ML_Encoder_register_stateChangeCallback(ML_Encoder_t * const me, ML_Encoder_stateChangeCallback callback, void* instance);

/**
 * @brief Starts an encoder active object task.
 * 
 * @param me A pointer to the ML_Encoder active object
 * @param priority The FreeRTOS priority initially assigned to this task
 * @param queuelen The length of the task's event queue
 */
void ML_Encoder_start(ML_Encoder_t * const me, uint8_t priority, uint32_t queuelen);

#ifdef __cplusplus
}
#endif

#endif