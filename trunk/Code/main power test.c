
#define STM32F10X_MD

//#include "stm32f10x.h"
#include "iostm32f10xxB.h"
#include "stm32f10x_conf.h"
#include "globaldefinitions.h"
#include "GlobalDeclarations.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_gpio.c"
#include "stm32f10x_RCC.h"
#include "stm32f10x_RCC.c"
#include "stm32f10x_usart.h"
#include "stm32f10x_usart.c"
#include "misc.c"
#include "misc.h"


u32    g_u32_CurrentTimeLow;
u16    g_u16_CurrentTimeHigh;
u32    g_u32_TimeLow;
u16    g_u16_TimeHigh;
u8     g_u8_Seconds;
u8     _RTC_flags;

int main()
{
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  
  //RCC_APB2ENR = RCC_APB2ENR | BIT4 | BIT3 | BIT2 | BIT12 ;  // enable the clock for Port C and A and B  
  
  
  
  Configure_UART();
  while(1){
    
    //u8 _u8_RevievedByte = Check_And_Recieve_UART();

    
    Midi_Note_On(1, 20, 100);
    Midi_Note_Off(1, 20, 100);
    
  }
  
  
  
  
  
  
  
  
  
  
//  GPIO_InitTypeDef GPIO_InitStructure;  
//  
//  
//  // Set PWRON to Output Open Drain
//  
//  GPIO_InitStructure.GPIO_Pin = PWRON;                                          // Configure PWRON 
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                             // speed 50Mhz
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                              // configure 
//  GPIO_Init(PWRON_PORT, &GPIO_InitStructure);                                   // initalize the pins on PWRON_PORT port ( Port B )
//  
//
//  GPIO_SetBits(PWRON_PORT, PWRON);                                            // Set the PWRON pin, keeping the uC alive
//  
//  // setup the LED outputs
//  
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_13;                      // Configure the LED pins
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                             // speed 50Mhz
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                              // configure Out Push pull
//  GPIO_Init(GPIOC, &GPIO_InitStructure);                                        // initalize the pins on LED_PORT port ( Port B )
//  
//  GPIO_SetBits(GPIOC, GPIO_Pin_14);                                             // Turn on one of the LEDs
//  
//   
//  GPIO_SetBits(GPIOC, GPIO_Pin_13);                                             // Turn on the other LED

 
  
  
  while(1);
  return 0;
}

