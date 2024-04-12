#ifndef __HSM_LIB_H__
#define __HSM_LIB_H__

#include "AES.h"
#include "RNG.h"
#include "UART.h"
#include "LED.h"

void ClearScreen(void);
uint8_t ChooseOption(void);
void MenuFunction(void);
void InitialiseHSM(void);
void DisplayHSMBanner(void);

#endif
