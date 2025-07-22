#include "GPT12_Timer_Interrupt.h"
#include "Ifx_Types.h"
#include "IfxGpt12.h"
#include "IfxPort.h"

#define ISR_PRIORITY_GPT12_TIMER    6
#define ISR_PROVIDER_GPT12_TIMER    IfxSrc_Tos_cpu0
#define RELOAD_VALUE                100u

volatile uint8 loop_cnt = 0;


IFX_INTERRUPT(interruptGpt12, 0, ISR_PRIORITY_GPT12_TIMER);

void initGpt12Timer(void)
{
    IfxGpt12_enableModule(&MODULE_GPT120);
    IfxGpt12_setGpt1BlockPrescaler(&MODULE_GPT120, IfxGpt12_Gpt1BlockPrescaler_16);

    IfxGpt12_T3_setMode(&MODULE_GPT120, IfxGpt12_Mode_timer);
    IfxGpt12_T3_setTimerDirection(&MODULE_GPT120, IfxGpt12_TimerDirection_down);
    IfxGpt12_T3_setTimerPrescaler(&MODULE_GPT120, IfxGpt12_TimerInputPrescaler_64);
    IfxGpt12_T3_setTimerValue(&MODULE_GPT120, RELOAD_VALUE);

    IfxGpt12_T2_setMode(&MODULE_GPT120, IfxGpt12_Mode_reload);
    IfxGpt12_T2_setReloadInputMode(&MODULE_GPT120, IfxGpt12_ReloadInputMode_bothEdgesTxOTL);
    IfxGpt12_T2_setTimerValue(&MODULE_GPT120, RELOAD_VALUE);

    volatile Ifx_SRC_SRCR *src = IfxGpt12_T3_getSrc(&MODULE_GPT120);
    IfxSrc_init(src, ISR_PROVIDER_GPT12_TIMER, ISR_PRIORITY_GPT12_TIMER);
    IfxSrc_enable(src);

    IfxGpt12_T3_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
}

void interruptGpt12(void)
{
    loop_cnt++;
}
