/*
 * Author: Jayson De La Vega
 * Date created: 8/7/23
 * 
 * Description: An active object super class
 */
#include <ml_active_object.h>
#include <assert.h>

#include <Arduino.h>

static void Active_eventLoop(void *pdata)
{
    Active *me = (Active *)pdata;   // pointer to AO instance

    static Event const initEvt = { INIT_SIG };
    (*me->dispatch)(me, &initEvt);

    while (1) {
        Event e;
        // uint8_t err;

        // block until event received
        bool ok = xQueueReceive(me->s_eventQueue, &e, portMAX_DELAY);
        assert(ok);

        (*me->dispatch)(me, &e);
    }
}

Active Active_Object(DispatchHandler dispatch)
{
    Active ao = {};
    ao.dispatch = dispatch;

    return ao;
}

void Active_ctor(Active * me, DispatchHandler dispatch)
{
    me->dispatch = dispatch; // attach dispatch handler
}

void Active_start(Active * const me,
                  uint8_t prio,
                  uint32_t queueLen,
                  uint16_t opt)
{
    // uint8_t err;

    me->s_eventQueue = xQueueCreate(queueLen, sizeof(Event));
    assert(me->s_eventQueue);
    
    bool ok = xTaskCreate(Active_eventLoop, "Thing 2", 100, me, prio, &(me->s_thread));
    assert(ok);
}

void Active_post(Active * const me, Event const * const e)
{
    bool ok = xQueueSendToBack(me->s_eventQueue, e, 0);
    assert(ok);
}

void Active_postFromISR(Active * const me, Event const * const e, BaseType_t * xHigherPriorityTaskWoken)
{
    bool ok = xQueueSendToBackFromISR(me->s_eventQueue, e, xHigherPriorityTaskWoken);
    assert(ok);
}