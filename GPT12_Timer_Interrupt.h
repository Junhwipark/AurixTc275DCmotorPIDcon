/* GPT12_Timer_Interrupt.h -------------------------------------------- */
#ifndef GPT12_TIMER_INTERRUPT_H_
#define GPT12_TIMER_INTERRUPT_H_

#include "Ifx_Types.h"          /* uint8 정의 */

void initGpt12Timer(void);
void interruptGpt12(void);
extern volatile uint8 loop_cnt; /* ← 가드 내부, 함수 선언 다음 */

#endif /* GPT12_TIMER_INTERRUPT_H_ */
