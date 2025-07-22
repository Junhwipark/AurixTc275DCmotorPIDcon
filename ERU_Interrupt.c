#include "ERU_Interrupt.h"
#include "Board_Pins.h"
#include "IfxPort.h"

#define ISR_PRIORITY_SCUERU_INT0   40
#define ISR_PRIORITY_SCUERU_INT1   41

#define ENC_A_PORT   &MODULE_P33,7              /* Phase-A : P33.7 */
#define ENC_B_PORT   &MODULE_P15,4              /* Phase-B : P15.4 */

#define REQ_IN       &IfxScu_REQ8_P33_7_IN
#define REQ_IN2      &IfxScu_REQ0_P15_4_IN

ERUconfig g_ERUconfig;      /* A */
ERUconfig g_ERUconfig2;     /* B */

volatile sint32 encoderPos = 0;                 /* ± 위치 */

static inline void updateQuadFromA(void)
{
    if (IfxPort_getPinState(ENC_B_PORT) == 0)
        encoderPos++;
    else
        encoderPos--;
}
static inline void updateQuadFromB(void)
{
    if (IfxPort_getPinState(ENC_A_PORT) == 1)
        encoderPos++;
    else
        encoderPos--;
}

IFX_INTERRUPT(SCUERU_Int0_Handler, 0, ISR_PRIORITY_SCUERU_INT0);
IFX_INTERRUPT(SCUERU_Int1_Handler, 0, ISR_PRIORITY_SCUERU_INT1);

void SCUERU_Int0_Handler(void) { updateQuadFromA(); }
void SCUERU_Int1_Handler(void) { updateQuadFromB(); }

void initPeripheralsAndERU(void)
{
    /* A-채널 */
    g_ERUconfig.reqPin = REQ_IN;
    IfxScuEru_initReqPin(g_ERUconfig.reqPin, IfxPort_InputMode_pullDown);
    g_ERUconfig.inputChannel = (IfxScuEru_InputChannel)g_ERUconfig.reqPin->channelId;
    IfxScuEru_enableRisingEdgeDetection(g_ERUconfig.inputChannel);
    IfxScuEru_enableFallingEdgeDetection(g_ERUconfig.inputChannel);
    g_ERUconfig.outputChannel = IfxScuEru_OutputChannel_0;
    g_ERUconfig.triggerSelect = IfxScuEru_InputNodePointer_0;
    IfxScuEru_enableTriggerPulse(g_ERUconfig.inputChannel);
    IfxScuEru_connectTrigger(g_ERUconfig.inputChannel, g_ERUconfig.triggerSelect);
    IfxScuEru_setInterruptGatingPattern(g_ERUconfig.outputChannel,
                                        IfxScuEru_InterruptGatingPattern_alwaysActive);
    g_ERUconfig.src = &MODULE_SRC.SCU.SCU.ERU[(int)g_ERUconfig.outputChannel % 4];
    IfxSrc_init(g_ERUconfig.src, IfxSrc_Tos_cpu0, ISR_PRIORITY_SCUERU_INT0);
    IfxSrc_enable(g_ERUconfig.src);

    /* B-채널 */
    g_ERUconfig2.reqPin = REQ_IN2;
    IfxScuEru_initReqPin(g_ERUconfig2.reqPin, IfxPort_InputMode_pullDown);
    g_ERUconfig2.inputChannel = (IfxScuEru_InputChannel)g_ERUconfig2.reqPin->channelId;
    IfxScuEru_enableRisingEdgeDetection(g_ERUconfig2.inputChannel);
    IfxScuEru_enableFallingEdgeDetection(g_ERUconfig2.inputChannel);
    g_ERUconfig2.outputChannel = IfxScuEru_OutputChannel_2;
    g_ERUconfig2.triggerSelect = IfxScuEru_InputNodePointer_2;
    IfxScuEru_enableTriggerPulse(g_ERUconfig2.inputChannel);
    IfxScuEru_connectTrigger(g_ERUconfig2.inputChannel, g_ERUconfig2.triggerSelect);
    IfxScuEru_setInterruptGatingPattern(g_ERUconfig2.outputChannel,
                                        IfxScuEru_InterruptGatingPattern_alwaysActive);
    g_ERUconfig2.src = &MODULE_SRC.SCU.SCU.ERU[(int)g_ERUconfig2.outputChannel % 4];
    IfxSrc_init(g_ERUconfig2.src, IfxSrc_Tos_cpu0, ISR_PRIORITY_SCUERU_INT1);
    IfxSrc_enable(g_ERUconfig2.src);
}
