#ifndef ERU_INTERRUPT_H_
#define ERU_INTERRUPT_H_

#include "Ifx_Types.h"
#include "IfxSrc.h"
#include "IfxScuEru.h"

/* 구조체 그대로 */
typedef struct
{
    IfxScu_Req_In *reqPin;
    IfxScuEru_InputChannel inputChannel;
    IfxScuEru_InputNodePointer triggerSelect;
    IfxScuEru_OutputChannel outputChannel;
    volatile Ifx_SRC_SRCR *src;
} ERUconfig;

/* signed 위치 카운터 */
extern volatile sint32 encoderPos;

void initPeripheralsAndERU(void);

#endif
