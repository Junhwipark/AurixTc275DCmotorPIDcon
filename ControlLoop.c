#include "ControlLoop.h"
#include "Board_Pins.h"
#include "Speed_Calculate.h"
#include "CCU6_PWM_Generation.h"
#include <math.h>

static float  time_sec = 0.0F;         /* 내부 상태 유지 */
static const float  freq = 0.1F;       /* 0.1 Hz */
static const float  amp  = 2.0F;       /* ±2 km/h */

#define M_PI 3.14159265358979323846f
extern volatile float32 deltaT;        /* GPT12 모듈에서 제공 */
volatile float target;
volatile float u;
/* ─ 10 ms 제어루프 ─ */
void ControlLoop(void)
{
     target = amp * sinf(2.0F * M_PI * freq * time_sec);

    Counter_Calculate();
     u = compute_pid(target);

    initMotorDirectionPins();

    uint8 duty;
    if (u <= 0.0F)       { duty = 0U;   }
    else if (u >= 100.0F){ duty = 100U; }
    else                 { duty = (uint8)u; }

    updatePWMDutyCycle(duty);
    IfxPort_togglePin(LOOP_CHECK_PORT, LOOP_CHECK_PIN);

    time_sec += deltaT;
}
