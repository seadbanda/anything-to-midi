/* All the commands for configuring the MIDI channels are in here.
This code is written to resemble the code from the ST peripheral library from the outside
but inside here it is set up in a little more straightforward way (I think) */


/* Includes ------------------------------------------------------------------*/

#include "stm32f10x_gpio.c"






typedef struct
{
  
  uint8_t MIDI_IN_Mode;         // This member configures the mode of the channel
  
  uint8_t MIDI_IN_Polarity;     // This member sets the polarity of the Channel
  
  uint8_t MIDI_IN_Sensitivity;          // This member sets the sensitivity
  
  int8_t MIDI_IN_Curve;        // sets the curve value 
  
  int8_t MIDI_IN_Offset;       // sets the offset values
  
} MIDI_InitTypeDefIN;



typedef struct
{
  
  uint8_t MIDI_OUT_Mode;         // This member configures the mode of the channel
  
  uint8_t MIDI_OUT_Polarity;     // This member sets the polarity of the Channel
  
} MIDI_InitTypeDefIN;
