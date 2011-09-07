/* -----------------------------------------------
Implements the RTC procedures 

Communication with the RTC is with SPI port 1
SPI port 1 is reserverd especially for the RTC, SPI port 2 is used for memory and SPI based sensors.

Pins 
CS    -   Pin 20  - PA4
SCK   -   Pin 21  - PA5
MISO  -   Pin 22  - PA6
MOSI  -   Pin 23  - PA7

Dependencies: 
globaldefinitions.h   - definitions used throughout the LAT code
spi.h                 - definitions specific to the spi port (pins and what not) 
GlobalDeclarations.h  
stm32f10x_spi.c       - ST provided library for spi fuctions
stm32f10x_spi.h       - header for ST provided library for spi fuctions 
stm32f10x_gpio.c      - ST provided library for general purpose port fuctions
stm32f10x_gpio.h      - header for ST provided library for general purpose port fuctions


--------------------------------------------------*/

#define STM32F10X_MD
//#include "iostm32f10xxB.h"
#include "globaldefinitions.h"
#include "spi.h"
#include "GlobalDeclarations.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_spi.c"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_gpio.c"







SPI_InitTypeDef   SPI_InitStructure;



/* ----------------------------------------------------------------------------*/
/**  
  *\fn u8 Write_SPI( u8 _Address, u8 _Length, u8* pFirstByte )

*\brief   \b Brief: Set up the SPI port to talk to the RTC

*\details \b Description: Set the pin configuration for the SPI port. This function does not reset the pins configuration. Because the pins are not used anywhere else, no
other fuction should rewrite them so this function really only needs to be called once after powering up the micro. However, there is no harm in calling it multiple times as it is quite a fast 
fuction to execute.
The SPI port uses Port A pins 4-7. Pin 4 is CS, Pin 5 CLK, Pin 6 MISO, pin 7 MOSI 

  *\b Input:		None

  *\b Output:		None

  *\b Global/StaticData: none

*\return unsigned char : return OK if all goes well.

  *\b Assumptions:	none

  *\author Sam MacKenzie

  *\date April 24th 2011
  
  *\version 1.0

*/

u8   Config_SPI(void){
  
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure SPIy pins: SCK, MISO and MOSI ---------------------------------*/
  
  GPIO_InitStructure.GPIO_Pin = SPIy_PIN_SCK | SPIy_PIN_MOSI;                   // Configure SCK and MOSI pins ( Port A pins 5 and 7 ) 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                             // speed 50Mhz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                               // Confugure SCK and MOSI pins as Alternate Function Push Pull
  GPIO_Init(SPIy_GPIO, &GPIO_InitStructure);                                    // initalize the pins on SPIy_GPIO port ( Port A )

  GPIO_InitStructure.GPIO_Pin = SPIy_PIN_MISO;                                  // select the MISO port
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                         // Confugure MISO pin as Input Floating 
  GPIO_Init(SPIy_GPIO, &GPIO_InitStructure);                                    // initalize the pins on SPIy_GPIO port ( Port A )
  
  
  // Configure PB2 as the CS pin
  
  GPIO_InitStructure.GPIO_Pin = SPIy_PIN_CS;                                    // chose the CS pin to configure ( Port A pin 4 )
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                             // output speed up to 50Mhz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                              // configure as standard output mode, push pull configuration
  
  GPIO_Init(SPIy_CSPort, &GPIO_InitStructure);                                  // initalize the pin, on SPIy_CSPort ( Port A )
    
  // Set up the SPI communications

  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;            // SPI full duplex mode
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                                 // Make the uC the master
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                             // 8-bit Data size
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                                    // clock polarity, default low  
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                                  // read on first clock edge (high to low transition)  
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                                     // control chip select seperatly by software
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;           // baud rate = clock speed / 32 = 8Mhz /32 = 250khz
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                            // send data MSB to LSB
//  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPIy, &SPI_InitStructure);                                           // Iniitilize the SPI port
  
  SPI_Cmd(SPIy, ENABLE);                                                        // enable the SPI port
  
  return OK;  
}


/* ----------------------------------------------------------------------------*/
/**  
  *\fn u8 Write_SPI( u8 _Address, u8 _Length, u8* pFirstByte )

*\brief   \b Brief: Read from one or more registers in the RTC

*\details \b Description: Enter the register the length of the data you wish to read, and a pointer to the Ram location of where to store the contents of said register. Data you with to read from the RTC must be
sequential in RAM and sequential on the RTC or you will have to call this function multiple times. 

  *\b Input:		Address, Message Lenth

  *\b Output:		The data from the Register(s)



  *\b Global/StaticData: none

*\return unsigned char : return OK if all goes well.

  *\b Assumptions:	none

  *\author Sam MacKenzie

  *\date April 24th 2011
  
  *\version 1.0

*/


extern u8 Write_SPI( u8 _Address, u8 _Length, u8* pFirstByte )
{
  Config_SPI();                                                                 // set up the SPI port

  GPIO_SetBits(SPIy_CSPort, SPIy_PIN_CS);                                       // set the CS pin
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               // wait for the buffer to empty          
  SPI_I2S_SendData(SPIy, _Address + 0x10);                                      // transmit the address to write (second register) 

  for( u8 i = 0 ; i < _Length ; i++ )                                           // recieve however many bits as defined by the message length
  {  
    while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);             // wait for the buffer to empty             
    SPI_I2S_SendData(SPIy, *((u8 *)pFirstByte + i));                            // transmit the second data
  }
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_BSY) == SET);                 // wait for the port to finish output  
  GPIO_ResetBits(SPIy_CSPort, SPIy_PIN_CS);                                     // reset the CS pin 

  
  
  return OK;  
  
}


/* ----------------------------------------------------------------------------*/
/**  
  *\fn u8 Read_SPI( u8 _Address, u8 _Length, u8* pFirstByte )

*\brief   \b Brief: Write to one or more registers in the RTC

*\details \b Description: Enter the register the length of the data you wish to write, and a pointer to the Ram location of the data you wish to write. Data you with to write the RTC must be
sequential in RAM and sequential on the RTC or you will have to call this function multiple times. 

  *\b Input:		Address, Message Lenth, the data to write (as a pointer to Ram containing the data)

  *\b Output:		None



  *\b Global/StaticData: none

*\return unsigned char : return OK if all goes well.

  *\b Assumptions:	none

  *\author Sam MacKenzie

  *\date April 24th 2011
  
  *\version 1.0

*/

u8 Read_SPI( u8 _Address, u8 _Length, u8* pFirstByte )
{

  Config_SPI();                                                                 // set up the SPI port

  GPIO_SetBits(SPIy_CSPort, SPIy_PIN_CS);                                       // set the CS pin
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               // wait for the buffer to empty          
  SPI_I2S_SendData(SPIy, _Address + 0x90);                                      // transmit the address to write (second register) 

  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET);              // wait for data in the RX buffer  
  *((u8 *)pFirstByte + 0) = SPI_I2S_ReceiveData(SPIy);   
  
  for( u8 i = 0 ; i < _Length ; i++ )                                           // recieve however many bits as defined by the message length
  {
    
    while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);             // wait for the buffer to empty             
    SPI_I2S_SendData(SPIy, 0x00);                                               // transmit an empty frame
  
    while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET);            // wait for data in the RX buffer  
    *((u8 *)pFirstByte + i) = SPI_I2S_ReceiveData(SPIy);   
 
  }    
    
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_BSY) == SET);                 // wait for the port to finish output  
  GPIO_ResetBits(SPIy_CSPort, SPIy_PIN_CS);                                     // reset the CS pin   
  
  return OK;  
  
}


/* ----------------------------------------------------------------------------*/
/**  
  *\fn u8 Set_Time( u8* pu8_TimeLow, u8* pu8_TimeHigh )

*\brief   \b Brief: Write the date and time to the RTC

*\details \b Description: calls the write SPI funtion twice writing the Second, minute, hour and day registers first from RAM starting at the TimeLow location. Then the Month and Year registers from 
RAM starting at TimeHigh

  *\b Input:		4 bytes starting at TimeLow containing Second, Minute, Hour, Day (LS to MS)
2 bytes starting at TimeHigh containing Month and Year (LS to MS)

  *\b Output:		None



  *\b Global/StaticData: g_u32_CurrentTimeLow gets passed to u8_TimeLow,  g_u16_CurrentTimeHigh gets passed to pu8_TimeHigh;

*\return unsigned char : return OK if all goes well.

  *\b Assumptions:	none

  *\author Sam MacKenzie

  *\date April 24th 2011
  
  *\version 1.0

*/
extern u8 Set_Time( u8* pu8_TimeLow, u8* pu8_TimeHigh )
{

  Write_SPI( RTC_Seconds, 4, (u8 *)pu8_TimeLow );                               // Write the 4 low time bytes
  Write_SPI( RTC_Months, 2, (u8 *)pu8_TimeHigh );                               // Write the 2 high time bytes
  
  return OK;  
  
}
/* ----------------------------------------------------------------------------*/
/**  
  *\fn u8 Get_Time( u8* pu8_TimeLow, u8* pu8_TimeHigh )

*\brief   \b Brief: read the date and time from the RTC

*\details \b Description: calls the read SPI funtion twice reading the Second, minute, hour and day registers first and storing them in RAM starting at the TimeLow location. Then the Month and Year registers and storing 
them starting at TimeHigh

  *\b Input:		none

  *\b Output:		4 bytes starting at TimeLow containing Second, Minute, Hour, Day (LS to MS)
2 bytes starting at TimeHigh containing Month and Year (LS to MS)


  *\b Global/StaticData: g_u32_CurrentTimeLow gets passed to u8_TimeLow,  g_u16_CurrentTimeHigh gets passed to pu8_TimeHigh;

*\return unsigned char : return OK if all goes well.

  *\b Assumptions:	none

  *\author: Sam MacKenzie

  *\date: April 24th 2011
  
  *\version 1.0

*/

extern u8 Get_Time( u8* pu8_TimeLow, u8* pu8_TimeHigh )
{

  Read_SPI( RTC_Seconds, 4, (u8 *)pu8_TimeLow );                                // Write the 4 low time bytes
  Read_SPI( RTC_Months, 2, (u8 *)pu8_TimeHigh );                                // Write the 2 high time bytes
  
  return OK;  
  
}



/* ----------------------------------------------------------------------------*/
/**  
  *\fn u8 Second_Interrupt(void)

*\brief   \b Brief:	Sets the one second interrupt on the RTC

  *\details \b Description: Send the one second intterupt but to RTC control register 2 to turn on the one second interrupt

  *\b Input:		none

  *\b Output:		none

  *\b Global/StaticData: none

*\return unsigned char : return OK if all goes well.

  *\b Assumptions:	none

  *\author: Sam MacKenzie

  *\date: April 24th 2011
  
  *\version 1.0

*/

extern u8 Second_Interrupt(void){
  
//! <b> Documenting sequence in TIMER_INIT_ARGOS_MODULATION_TIMER2: </b>  <ul>
  Config_SPI();                                                                 //! <li> set up the SPI port

  GPIO_SetBits(SPIy_CSPort, SPIy_PIN_CS);                                       //! <li> set the CS pin
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               //! <li> wait for the buffer to empty          
  SPI_I2S_SendData(SPIy, RTC_CONTROL_2 + 0x10);                                 //! <li> transmit the address to write 
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               //! <li> wait for the buffer to empty             
  SPI_I2S_SendData(SPIy, RTC_C2_SI | RTC_C2_TI_TP);                                            //! <li> transmit the 1 second intterupt bit
  
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_BSY) == SET);                 //! <li> wait for the port to finish output  
  GPIO_ResetBits(SPIy_CSPort, SPIy_PIN_CS);                                     //! <li> reset the CS pin
  
  return OK;
}

extern u8 CLKOUT_1s(void){
  
  Config_SPI();                                                                 //! <li> set up the SPI port

  GPIO_SetBits(SPIy_CSPort, SPIy_PIN_CS);                                       //! <li> set the CS pin
      
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               //! <li> wait for the buffer to empty          
  SPI_I2S_SendData(SPIy, RTC_CLKOUT + 0x10);                                    //! <li> transmit the address (RTC clock out control reg) to write 
 
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               //! <li> wait for the buffer to empty
  SPI_I2S_SendData(SPIy, BIT6 | BIT5);                                          //! <li> transmit the bits to set the 1s out
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_BSY) == SET);                 //! <li> wait for the port to finish output  
  GPIO_ResetBits(SPIy_CSPort, SPIy_PIN_CS);                                     //! <li> reset the CS pin
   
  return OK;
}


/* ----------------------------------------------------------------------------*/
/**  
  *\fn u8 Set_Coundown_Time(u8 _CountdownTime)

*\brief   \b Brief:	

  *\details \b Description: 

  *\b Input:		u8 _CountdownTime, the time in seconds to count down before the intterupt.

  *\b Output:		none

  *\b Global/StaticData: none

*\return unsigned char : return OK if all goes well.

  *\b Assumptions:	none

  *\author: Sam MacKenzie

  *\date: April 24th 2011
  
  *\version 1.0

*/

extern u8 Set_Coundown_Time(u8 _CountdownTime){
  
  Config_SPI();                                                                 //! <li> set up the SPI port

  GPIO_SetBits(SPIy_CSPort, SPIy_PIN_CS);                                       //! <li> set the CS pin
      
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               //! <li> wait for the buffer to empty          
  SPI_I2S_SendData(SPIy, RTC_CLKOUT + 0x10);                                    //! <li> transmit the address (RTC_CLKOUT) to write 
 
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               //! <li> wait for the buffer to empty
  SPI_I2S_SendData(SPIy, BIT1);                                          //! <li> transmit the bits to set the countdown timer to 1s clock source
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               //! <li> wait for the buffer to empty
  SPI_I2S_SendData(SPIy, _CountdownTime);                                          //! <li> transmit the bits to set the countdown timer value
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_BSY) == SET);                 //! <li> wait for the port to finish output  
  GPIO_ResetBits(SPIy_CSPort, SPIy_PIN_CS);                                     //! <li> reset the CS pin
   
  return OK;
}

extern u8 Get_Coundown_Time(void){
  
  Config_SPI();                                                                 //! <li> set up the SPI port

  GPIO_SetBits(SPIy_CSPort, SPIy_PIN_CS);                                       //! <li> set the CS pin
      
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               //! <li> wait for the buffer to empty          
  SPI_I2S_SendData(SPIy, RTC_CLKOUT + 0x90);                                    //! <li> transmit the address (RTC_CLKOUT) to write 

  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET);              // wait for data in the RX buffer  
  u8 a = SPI_I2S_ReceiveData(SPIy);     
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               //! <li> wait for the buffer to empty
  SPI_I2S_SendData(SPIy, 0x00);                                                 //! <li> transmit the bits to set the countdown timer to 1s clock source

  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET);              // wait for data in the RX buffer  
  u8 _countdown_clock = SPI_I2S_ReceiveData(SPIy);   
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               //! <li> wait for the buffer to empty
  SPI_I2S_SendData(SPIy, 0x00);                                                 //! <li> transmit the bits to set the countdown timer value

  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET);              // wait for data in the RX buffer  
  u8 _countdown_time = SPI_I2S_ReceiveData(SPIy);   
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_BSY) == SET);                 //! <li> wait for the port to finish output  
  GPIO_ResetBits(SPIy_CSPort, SPIy_PIN_CS);                                     //! <li> reset the CS pin
   
  return _countdown_clock;
}

extern u8 Set_RTC_Register( u8 _address, u8 _data ){
  
  Config_SPI();                                                                 //! <li> set up the SPI port

  GPIO_SetBits(SPIy_CSPort, SPIy_PIN_CS);                                       //! <li> set the CS pin
      
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               //! <li> wait for the buffer to empty          
  SPI_I2S_SendData(SPIy, _address + 0x10);                                    //! <li> transmit the address of the register to write to
 
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               //! <li> wait for the buffer to empty
  SPI_I2S_SendData(SPIy, _data);                                                 //! <li> transmit the data to write to the register
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_BSY) == SET);                 //! <li> wait for the port to finish output  
  GPIO_ResetBits(SPIy_CSPort, SPIy_PIN_CS);                                     //! <li> reset the CS pin
   
  return OK; 
}


extern u8 Get_RTC_Register( u8 _address ){
  
  Config_SPI();                                                                 //! <li> set up the SPI port

  GPIO_SetBits(SPIy_CSPort, SPIy_PIN_CS);                                       //! <li> set the CS pin
      
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               //! <li> wait for the buffer to empty          
  SPI_I2S_SendData(SPIy, _address + 0x90);                                    //! <li> transmit the address to read from
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET);              // wait for data in the RX buffer  
  u8 a = SPI_I2S_ReceiveData(SPIy);     
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE) == RESET);               //! <li> wait for the buffer to empty
  SPI_I2S_SendData(SPIy, 0x00);                                                 //! <li> transmit an empty frame

  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE) == RESET);              // wait for data in the RX buffer  
  u8 _data = SPI_I2S_ReceiveData(SPIy);   
  
  while (SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_BSY) == SET);                 //! <li> wait for the port to finish output  
  GPIO_ResetBits(SPIy_CSPort, SPIy_PIN_CS);                                     //! <li> reset the CS pin
   
  return _data;
}