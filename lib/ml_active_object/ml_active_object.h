/*
 * Author: Jayson De La Vega
 * Date created: 8/7/23
 * 
 * Description: An active object super class
 */
#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <FreeRTOS_SAMD51.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Event Loop Facilities */
typedef uint16_t Signal;

enum {
    INIT_SIG,   // Reserved init signal
    USER_SIG    // Start of user signals
} ReservedSignals;

typedef struct {
    Signal sig;

    /* Event parameters */
    int32_t param;
} Event;

/* Active Object Facilities */

typedef struct Active Active;

typedef void (*DispatchHandler)(Active * me, Event const * const e);

struct Active {
    TaskHandle_t    s_thread;       // private thread
    QueueHandle_t   s_eventQueue;   // private queue

    DispatchHandler dispatch;       // pointer to dispatch() function
};

/**
 * @brief Constructs an active object. Calling this function does not start the task.
 * 
 * @param me A pointer to the active object.
 * @param dispatch The function that will define the main loop of this task.
 */
void Active_ctor(Active * const me, DispatchHandler dispatch);

/**
 * @brief Starts an active object task.
 * 
 * @param me A pointer to the active object to start.
 * @param prio The The FreeRTOS priority initially assigned to this task.
 * @param queuelen The length of the task's event queue.
 */
void Active_start(Active * const me,
                  uint8_t prio,
                  uint32_t queueLen,
                  uint16_t opt);

/**
 * @brief Post an event to an active object's queue.
 * 
 * @param me A pointer to the active object that will receive the event.
 * @param e A pointer to the event.
 */
void Active_post(Active * const me, Event const * const e);

/**
 * @brief Post an event to an active object's queue from inside an ISR.
 * 
 * @param me A pointer to the active object that will receive the event.
 * @param e A pointer to the event.
 * @param xHigherPriorityTaskWoken A pointer indicating if a higher priority task was woken from inside the interrupt
 */
void Active_postFromISR(Active * const me, Event const * const e, BaseType_t * xHigherPriorityTaskWoken);

#ifdef __cplusplus
}
#endif

#endif