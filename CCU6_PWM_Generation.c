#include "IfxCcu6_PwmHl.h"
#include "IfxCpu.h"
#include "IfxPort.h"
#include "Board_Pins.h"
#include "CCU6_PWM_Generation.h"

/* ─ PWM 파라미터 ─ */
#define CCU6_BASE_FREQUENCY  100000000U
#define PWM_FREQUENCY        20000U
#define PWM_PERIOD           (CCU6_BASE_FREQUENCY / PWM_FREQUENCY)
#define NUMBER_OF_CHANNELS   2      /* CC60 dummy + CC61 실사용 */

/* CC60/COUT60  : P02.0 / P02.1 (사용 안함) */
#define PWM_CC0_PIN   &IfxCcu60_CC60_P02_0_OUT
#define PWM_COUT0_PIN &IfxCcu60_COUT60_P02_1_OUT
/* CC61/COUT61  : P02.7 / P02.3 (모터 드라이버 IN) */
#define PWM_CC1_PIN   &IfxCcu60_CC61_P02_7_OUT
#define PWM_COUT1_PIN &IfxCcu60_COUT61_P02_3_OUT

static IfxCcu6_TimerWithTrigger g_timer;
static IfxCcu6_PwmHl            g_driver;

static uint8 g_duty0 = 0;      /* CC60: 항상 0 % */
static uint8 g_duty1 = 50;     /* CC61: 초기 50 % */

extern volatile float32 pidOutput;

/* ─ CCU6 초기화 ─ */
void initCCU6(void)
{
    boolean intState = IfxCpu_disableInterrupts();

    /* 1. T12 타이머 설정 */
    IfxCcu6_TimerWithTrigger_Config tConf;
    IfxCcu6_TimerWithTrigger_initConfig(&tConf, &MODULE_CCU60);
    tConf.base.frequency = PWM_FREQUENCY;
    tConf.base.countDir  = IfxStdIf_Timer_CountDir_upAndDown;
    IfxCcu6_TimerWithTrigger_init(&g_timer, &tConf);

    /* 2. PWM High/Low 설정 */
    IfxCcu6_PwmHl_Config pConf;
    IfxCcu6_PwmHl_initConfig(&pConf);
    pConf.timer             = &g_timer;
    pConf.base.channelCount = NUMBER_OF_CHANNELS;
    pConf.cc0   = PWM_CC0_PIN;  pConf.cout0 = PWM_COUT0_PIN;
    pConf.cc1   = PWM_CC1_PIN;  pConf.cout1 = PWM_COUT1_PIN;

    IfxCcu6_PwmHl_init(&g_driver, &pConf);
    IfxCcu6_PwmHl_setMode(&g_driver, Ifx_Pwm_Mode_centerAligned);

    /* 3. 초기 듀티(채널0=0%, 채널1=g_duty1) */
    Ifx_TimerValue cmp[NUMBER_OF_CHANNELS];
    cmp[0] = (PWM_PERIOD / 100) * (100 - g_duty0);
    cmp[1] = (PWM_PERIOD / 100) * (100 - g_duty1);
    g_driver.update(&g_driver, cmp);
    IfxCcu6_TimerWithTrigger_applyUpdate(g_driver.timer);

    IfxCpu_restoreInterrupts(intState);
}

/* ─ DIR/BRAKE 핀 설정 및 방향 결정 ─ */
void initMotorDirectionPins(void)
{
    IfxPort_setPinModeOutput(DIR_PORT, DIR_PIN, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(BRK_PORT, BRK_PIN, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

    if (pidOutput >= 0.0f)
    {
        IfxPort_setPinHigh(DIR_PORT, DIR_PIN);
    }
    else
    {
        IfxPort_setPinLow(DIR_PORT, DIR_PIN);
        pidOutput = -pidOutput;   /* 듀티 계산용 절댓값 */
    }
    IfxPort_setPinLow(BRK_PORT, BRK_PIN);   /* 브레이크 해제 */
}

/* ─ PWM 스타트 ─ */
void startPWMGeneration(void)
{
    IfxCcu6_TimerWithTrigger_run(&g_timer);
}

/* ─ 듀티 갱신 ─ */
void updatePWMDutyCycle(uint8 dutyPercent)
{
    if (dutyPercent > 100) dutyPercent = 100;
    g_duty1 = dutyPercent;

    Ifx_TimerValue cmp[NUMBER_OF_CHANNELS];
    cmp[0] = (PWM_PERIOD / 100) * (100 - g_duty0);
    cmp[1] = (PWM_PERIOD / 100) * (100 - g_duty1);

    boolean intState = IfxCpu_disableInterrupts();
    g_driver.update(&g_driver, cmp);
    IfxCcu6_TimerWithTrigger_applyUpdate(g_driver.timer);
    IfxCpu_restoreInterrupts(intState);
}

/* ─ 모터 급브레이크 ─ */
void stopMotor(void)
{
    IfxPort_setPinHigh(BRK_PORT, BRK_PIN);
}