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



//u16 _currentPin = 0x0001;
//GPIO_TypeDef* _currentPort = GPIOA;



uint8_t ReadChannel(u8 _channel, GPIO_TypeDef* _PrimaryPort, uint16_t _PrimaryPin, GPIO_TypeDef* _SecondaryPort, uint16_t _SecondaryPin, uint16_t _ADC_Channel, uint16_t _BitToUse)
{
  
  uint8_t _mode = (uint8_t)*(&MIDI0MODE + _channel);
  
  if(_mode == 0x00)     // Digital Mode
  {
    uint8_t _pol = (uint8_t)*(&MIDI0POL + _channel);  // load the polarity value into ram
    
    test = GPIO_ReadInputData(_PrimaryPort);
    test = (GPIO_ReadInputData(_PrimaryPort) | _PrimaryPin);
    test = ((_pol==1)&&(GPIO_ReadInputData(_PrimaryPort) & _PrimaryPin));
    test = (!(GPIO_ReadInputData(_PrimaryPort) & _PrimaryPin));
    test = ((!(_pol==1))&&(!(GPIO_ReadInputData(_PrimaryPort) & _PrimaryPin)));
    
    
    
    if(((_pol==1)&&(GPIO_ReadInputData(_PrimaryPort) & _PrimaryPin))||((!(_pol==1))&&(!(GPIO_ReadInputData(_PrimaryPort) & _PrimaryPin))))  // if the pol is 1 and the pin is one, or the pol is 0 and the pin is 0
    {
      if(CurrentNoteStatus & _BitToUse);             // check if the note is already on if it is, do nothing
        
      else{                                          // if it is not, start the note and set it
        Midi_Note_On(1, (uint8_t)*(&MIDI0NOTE + _channel), (uint8_t)*(&MIDI0SENS + _channel));        // start the note defined in the registers for this channel
        CurrentNoteStatus = CurrentNoteStatus | _BitToUse;                                 // set the current note to show that this note is on.       
      }
        
    }
    
    else
    {
      if(CurrentNoteStatus & _BitToUse){             // check if the note is already on if it is, stop it
         
        Midi_Note_Off(1, (uint8_t)*(&MIDI0NOTE + _channel), (uint8_t)*(&MIDI0SENS + _channel));        // stop the note defined in the registers for this channel
        CurrentNoteStatus = CurrentNoteStatus & !_BitToUse;                                             // reset the current note to show that this note is off.       
      }
      
      else;                                          // if it is not, don't do anything

                 
    }
       
  }
     
  else if(_mode == 0x00)     // Analog Mode
  {
    
  }

  else if(_mode == 0x00)     // Velocity Mode
  {
      
  }

  else if(_mode == 0x00)     // Analog Control Mode
  {
      
  }      
  
  
  return OK;
}





extern uint8_t ReadKeyboard(void)
{
  
  // Channel each of the 14 channels
  // Channel, Primary port, Primary Pin, Secondary Port, Secondary Pin, ADC channel
  
  ReadChannel(0, GPIOA, GPIO_Pin_0, GPIOA, GPIO_Pin_8, ADC_Channel_0, BIT0);
  ReadChannel(1, GPIOA, GPIO_Pin_1, GPIOA, GPIO_Pin_11, ADC_Channel_1, BIT1);
  ReadChannel(2, GPIOA, GPIO_Pin_2, GPIOA, GPIO_Pin_12, ADC_Channel_2, BIT2);
  ReadChannel(3, GPIOA, GPIO_Pin_3, GPIOB, GPIO_Pin_12, ADC_Channel_3, BIT3);
  ReadChannel(4, GPIOA, GPIO_Pin_4, GPIOB, GPIO_Pin_13, ADC_Channel_4, BIT4);
  ReadChannel(5, GPIOA, GPIO_Pin_5, GPIOB, GPIO_Pin_14, ADC_Channel_5, BIT5);
  ReadChannel(6, GPIOA, GPIO_Pin_6, GPIOB, GPIO_Pin_15, ADC_Channel_6, BIT6);
  ReadChannel(7, GPIOA, GPIO_Pin_7, GPIOB, GPIO_Pin_2, ADC_Channel_7, BIT7);
  ReadChannel(8, GPIOB, GPIO_Pin_0, GPIOB, GPIO_Pin_5, ADC_Channel_8, BIT8);
  ReadChannel(9, GPIOB, GPIO_Pin_1, GPIOB, GPIO_Pin_6, ADC_Channel_9, BIT9);
  ReadChannel(10, GPIOC, GPIO_Pin_0, GPIOB, GPIO_Pin_7, ADC_Channel_10, BIT10);
  ReadChannel(11, GPIOC, GPIO_Pin_1, GPIOB, GPIO_Pin_8, ADC_Channel_11, BIT11);
  ReadChannel(12, GPIOC, GPIO_Pin_2, GPIOB, GPIO_Pin_9, ADC_Channel_12, BIT12);
  ReadChannel(13, GPIOC, GPIO_Pin_3, GPIOC, GPIO_Pin_6, ADC_Channel_13, BIT13);



//  // Go though each of the 14 channels to determine how to read them, read them, and update the state list.
//  
//  u16 _currentPin;
//  
//  
//  for(uint8_t i = 0; i<14; i++){
//    uint8_t _mode = (uint8_t)*(&MIDI0MODE + i);
//    
//  
//    // Check the mode of the port to determine what you should do with it
//    
//    if(_mode == 0x00)     // Digital Mode
//    {
//      uint8_t _pol = (uint8_t)*(&MIDI0POL + i);  // load the polarity value into ram
//      
//      if(((_pol)|(GPIO_ReadInputData(_currentPort)|_currentPin))&&(!(_pol)|(!(GPIO_ReadInputData(_currentPort)|_currentPin))))  // if the pol is 1 and the pin is one, or the pol is 0 and the pin is 0
//      {
//        CurrentNoteStatus = CurrentNoteStatus | _currentPin;
//      }
//      else
//      {
//        CurrentNoteStatus = CurrentNoteStatus & (!_currentPin);
//      }
//      
//      
//      
//    }
//     
//    else if(_mode == 0x00)     // Analog Mode
//    {
//      
//    }
//
//    else if(_mode == 0x00)     // Velocity Mode
//    {
//      
//    }
//
//    else if(_mode == 0x00)     // Analog Control Mode
//    {
//      
//    }    
//        
//    
//    
//    // load the current pin value and current port values for the next interation
//    // on channel 8 and 10 we reset the current pin values and set the apropriate GPIO port. all others we mearly shift left
//    
//    if(i == 7){                       // 8 is coming up next
//      _currentPin = 0x0001;
//      _currentPort = GPIOB;
//    }  
//      
//    if(i == 9){                       // 10 is coming up next
//      _currentPin = 0x0001;
//      _currentPort = GPIOC;
//    }
//    
//    else{
//      _currentPin = _currentPin * 2;
//    }
//    
//  }
  
  
  
  
  
  
  return OK;
}



extern uint8_t SendMessage(void)
{
  return OK;
}