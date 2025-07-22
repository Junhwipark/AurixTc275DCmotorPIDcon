#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "Board_Pins.h"
#include "CCU6_PWM_Generation.h"
#include "ERU_Interrupt.h"
#include "GPT12_Timer_Interrupt.h"
#include "Speed_Calculate.h"
#include "ControlLoop.h"
#include <math.h>

IfxCpu_syncEvent g_cpuSyncEvent = 0;

extern volatile uint8   loop_cnt;
extern volatile float32 deltaT;

int core0_main(void)
{
    IfxCpu_enableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);
    initCCU6();
    initPeripheralsAndERU();
    initGpt12Timer();
    startPWMGeneration();
    IfxPort_setPinModeOutput(LOOP_CHECK_PORT, LOOP_CHECK_PIN,
                              IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(BRK_PORT, BRK_PIN);

    /* ─ 메인 루프 ─ */
    while (1)
    {
        if (loop_cnt >= 10U)
        {
            loop_cnt = 0U;
            ControlLoop();
        }
    }
    return 0;
}
