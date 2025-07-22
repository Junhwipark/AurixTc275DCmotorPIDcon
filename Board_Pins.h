#ifndef BOARD_PINS_H_
#define BOARD_PINS_H_

#include "IfxPort.h"

/* Port/pin macro pairs for VX-toolset API (expects 4 args) */
#define LOOP_CHECK_PORT   &MODULE_P00
#define LOOP_CHECK_PIN    6U

#define DIR_PORT          &MODULE_P02
#define DIR_PIN           6U

#define BRK_PORT          &MODULE_P10
#define BRK_PIN           5U

#define ENC_A_PORT        &MODULE_P33
#define ENC_A_PIN         7U

#define ENC_B_PORT        &MODULE_P15
#define ENC_B_PIN         4U

#endif /* BOARD_PINS_H_ */