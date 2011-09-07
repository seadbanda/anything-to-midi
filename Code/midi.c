// This file contains all of the Midi message and control funtions



#define STM32F10X_MD

#include "iostm32f100xB.h"
#include "stm32f10x_conf.h"
#include "globaldefinitions.h"
#include "GlobalDeclarations.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_RCC.h"
#include "stm32f10x_usart.h"
#include "misc.h"


/* u8 Midi_Note_Off(u8 _u8_channel, u8 _u8_note, u8 _u8_velocity)

Sends the midi Note Off comand 1000xxxx 0nnnnnnn 0vvvvvvv
returns OK if all is well

*/


extern u8 Midi_Note_Off(u8 _u8_channel, u8 _u8_note, u8 _u8_velocity){
  UART_Send(_u8_channel + 0x80);
  UART_Send(_u8_note);
  UART_Send(_u8_velocity);
  
  return OK;
}

/* u8 Midi_Note_On(u8 _u8_channel, u8 _u8_note, u8 _u8_velocity)

Sends the midi Note On comand 1001xxxx 0nnnnnnn 0vvvvvvv
returns OK if all is well

*/
extern u8 Midi_Note_On(u8 _u8_channel, u8 _u8_note, u8 _u8_velocity){
  UART_Send(_u8_channel + 0x90);
  UART_Send(_u8_note);
  UART_Send(_u8_velocity);
  
  return OK;
}

/* u8 Midi_Poly_Key_Pressure(u8 _u8_channel, u8 _u8_note, u8 _u8_velocity)

Sends the midi Polyphonic Key Pressure comand 1010xxxx 0nnnnnnn 0vvvvvvv
returns OK if all is well

*/
extern u8 Midi_Poly_Key_Pressure(u8 _u8_channel, u8 _u8_note, u8 _u8_velocity){
  UART_Send(_u8_channel + 0xA0);
  UART_Send(_u8_note);
  UART_Send(_u8_velocity);
  
  return OK;
}

/* u8 Midi_Control_Change(u8 _u8_channel, u8 _u8_controller, u8 _u8_value)

Sends the command to change the controller value 1011cccc 0ttttttt 0vvvvvvv
Controllers are things such as sustain pedals, leavers, faders and such. Things that are set and stay
the same for a while. 
tttttttt is the controller number, channel 120-127 are reserved for Channel Mode Message
*/
extern u8 Midi_Control_Change(u8 _u8_channel, u8 _u8_controller, u8 _u8_value){
  UART_Send(_u8_channel + 0xB0);
  UART_Send(_u8_controller);
  UART_Send(_u8_value);
  
  return OK;
}


/* u8 Midi_Program_Change(u8 _u8_channel, u8 _u8_program)

Used to send patch number changes 1100cccc 0ppppppp
used if you want to change the sound bank or synth patch you are using.

*/
extern u8 Midi_Program_Change(u8 _u8_channel, u8 _u8_program){
  UART_Send(_u8_channel + 0xC0);
  UART_Send(_u8_program);
  
  return OK;
}

/* Midi_Channel_Pressure(u8 _u8_channel, u8 _u8_pressure)

Sends the channel pressure message 1101cccc 0vvvvvvv
This is used for aftertouch on a keyboard, this is not used for contiuous controlled pressure
on something like a midi wind controller, for that use Polyphonic Key Pressure.
Only the greatest pressure of all of the depressed keys should be sent

*/
extern u8 Midi_Channel_Pressure(u8 _u8_channel, u8 _u8_pressure){
  UART_Send(_u8_channel + 0xD0);
  UART_Send(_u8_pressure);
  
  return OK;
}

/* u8 Midi_Pitch_Wheel(u8 _u8_channel, u16 _u16_value)

Sends the pitch wheel change command 1110cccc 0vvvvvvv 0vvvvvvv
Sends the 14bit value of the pitch wheel
This value is passed as a 16bit value, but is split into two 7 bit values and sent
as two 8 bit messages with leading 0s

*/
extern u8 Midi_Pitch_Wheel(u8 _u8_channel, u16 _u16_value){
  UART_Send(_u8_channel + 0xE0);
  u8 _u8_LB = _u16_value && 0x007F; // extract the lower bit
  u8 _u8_HB = (_u16_value && 0x3F800) / 128; // Note: the compiler knows this is a shift and not a divide
  UART_Send(_u8_LB);   // send the low bit first
  UART_Send(_u8_HB);   // send the high bit last
  
  return OK;
  
}


// Channel Mode Messages
extern u8 Midi_Sound_Off(u8 _u8_channel){
  return OK;
}


extern u8 Midi_Reset_All_Controllers(u8 _u8_channel){
  
  return OK;
  
}


extern u8 Midi_Local_Control(u8 _u8_channel){
  
  return OK;
  
}


extern u8 Midi_All_Notes_Off(u8 _u8_channel){
  
  return OK;
  
}