#ifndef CCU6_PWM_GENERATION_H_
#define CCU6_PWM_GENERATION_H_

#include "Ifx_Types.h"

void initCCU6(void);
void startPWMGeneration(void);
void updatePWMDutyCycle(uint8 dutyPercent);   /* 0–100 % */
void initMotorDirectionPins(void);
void stopMotor(void);

#endif /* CCU6_PWM_GENERATION_H_ */