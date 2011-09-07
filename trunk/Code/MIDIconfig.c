/* All the commands for configuring the MIDI channels are in here. 

*/


/* Includes ------------------------------------------------------------------*/

#include "stm32f10x_gpio.c"





/* MIDI_IN_Setmode

Arguments: _Channel _Mode 
  _Channel is the input channel that is being configured
  _Mode is the mode it is being put in.

It returns OK if the mode is valid, NOK if it is invalid.

*/

uint8_t MIDI_Setmode(uint8_t _Channel, uint8_t _Mode){
  
  if(_Mode < 4)   // Check if the _Mode value matches that for the Digital mode
  {
    *(&MIDI0MODE = _Mode)
  }

  else
  {
    return NOK
  }
 
  return OK
}




