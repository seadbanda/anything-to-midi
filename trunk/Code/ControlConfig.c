

#define STM32F10X_MD

#include "iostm32f100xB.h"
#include "stm32f10x_conf.h"
#include "globaldefinitions.h"
#include "GlobalDeclarations.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_RCC.h"
#include "stm32f10x_usart.h"
#include "misc.h"

#define BANK1_WRITE_START_ADDR  ((uint32_t)0x08007800)
#define BANK1_WRITE_END_ADDR    ((uint32_t)0x08007C00)
#define FLASH_PAGE_SIZE         ((uint16_t)0x400)

// Ram variables for all of the configuration registers
// These will get loaded into flash when cofiguration is done

u8 BOARDCONFIG_ram;

u8 MIDI0MODE_ram; u8 MIDI1MODE_ram; u8 MIDI2MODE_ram; u8 MIDI3MODE_ram;
u8 MIDI4MODE_ram; u8 MIDI5MODE_ram; u8 MIDI6MODE_ram; u8 MIDI7MODE_ram;
u8 MIDI8MODE_ram; u8 MIDI9MODE_ram; u8 MIDI10MODE_ram; u8 MIDI11MODE_ram;
u8 MIDI12MODE_ram; u8 MIDI13MODE_ram;

u8 MIDI0POL_ram; u8 MIDI1POL_ram; u8 MIDI2POL_ram; u8 MIDI3POL_ram; 
u8 MIDI4POL_ram; u8 MIDI5POL_ram; u8 MIDI6POL_ram; u8 MIDI7POL_ram;
u8 MIDI8POL_ram; u8 MIDI9POL_ram; u8 MIDI10POL_ram; u8 MIDI11POL_ram;
u8 MIDI12POL_ram; u8 MIDI13POL_ram;

u8 MIDI0SENS_ram; u8 MIDI1SENS_ram; u8 MIDI2SENS_ram; u8 MIDI3SENS_ram;
u8 MIDI4SENS_ram; u8 MIDI5SENS_ram; u8 MIDI6SENS_ram; u8 MIDI7SENS_ram;
u8 MIDI8SENS_ram; u8 MIDI9SENS_ram; u8 MIDI10SENS_ram; u8 MIDI11SENS_ram;
u8 MIDI12SENS_ram; u8 MIDI13SENS_ram;

u8 MIDI0OFFSET_ram; u8 MIDI1OFFSET_ram;  u8 MIDI2OFFSET_ram; u8 MIDI3OFFSET_ram;
u8 MIDI4OFFSET_ram; u8 MIDI5OFFSET_ram; u8 MIDI6OFFSET_ram; u8 MIDI7OFFSET_ram;
u8 MIDI8OFFSET_ram; u8 MIDI9OFFSET_ram; u8 MIDI10OFFSET_ram; u8 MIDI11OFFSET_ram;
u8 MIDI12OFFSET_ram; u8 MIDI13OFFSET_ram;

uint8_t MIDI0CURVE_ram = 0; uint8_t MIDI1CURVE_ram = 0; uint8_t MIDI2CURVE_ram = 0;
uint8_t MIDI3CURVE_ram = 0; uint8_t MIDI4CURVE_ram = 0; uint8_t MIDI5CURVE_ram = 0;
uint8_t MIDI6CURVE_ram = 0; uint8_t MIDI7CURVE_ram = 0; uint8_t MIDI8CURVE_ram = 0;
uint8_t MIDI9CURVE_ram = 0; uint8_t MIDI10CURVE_ram = 0; uint8_t MIDI11CURVE_ram = 0;
uint8_t MIDI12CURVE_ram = 0; uint8_t MIDI13CURVE_ram = 0;


u8 MIDI0NOTE_ram; u8 MIDI1NOTE_ram; u8 MIDI2NOTE_ram; u8 MIDI3NOTE_ram; 
u8 MIDI4NOTE_ram; u8 MIDI5NOTE_ram; u8 MIDI6NOTE_ram; u8 MIDI7NOTE_ram; 
u8 MIDI8NOTE_ram; u8 MIDI9NOTE_ram; u8 MIDI10NOTE_ram; u8 MIDI11NOTE_ram; 
u8 MIDI12NOTE_ram; u8 MIDI13NOTE_ram; 

u8 ConfigData[72];




uint32_t EraseCounter = 0x00, Address = 0x00;
uint32_t Data = 0x3210ABCD;
uint32_t NbrOfPage = 0x00;

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
volatile TestStatus MemoryProgramStatus = PASSED;

uint8_t ConfigureChannelPins(u8 _channel, GPIO_TypeDef* _PrimaryPort, uint16_t _PrimaryPin, GPIO_TypeDef* _SecondaryPort, uint16_t _SecondaryPin, uint16_t _ADC_Channel)
{


  GPIO_InitTypeDef GPIO_InitStructure;      
  uint8_t _mode = (uint8_t)*(&MIDI0MODE + _channel);
    
  
  if(_mode == 0x00)     // Digital Mode
  {
    uint8_t _pol = (uint8_t)*(&MIDI0POL + _channel);  // load the polarity value into ram
 
    
    if (_pol == 0){
        GPIO_InitStructure.GPIO_Pin = _PrimaryPin;                                 // Configure the  Primary pin  
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                          // speed 50Mhz
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                              // configure input with pull up
        GPIO_Init(_PrimaryPort, &GPIO_InitStructure);                              // intialize on the primary port
    }
    
    else{
        GPIO_InitStructure.GPIO_Pin = _PrimaryPin;                                 // Configure the  Primary pin
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                          // speed 50Mhz
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;                              // configure input with pull down
        GPIO_Init(_PrimaryPort, &GPIO_InitStructure);                              // intialize on the primary port
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

extern u8 ConfigurePorts(void)
{
  
  // configure all the 14 channels
  
  ConfigureChannelPins(0, GPIOA, GPIO_Pin_0, GPIOA, GPIO_Pin_8, ADC_Channel_0);
  ConfigureChannelPins(1, GPIOA, GPIO_Pin_1, GPIOA, GPIO_Pin_11, ADC_Channel_1);
  ConfigureChannelPins(2, GPIOA, GPIO_Pin_2, GPIOA, GPIO_Pin_12, ADC_Channel_2);
  ConfigureChannelPins(3, GPIOA, GPIO_Pin_3, GPIOB, GPIO_Pin_12, ADC_Channel_3);
  ConfigureChannelPins(4, GPIOA, GPIO_Pin_4, GPIOB, GPIO_Pin_13, ADC_Channel_4);
  ConfigureChannelPins(5, GPIOA, GPIO_Pin_5, GPIOB, GPIO_Pin_14, ADC_Channel_5);
  ConfigureChannelPins(6, GPIOA, GPIO_Pin_6, GPIOB, GPIO_Pin_15, ADC_Channel_6);
  ConfigureChannelPins(7, GPIOA, GPIO_Pin_7, GPIOB, GPIO_Pin_2, ADC_Channel_7);
  ConfigureChannelPins(8, GPIOB, GPIO_Pin_0, GPIOB, GPIO_Pin_5, ADC_Channel_8);
  ConfigureChannelPins(9, GPIOB, GPIO_Pin_1, GPIOB, GPIO_Pin_6, ADC_Channel_9);
  ConfigureChannelPins(10, GPIOC, GPIO_Pin_0, GPIOB, GPIO_Pin_7, ADC_Channel_10);
  ConfigureChannelPins(11, GPIOC, GPIO_Pin_1, GPIOB, GPIO_Pin_8, ADC_Channel_11);
  ConfigureChannelPins(12, GPIOC, GPIO_Pin_2, GPIOB, GPIO_Pin_9, ADC_Channel_12);
  ConfigureChannelPins(13, GPIOC, GPIO_Pin_3, GPIOC, GPIO_Pin_6, ADC_Channel_13);

  return OK;
}

u8 WriteConfigurationBlock(void)
{
  // load all of the config RAM registers into one big array
  
  ConfigData[0] = BOARDCONFIG_ram;
  
  ConfigData[1] = MIDI0MODE_ram;  ConfigData[2] = MIDI1MODE_ram;  ConfigData[3] = MIDI2MODE_ram;
  ConfigData[4] = MIDI3MODE_ram;  ConfigData[5] = MIDI4MODE_ram;  ConfigData[6] = MIDI5MODE_ram;
  ConfigData[7] = MIDI6MODE_ram;  ConfigData[8] = MIDI7MODE_ram;  ConfigData[9] = MIDI8MODE_ram;
  ConfigData[10] = MIDI9MODE_ram;  ConfigData[11] = MIDI10MODE_ram;  ConfigData[12] = MIDI11MODE_ram;
  ConfigData[13] = MIDI12MODE_ram;  ConfigData[14] = MIDI13MODE_ram;
  
  ConfigData[15] = MIDI0POL_ram;  ConfigData[16] = MIDI1POL_ram;  ConfigData[17] = MIDI2POL_ram;
  ConfigData[18] = MIDI3POL_ram;  ConfigData[19] = MIDI4POL_ram;  ConfigData[20] = MIDI5POL_ram;
  ConfigData[21] = MIDI6POL_ram;  ConfigData[22] = MIDI7POL_ram;  ConfigData[23] = MIDI8POL_ram;
  ConfigData[24] = MIDI9POL_ram;  ConfigData[25] = MIDI10POL_ram;  ConfigData[26] = MIDI11POL_ram;
  ConfigData[27] = MIDI12POL_ram;  ConfigData[28] = MIDI13POL_ram;
  
  ConfigData[29] = MIDI0SENS_ram;  ConfigData[30] = MIDI1SENS_ram;  ConfigData[31] = MIDI2SENS_ram;
  ConfigData[32] = MIDI3SENS_ram;  ConfigData[33] = MIDI4SENS_ram;  ConfigData[34] = MIDI5SENS_ram;
  ConfigData[35] = MIDI6SENS_ram;  ConfigData[36] = MIDI7SENS_ram;  ConfigData[37] = MIDI8SENS_ram;
  ConfigData[38] = MIDI9SENS_ram;  ConfigData[39] = MIDI10SENS_ram;  ConfigData[40] = MIDI11SENS_ram;
  ConfigData[41] = MIDI12SENS_ram;  ConfigData[42] = MIDI13SENS_ram;
  
  ConfigData[43] = MIDI0CURVE_ram;  ConfigData[44] = MIDI1CURVE_ram;  ConfigData[45] = MIDI2CURVE_ram; 
  ConfigData[46] = MIDI3CURVE_ram;  ConfigData[47] = MIDI4CURVE_ram;  ConfigData[48] = MIDI5CURVE_ram; 
  ConfigData[49] = MIDI6CURVE_ram;  ConfigData[50] = MIDI7CURVE_ram;  ConfigData[51] = MIDI8CURVE_ram; 
  ConfigData[52] = MIDI9CURVE_ram;  ConfigData[53] = MIDI10CURVE_ram;  ConfigData[54] = MIDI11CURVE_ram; 
  ConfigData[55] = MIDI12CURVE_ram;  ConfigData[56] = MIDI13CURVE_ram;
   
  ConfigData[57] = MIDI0NOTE_ram;  ConfigData[58] = MIDI1NOTE_ram;  ConfigData[59] = MIDI2NOTE_ram;
  ConfigData[60] = MIDI3NOTE_ram;  ConfigData[61] = MIDI4NOTE_ram;  ConfigData[62] = MIDI5NOTE_ram;
  ConfigData[63] = MIDI6NOTE_ram;  ConfigData[64] = MIDI7NOTE_ram;  ConfigData[65] = MIDI8NOTE_ram;
  ConfigData[66] = MIDI9NOTE_ram;  ConfigData[67] = MIDI10NOTE_ram;  ConfigData[68] = MIDI11NOTE_ram;
  ConfigData[69] = MIDI12NOTE_ram;  ConfigData[70] = MIDI13NOTE_ram;
  
  
  FLASH_UnlockBank1();

  /* Define the number of page to be erased */
  NbrOfPage = (BANK1_WRITE_END_ADDR - BANK1_WRITE_START_ADDR) / FLASH_PAGE_SIZE;

  /* Clear All pending flags */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

  /* Erase the FLASH pages */
  for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
  {
    FLASHStatus = FLASH_ErasePage(BANK1_WRITE_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
  }
  
  // Write the blocks
    
    
  uint32_t flashAddress = 0x08007800;
  uint8_t *dataaddress = &ConfigData[0];
  uint32_t data;   
  dataaddress = &ConfigData[0];   
  
  
  for(u8 i = 0; i<18; i++){
    
    uint8_t j = i*4;
//    dataaddress = &ConfigData[j];
    
//    data = (uint32_t)*(dataaddress + j);
  
    data = ConfigData[j]+(ConfigData[j+1]*0x00000100)+(ConfigData[j+2]*0x00010000)+(ConfigData[j+3]*0x01000000);
    
    
    FLASHStatus = FLASH_ProgramWord(flashAddress + j, data);
    
  }
  
  FLASH_LockBank1();        // lock the Flash memory again
  
  
  
  ConfigurePorts();         // reconfigure the Ports any time you update the configuration
  
  return OK;
}



// Set a default configuration with all channels being in analog positive polarity mode.


extern u8 DefaultConfiguration(void)
{

  

  
  BOARDCONFIG_ram = 21;
  MIDI0MODE_ram = 0;  MIDI1MODE_ram = 0;  MIDI2MODE_ram = 0;  MIDI3MODE_ram = 0;
  MIDI4MODE_ram = 0;  MIDI5MODE_ram = 0;  MIDI6MODE_ram = 0;  MIDI7MODE_ram = 0;  
  MIDI8MODE_ram = 0;  MIDI9MODE_ram = 0;  MIDI10MODE_ram = 0;  MIDI11MODE_ram = 0;  
  MIDI12MODE_ram = 0;  MIDI13MODE_ram = 0;  
  
  MIDI0POL_ram = 1;  MIDI1POL_ram = 1;  MIDI2POL_ram = 1;  MIDI3POL_ram = 1;
  MIDI4POL_ram = 1;  MIDI5POL_ram = 1;  MIDI6POL_ram = 1;  MIDI7POL_ram = 1;
  MIDI8POL_ram = 1;  MIDI9POL_ram = 1;  MIDI10POL_ram = 1;  MIDI11POL_ram = 1;
  MIDI12POL_ram = 1;  MIDI13POL_ram = 1;
  
  MIDI0SENS_ram = 127;  MIDI1SENS_ram = 127;  MIDI2SENS_ram = 127;  MIDI3SENS_ram = 127;
  MIDI4SENS_ram = 127;  MIDI5SENS_ram = 127;  MIDI6SENS_ram = 127;  MIDI7SENS_ram = 127;
  MIDI8SENS_ram = 127;  MIDI9SENS_ram = 127;  MIDI10SENS_ram = 127;  MIDI11SENS_ram = 127;
  MIDI12SENS_ram = 127;  MIDI13SENS_ram = 127;  
  

  MIDI0NOTE_ram = 55;  MIDI1NOTE_ram = 56;  MIDI2NOTE_ram = 57;  MIDI3NOTE_ram = 58;
  MIDI4NOTE_ram = 59;  MIDI5NOTE_ram = 60;  MIDI6NOTE_ram = 61;  MIDI7NOTE_ram = 62;
  MIDI8NOTE_ram = 63;  MIDI9NOTE_ram = 64;  MIDI10NOTE_ram = 65;  MIDI11NOTE_ram = 66;
  MIDI12NOTE_ram = 67;  MIDI13NOTE_ram = 68;

  WriteConfigurationBlock();
  
  return OK;
}








