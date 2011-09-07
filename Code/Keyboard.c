// This file contains all of the funtions to read the inputs


#define STM32F10X_MD

#include "iostm32f100xB.h"
#include "stm32f10x_conf.h"
#include "globaldefinitions.h"
#include "GlobalDeclarations.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_RCC.h"
#include "stm32f10x_usart.h"
#include "misc.h"





extern u8 ReadKeyboard(void)
{
  return OK;
}



extern u8 SendMessage(void)
{
  return OK;
}