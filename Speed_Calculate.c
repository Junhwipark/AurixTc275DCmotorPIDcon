#include "Speed_Calculate.h"
#include "Ifx_Types.h"
#include <math.h>

#define NUM_READINGS        10
#define ENCODER_PPR         100
#define WHEEL_DIAMETER_M    0.065f

volatile float32 deltaT = 0.01f;         /* 10 ms 샘플 */

static float32 readings[NUM_READINGS] = {0};
static sint32  total                  = 0;
static uint32  readIndex              = 0;

volatile float32 RPM_counter = 0.0f;
volatile float32 Speed_kmh   = 0.0f;
volatile float32 pidOutput   = 0.0f;
volatile float   Target_Speed = 0.0f;

extern volatile sint32 encoderPos;

/* PID 변수 */
static float integral_error = 0.0f;
static float prevFilt       = 0.0f;
static const float Kp  = 0.5f;
static const float Ki  = 0.000000010f;
static const float Kd  = 0.001f;
static const float fe_a = 1.0f / (2.0f * 3.14159265f);

void Counter_Calculate(void)
{
    static sint32 prevPos = 0;
    sint32 delta = encoderPos - prevPos;
    prevPos      = encoderPos;

    total -= readings[readIndex];
    readings[readIndex] = (float32)delta;
    total += readings[readIndex];
    readIndex = (readIndex + 1U) % NUM_READINGS;

    float32 avg = (float32)total / NUM_READINGS;
    RPM_counter = (60.0f * avg) / (deltaT * ENCODER_PPR * 4.0f);
    Speed_kmh   = RPM_counter * WHEEL_DIAMETER_M * 3.14159265f * 60.0f / 1000.0f;
}

float compute_pid(float targetSpeed)
{
    float targetRPM = targetSpeed * 1000.0f /
                      (WHEEL_DIAMETER_M * 3.14159265f * 60.0f);
    float error     = targetRPM - RPM_counter;

    /* 적분 + 필터형 미분 */
    integral_error += error * deltaT;
    float filt = prevFilt + (deltaT / fe_a) * (error - prevFilt);
    float deriv = (filt - prevFilt) / deltaT;
    prevFilt = filt;

    pidOutput = Kp * error + Ki * integral_error + Kd * deriv;
    return pidOutput;
}
