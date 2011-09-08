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
  
  // Go though each of the 14 channels to determine how to read them, read them, and update the state list.
  
  for(uint8_t i = 0; i<14; i++){
    uint8_t _mode = *(&MIDI0MODE + i);
    
    // Check the mode of the port to determine what you should do with it
    
    if(_mode = 0x00)     // Digital Mode
    {
      uint8_t _pol = = *(&MIDI0POL + i);  // load the polarity value into ram
      
      if((_pol)|(
      
      
    }
     
    else if(_mode = 0x00)     // Analog Mode
    {
      
    }

    else if(_mode = 0x00)     // Velocity Mode
    {
      
    }

    else if(_mode = 0x00)     // Analog Control Mode
    {
      
    }    
    
    
  }
  
  
  
  
  
  
  return OK;
}



extern u8 SendMessage(void)
{
  return OK;
}