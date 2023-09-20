#include <FreeRTOS_SAMD51.h>

#include <ml_clocks.h>
#include <ml_tcc.h>
#include <ml_tc.h>
#include <ml_eic.h>

#include <ml_encoder_module.h>
#include <ml_motor_module.h>
#include <ml_active_object.h>

#define NUM_MOTORS  6

ML_Encoder_t enc[NUM_MOTORS] = {
    ML_Encoder(
        {PORT_GRP_C, 13, PMUX_DISABLE, PF_A, PP_ODD, INPUT_PULL_DOWN, DRIVE_OFF},
        {PORT_GRP_C, 12, PMUX_DISABLE, PF_A, PP_EVEN, INPUT_PULL_DOWN, DRIVE_OFF}
        ),
    ML_Encoder(
        {PORT_GRP_C, 12, PMUX_DISABLE, PF_A, PP_EVEN, INPUT_PULL_UP, DRIVE_OFF},
        {PORT_GRP_C, 13, PMUX_DISABLE, PF_A, PP_ODD, INPUT_PULL_UP, DRIVE_OFF}
        ),
    ML_Encoder(
        {PORT_GRP_C, 10, PMUX_DISABLE, PF_A, PP_EVEN, INPUT_PULL_DOWN, DRIVE_OFF},
        {PORT_GRP_C, 11, PMUX_DISABLE, PF_A, PP_ODD, INPUT_PULL_DOWN, DRIVE_OFF}
    ) 
};

ML_Motor_t m[NUM_MOTORS] = {
    ML_Motor(
        {PORT_GRP_B, 16, PMUX_DISABLE, PF_B, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},
        {PORT_GRP_C, 20, PMUX_ENABLE, PF_F, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},
        TCC0, 4, ML_HPCB_LV_75P1, ML_ENC_CPR
    ),
    ML_Motor(
        {PORT_GRP_B, 21, PMUX_DISABLE, PF_B, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},
        {PORT_GRP_C, 16, PMUX_ENABLE, PF_F, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},
        TCC0, 0, ML_HPCB_LV_75P1, ML_ENC_CPR
    ),
    ML_Motor(
        {PORT_GRP_B, 17, PMUX_DISABLE, PF_B, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},
        {PORT_GRP_C, 19, PMUX_ENABLE, PF_F, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},
        TCC0, 3, ML_HPCB_LV_75P1, ML_ENC_CPR
    ),
    // ML_Motor(
    //     {PORT_GRP_B, 13, PF_B, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},
    //     {PORT_GRP_C, 18, PF_F, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},
    //     TCC0, 2, ML_HPCB_LV_75P1, ML_ENC_CPR
    // ),
    // ML_Motor(
    //     {PORT_GRP_C, 23, PF_B, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},
    //     {PORT_GRP_C, 20, PF_F, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},
    //     TCC0, 4, ML_HPCB_LV_75P1, ML_ENC_CPR
    // ),
    // ML_Motor(
    //     {PORT_GRP_C, 22, PF_B, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},
    //     {PORT_GRP_C, 21, PF_F, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},
    //     TCC0, 5, ML_HPCB_LV_75P1, ML_ENC_CPR
    // ),
};


// ML_Encoder_t enc3 = {
//     {}, 
//     {PORT_GRP_C, 11, PF_A, PP_ODD, INPUT_PULL_DOWN, DRIVE_OFF},
//     {PORT_GRP_C, 10, PF_A, PP_EVEN, INPUT_PULL_DOWN, DRIVE_OFF},
//     0, 0, NULL};
// ML_Encoder_t * const enc3_ptr = &enc3;

// ML_Motor_t m3 = {
//     {},
//     {PORT_GRP_B, 13, PF_B, PP_ODD, OUTPUT_PULL_DOWN, DRIVE_ON},
//     {PORT_GRP_C, 18, PF_F, PP_EVEN, OUTPUT_PULL_DOWN, DRIVE_ON},
//     enc3_ptr,
//     {10.0, 0.0, 0.0, 500, 0, 0, 0, STEADY, 0},

//     TCC0, 0, ML_HPCB_LV_75P1, ML_ENC_CPR, 0
// };

void dstack_a_init(void)
{
    ML_SET_GCLK7_PCHCTRL(TCC0_GCLK_ID);

    TCC_DISABLE(TCC0);
    TCC_sync(TCC0);

    TCC0->CTRLA.reg = 
    (
        TCC_CTRLA_PRESCALER_DIV2 | 
        TCC_CTRLA_PRESCSYNC_PRESC
    );

    TCC0->WAVE.reg |= TCC_WAVE_WAVEGEN_NPWM;

    TCC_set_period(TCC0, 6000);

    // default output matrix configuration (pg. 1829)
    TCC0->WEXCTRL.reg |= TCC_WEXCTRL_OTMX(0x00);

    for(uint8_t i=0; i < 6; i++)
    {
        TCC0->CC[i].reg |= TCC_CC_CC(6000/2);
    }

    /*
     * Peripheral function "F"
     *
     * CC0 -> PC16 (D25), 
     * CC1 -> PC17 (D24)
     * CC2 -> PC18 (D2)
     * CC3 -> PC19 (D3)
     * CC4 -> PC20 (D4)
     * CC5 -> PC21 (D5)
     */
}

void dstack_b_init(void)
{
    //ML_SET_GCLK7_PCHCTRL(TCC0_GCLK_ID);

    TCC_DISABLE(TCC1);
    TCC_SWRST(TCC1);
    TCC_sync(TCC1);

    TCC1->CTRLA.reg = 
    (
        TCC_CTRLA_PRESCALER_DIV2 | 
        TCC_CTRLA_PRESCSYNC_PRESC
    );

    TCC1->WAVE.reg |= TCC_WAVE_WAVEGEN_NPWM;

    TCC_set_period(TCC1, 6000);

    // default output matrix configuration (pg. 1829)
    TCC1->WEXCTRL.reg |= TCC_WEXCTRL_OTMX(0x00);

    for(uint8_t i=0; i < 6; i++)
    {
        TCC1->CC[i].reg |= TCC_CC_CC(6000/2);
    }

    /*
     * Peripheral function "F"
     *
     * CC0 -> PA16 (D37), 
     * CC1 -> PA17 (D36)
     * CC2 -> PA18 (D35)
     * CC3 -> PA19 (D34)
     * CC4 -> PA20 (D33)
     * CC5 -> PA21 (D32)
     */
}

static void vPIDTimerCallback(xTimerHandle pxTimer) {
    // static bool started = false;

    // static bool dir = false;

    // int32_t id = (int32_t)pvTimerGetTimerID(pxTimer);

    // if (!started)
    // {
    //     Event e = {SET_PWM_SIG, 5500};
    //     Active_post(&(m[id].super), &e);

    //     started = true;
    // }
    // else
    // {
    //     Event e = {SET_DIR_SIG, OFF};
    //     if (dir) { e.param = CW; }
    //     else { e.param = CCW; }

    //     Active_post(&(m[id].super), &e);

    //     dir = !dir;
    // }

    int32_t id = (int32_t)pvTimerGetTimerID(pxTimer);

    Serial.print("Motor "); Serial.print(id); Serial.print(" position: "); Serial.print(m[id].ticks); Serial.print("\t"); Serial.println(m[id].pid.control_sig);

    Event e = {SET_TARGET_POS_SIG, 180};
    Active_post(&(m[id].super), &e);
}

void setup(void)
{
    // Initialize system clock
    MCLK_init();
    GCLK_init();

    // Initialize encoder interrupts
    eic_init();
    ML_Encoder_extint_init();
    eic_enable();

    vSetErrorLed(13, HIGH);

    dstack_a_init();
    TCC_ENABLE(TCC0);
    TCC_sync(TCC0);

    dstack_b_init();
    TCC_ENABLE(TCC1);
    TCC_sync(TCC1);

    // ========== Initialization Process ===========
    for (int i = 0; i < 1; ++i)
    {
        // Use FreeRTOS's software timers to periodically call PID
        xTimerHandle pidTimer = xTimerCreate("PID Timer", pdMS_TO_TICKS(50), pdTRUE, (void *)i, vPIDTimerCallback);
        if (pidTimer == NULL);
        else
        {
            if( xTimerStart(pidTimer, 0) != pdPASS ) while(1);
        }

        // ML_Encoder_register_stateChangeCallback(&(enc[i]), (ML_Encoder_stateChangeCallback)cb_func, NULL);
        ML_Encoder_start(&(enc[i]), 5, 20);

        ML_Motor_attachEncoder(&(m[i]), &(enc[i]));
        // Set PID parameters
        ML_Motor_setPIDParams(&(m[i]), 10.0, 2.0, 0.0, 50, 0);
        ML_Motor_start(&(m[i]), 2, 20);
    }
    // =============================================


    vTaskStartScheduler();

    while(1)
    {
        Serial.println("Scheduler Failed! \n");
        Serial.flush();
        delay(1000);
    }
}

void loop(void)
{

}

void EIC_6_Handler(void)
{
    EIC_CLR_INTFLAG(6);

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    static Event const e = {TICK_SIG};

    Active_postFromISR(&(enc[2].super), &e, &xHigherPriorityTaskWoken);

    if (xHigherPriorityTaskWoken)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void EIC_9_Handler(void)
{
    EIC_CLR_INTFLAG(9);

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    static Event const e = {TICK_SIG};

    Active_postFromISR(&(enc[2].super), &e, &xHigherPriorityTaskWoken);

    if (xHigherPriorityTaskWoken)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void EIC_10_Handler(void)
{
    EIC_CLR_INTFLAG(10);

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    static Event const e = {TICK_SIG};

    Active_postFromISR(&(enc[2].super), &e, &xHigherPriorityTaskWoken);

    if (xHigherPriorityTaskWoken)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void EIC_11_Handler(void)
{
    EIC_CLR_INTFLAG(11);

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    static Event const e = {TICK_SIG};

    Active_postFromISR(&(enc[2].super), &e, &xHigherPriorityTaskWoken);

    if (xHigherPriorityTaskWoken)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void EIC_12_Handler(void)
{
    EIC_CLR_INTFLAG(12);

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    static Event const e = {TICK_SIG};

    Active_postFromISR(&(enc[0].super), &e, &xHigherPriorityTaskWoken);

    if (xHigherPriorityTaskWoken)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void EIC_13_Handler(void)
{
    EIC_CLR_INTFLAG(13);

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    static Event const e = {TICK_SIG};

    Active_postFromISR(&(enc[0].super), &e, &xHigherPriorityTaskWoken);

    if (xHigherPriorityTaskWoken)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void EIC_14_Handler(void)
{
    EIC_CLR_INTFLAG(14);

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    static Event const e = {TICK_SIG};

    Active_postFromISR(&(enc[0].super), &e, &xHigherPriorityTaskWoken);

    if (xHigherPriorityTaskWoken)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void EIC_15_Handler(void)
{
    EIC_CLR_INTFLAG(15);

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    static Event const e = {TICK_SIG};

    Active_postFromISR(&(enc[0].super), &e, &xHigherPriorityTaskWoken);

    if (xHigherPriorityTaskWoken)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}