

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


u8 WriteConfigurationBlock(void)
{
  // load all of the config RAM registers into one big array
  
  ConfigData[0] = BOARDCONFIG_ram;
  
  ConfigData[1] = MIDI0MODE_ram;  ConfigData[2] = MIDI1MODE_ram;  ConfigData[3] = MIDI2MODE_ram;
  ConfigData[4] = MIDI3MODE_ram;  ConfigData[5] = MIDI4MODE_ram;  ConfigData[6] = MIDI5MODE_ram;
  ConfigData[7] = MIDI6MODE_ram;  ConfigData[8] = MIDI7MODE_ram;  ConfigData[9] = MIDI8MODE_ram;
  ConfigData[10] = MIDI9MODE_ram;  ConfigData[11] = MIDI10MODE_ram;  ConfigData[12] = MIDI11MODE_ram;
  ConfigData[13] = MIDI12MODE_ram;  ConfigData[14] = MIDI13MODE_ram;
  
  ConfigData[14] = MIDI0POL_ram;  ConfigData[15] = MIDI1POL_ram;  ConfigData[16] = MIDI2POL_ram;
  ConfigData[17] = MIDI3POL_ram;  ConfigData[18] = MIDI4POL_ram;  ConfigData[19] = MIDI5POL_ram;
  ConfigData[20] = MIDI6POL_ram;  ConfigData[21] = MIDI7POL_ram;  ConfigData[22] = MIDI8POL_ram;
  ConfigData[23] = MIDI9POL_ram;  ConfigData[24] = MIDI10POL_ram;  ConfigData[25] = MIDI11POL_ram;
  ConfigData[26] = MIDI12POL_ram;  ConfigData[26] = MIDI13POL_ram;
  
  ConfigData[27] = MIDI0SENS_ram;  ConfigData[28] = MIDI1SENS_ram;  ConfigData[29] = MIDI2SENS_ram;
  ConfigData[30] = MIDI3SENS_ram;  ConfigData[31] = MIDI4SENS_ram;  ConfigData[32] = MIDI5SENS_ram;
  ConfigData[33] = MIDI6SENS_ram;  ConfigData[34] = MIDI7SENS_ram;  ConfigData[35] = MIDI8SENS_ram;
  ConfigData[36] = MIDI9SENS_ram;  ConfigData[37] = MIDI10SENS_ram;  ConfigData[38] = MIDI11SENS_ram;
  ConfigData[39] = MIDI12SENS_ram;  ConfigData[40] = MIDI13SENS_ram;
 
  ConfigData[58] = MIDI0NOTE_ram;  ConfigData[59] = MIDI1NOTE_ram;  ConfigData[60] = MIDI2NOTE_ram;
  ConfigData[61] = MIDI3NOTE_ram;  ConfigData[62] = MIDI4NOTE_ram;  ConfigData[63] = MIDI5NOTE_ram;
  ConfigData[64] = MIDI6NOTE_ram;  ConfigData[65] = MIDI7NOTE_ram;  ConfigData[66] = MIDI8NOTE_ram;
  ConfigData[67] = MIDI9NOTE_ram;  ConfigData[68] = MIDI10NOTE_ram;  ConfigData[69] = MIDI11NOTE_ram;
  ConfigData[70] = MIDI12NOTE_ram;  ConfigData[71] = MIDI13NOTE_ram;    
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
    dataaddress = &ConfigData[j];
    
    data = (uint32_t)*(dataaddress + j);
    
    FLASHStatus = FLASH_ProgramWord(flashAddress + j, data);
    
  }
  
  FLASH_LockBank1();
  
  
  
  
  return OK;
}


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


