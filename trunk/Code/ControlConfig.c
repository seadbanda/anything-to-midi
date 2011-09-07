

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

u8 BOARDCONFIG_ram;
u8 MIDI0MODE_ram;
u8 MIDI1MODE_ram;
u8 MIDI2MODE_ram;
u8 MIDI3MODE_ram;
u8 MIDI4MODE_ram;
u8 MIDI5MODE_ram;
u8 MIDI6MODE_ram;
u8 MIDI7MODE_ram;
u8 MIDI8MODE_ram;
u8 MIDI9MODE_ram;
u8 MIDI10MODE_ram;
u8 MIDI11MODE_ram;
u8 MIDI12MODE_ram;
u8 MIDI13MODE_ram;

u8 ConfigData[32];




uint32_t EraseCounter = 0x00, Address = 0x00;
uint32_t Data = 0x3210ABCD;
uint32_t NbrOfPage = 0x00;

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
volatile TestStatus MemoryProgramStatus = PASSED;


u8 WriteConfigurationBlock(void)
{
  
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
  
  uint32_t data = (uint32_t)*dataaddress;
  
  FLASHStatus = FLASH_ProgramWord(flashAddress, data);
   
  
  FLASHStatus = FLASH_ProgramWord(flashAddress, data);
  
  
  data = (uint32_t)*(dataaddress + 4);
  
    
  FLASH_LockBank1();
  
  
  
  
  return OK;
}


extern u8 DefaultConfiguration(void)
{
  
  BOARDCONFIG_ram = 21;
  MIDI0MODE_ram = 0;
  MIDI1MODE_ram = 0;
  MIDI2MODE_ram = 0;
  MIDI3MODE_ram = 0;
  MIDI4MODE_ram = 0;
  MIDI5MODE_ram = 0;
  MIDI6MODE_ram = 0;
  MIDI7MODE_ram = 0;  
  MIDI8MODE_ram = 0;
  MIDI9MODE_ram = 0;
  MIDI10MODE_ram = 0;
  MIDI11MODE_ram = 0;  
  MIDI12MODE_ram = 0;
  MIDI13MODE_ram = 0;  
  
  ConfigData[0] = BOARDCONFIG_ram;
  ConfigData[1] = MIDI0MODE_ram;
  ConfigData[2] = MIDI1MODE_ram;
  ConfigData[3] = MIDI2MODE_ram;
  ConfigData[4] = MIDI3MODE_ram;
  ConfigData[5] = MIDI4MODE_ram;
  ConfigData[6] = MIDI5MODE_ram;
  ConfigData[7] = MIDI6MODE_ram;
  ConfigData[8] = MIDI7MODE_ram;
  ConfigData[9] = MIDI8MODE_ram;
  ConfigData[10] = MIDI9MODE_ram;
  ConfigData[11] = MIDI10MODE_ram;
  ConfigData[12] = MIDI11MODE_ram;
  ConfigData[13] = MIDI12MODE_ram;
  ConfigData[14] = MIDI13MODE_ram;
  
  WriteConfigurationBlock();
  
  return OK;
}


