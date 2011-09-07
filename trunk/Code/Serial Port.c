// Contains all the code for implementing the Serial port

#define STM32F10X_MD

#include "iostm32f100xB.h"
#include "stm32f10x_conf.h"
#include "globaldefinitions.h"
#include "GlobalDeclarations.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_RCC.h"
#include "stm32f10x_usart.h"
#include "misc.h"



// Private Typedef

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
/* Define the variables that will be used only within this .c file
   Including the TX and RX bufferes and counters */

#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define TxBufferSize2   (countof(TxBuffer2) - 1)
#define DYMMY_BYTE      0x00

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
USART_InitTypeDef USART_InitStructure;
USART_ClockInitTypeDef USART_ClockInitStructure; 

uint8_t TxBuffer1[] = "USART Synchronous Example: USARTy -> SPIy using TXE and RXNE Flags";
uint8_t TxBuffer2[] = "USART Synchronous Example: SPIy -> USARTy using TXE and RXNE Flags";
uint8_t RxBuffer1[TxBufferSize2];
uint8_t RxBuffer2[TxBufferSize1];
__IO uint8_t NbrOfDataToRead1 = TxBufferSize2;
__IO uint8_t NbrOfDataToRead2 = TxBufferSize1;
__IO uint8_t TxCounter1 = 0, RxCounter1 = 0;
__IO uint8_t TxCounter2 = 0, RxCounter2 = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED; 


/* void Configure_UART()

This function configures the UART to 38400 baud and sets up the RCC config and GPIO configuration

*/

extern u8 Configure_UART(){
  
  
  
  // If the USB port is being used configure the serial port for USART3
  if(1){  
  
  // RCC Configuration
    /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(USART_USB_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

  /* Enable USARTy Clock */
  RCC_APB2PeriphClockCmd(USART_USB_CLK, ENABLE); 
  
  
  // GPIO Configuration. Configure USART TX pin as a Alternate fuction Push Pull and the RX as input floating
  
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure USARTy TX  pin as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = USART_USB_TxPin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(USART_USB_GPIO, &GPIO_InitStructure);  
  
   /* Configure USARTy RX as input floating */
  GPIO_InitStructure.GPIO_Pin = USART_USB_RxPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(USART_USB_GPIO, &GPIO_InitStructure); 
  
  
 
/* USARTy configuration ------------------------------------------------------*/
  /* USARTy configured as follow:
        - BaudRate = 38200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
        - USART Clock Disable
  */
  
  USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;
  USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Enable;
  USART_ClockInit(USART_USB, &USART_ClockInitStructure);

  USART_InitStructure.USART_BaudRate = 38200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART_USB, &USART_InitStructure);
  
  /* Configure the USARTy */
  USART_Init(USART_USB, &USART_InitStructure);

  /* Enable the USARTy */
  USART_Cmd(USART_USB, ENABLE);
  }
  
  
  
  
  
  
  return OK;
}


/* u8 UART_Send(u8* DataToSend, MessageLength)

Transmits a message
DataToSend is the data that is sent

Returns OK if the transmission is sucessful, NOK if it fails.

*/

extern u8 UART_Send(u8 DataToSend){
  
  while(USART_GetFlagStatus(USART_USB, USART_FLAG_TXE) == RESET);
  USART_SendData(USART_USB, DataToSend);
  
  return OK;
}


u8 Check_And_Recieve_UART(){
  if(USART_GetFlagStatus(USART_USB, USART_FLAG_RXNE) == SET)
    return USART_ReceiveData(USART_USB);
  else
    return NOK;
}




