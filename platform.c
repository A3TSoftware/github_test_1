/***********************************************************************************************************************
    @file    platform.c
    @author  FAE Team
    @date    18-Apr-2023
    @brief   THIS FILE PROVIDES ALL THE SYSTEM FUNCTIONS.
  **********************************************************************************************************************
    @attention

    <h2><center>&copy; Copyright(c) <2023> <MindMotion></center></h2>

      Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
    following conditions are met:
    1. Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
       the following disclaimer in the documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or
       promote products derived from this software without specific prior written permission.

      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *********************************************************************************************************************/

/* Define to prevent recursive inclusion */
#define _PLATFORM_C_

/* Files include */
#include <stdio.h>
#include "platform.h"

/**
  * @addtogroup MM32G0001_LibSamples
  * @{
  */

/**
  * @addtogroup TIM1
  * @{
  */

/**
  * @addtogroup TIM1_PWM_Output
  * @{
  */

/* Private typedef ****************************************************************************************************/

/* Private define *****************************************************************************************************/

/* Private macro ******************************************************************************************************/

/* Private variables **************************************************************************************************/

/* Private functions **************************************************************************************************/

/***********************************************************************************************************************
  * @brief  Initialize SysTick for delay function
  * @note   none
  * @param  none
  * @retval none
  *********************************************************************************************************************/
	
	static __IO u32 sDelayNopNumber;
	
void PLATFORM_InitDelay(void)
{
	sDelayNopNumber = 99;
//    if (SysTick_Config(RCC_GetHCLKFreq() / 1000))
//    {
//        while (1)
//        {
//        }
//    }

//    NVIC_SetPriority(SysTick_IRQn, 0x0);
}

/***********************************************************************************************************************
  * @brief  Millisecond delay
  * @note   none
  * @param  Millisecond: delay time unit
  * @retval none
  *********************************************************************************************************************/
void PLATFORM_DelayMS(uint32_t count)
{
   u32 i = 0;
    while(count--) {
        i = sDelayNopNumber * 1000;
        while(i--);
    }
}
void PLATFORM_DelayUS(__IO u32 count)
{
    u32 i = 0;
    while(count--) {
        i = sDelayNopNumber;
        while(i--);
    }
}

void LED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin  =  LED1_Pin ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LED1_Port, &GPIO_InitStructure);

//	  GPIO_InitTypeDef  GPIO_InitStructure2;
//	  RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
//    GPIO_StructInit(&GPIO_InitStructure);
//    GPIO_InitStructure.GPIO_Pin  =  LED2_Pin ;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_Init(LED1_Port, &GPIO_InitStructure);
		
		RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin  =  Input_Switch_Pin ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

		RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin  =  Normal_Switch | PWM_Switch;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

}

void LED2_GPIO_Init(void)
{
      // Enable Port B clock

    GPIO_InitTypeDef GPIO_InitStructure;
  	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE); 
    GPIO_StructInit(&GPIO_InitStructure);              // Optional reset

    GPIO_InitStructure.GPIO_Pin   = LED2_Pin ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(LED2_Port, &GPIO_InitStructure);         // Make sure Port matches clock
}
/***********************************************************************************************************************
  * @brief  Initialize console for printf
  * @note   none
  * @param  Baudrate : USART1 communication baudrate
  * @retval none
  *********************************************************************************************************************/
//void PLATFORM_InitConsole(uint32_t Baudrate)
//{
//    GPIO_InitTypeDef  GPIO_InitStruct;
//    USART_InitTypeDef USART_InitStruct;

//    RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART1, ENABLE);

//    USART_StructInit(&USART_InitStruct);
//    USART_InitStruct.USART_BaudRate   = Baudrate;
//    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
//    USART_InitStruct.USART_StopBits   = USART_StopBits_1;
//    USART_InitStruct.USART_Parity     = USART_Parity_No;
//    USART_InitStruct.USART_Mode       = USART_Mode_Tx;
//    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//    USART_Init(USART1, &USART_InitStruct);

//    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);

//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_4);

//    GPIO_StructInit(&GPIO_InitStruct);
//    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
//    GPIO_Init(GPIOA, &GPIO_InitStruct);

//    USART_Cmd(USART1, ENABLE);
//}

#if   defined (__ICCARM__)

#if   (__VER__ >= 9030001)

/* Files include */
#include <stddef.h>
#include <LowLevelIOInterface.h>

/***********************************************************************************************************************
  * @brief  redefine __write function
  * @note   for printf
  * @param  handle
  * @param  *buf
  * @param  bufSize
  * @retval nChars
  *********************************************************************************************************************/
size_t __write(int handle, const unsigned char *buf, size_t bufSize)
{
    size_t nChars = 0;

    /* Check for the command to flush all handles */
    if (-1 == handle)
    {
        return (0);
    }

    /* Check for stdout and stderr (only necessary if FILE descriptors are enabled.) */
    if ((_LLIO_STDOUT != handle) && (_LLIO_STDERR != handle))
    {
        return (-1);
    }

    for (/* Empty */; bufSize > 0; --bufSize)
    {
        USART_SendData(USART1, *buf);

        while (RESET == USART_GetFlagStatus(USART1, USART_FLAG_TC))
        {
        }

        ++buf;
        ++nChars;
    }

    return (nChars);
}

#else

/***********************************************************************************************************************
  * @brief  redefine fputc function
  * @note   for printf
  * @param  ch
  * @param  f
  * @retval ch
  *********************************************************************************************************************/
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (uint8_t)ch);

    while (RESET == USART_GetFlagStatus(USART1, USART_FLAG_TC))
    {
    }

    return (ch);
}

#endif

#elif defined (__GNUC__)

#else

/***********************************************************************************************************************
  * @brief  redefine fputc function
  * @note   for printf
  * @param  ch
  * @param  f
  * @retval ch
  *********************************************************************************************************************/
//int fputc(int ch, FILE *f)
//{
//    USART_SendData(USART1, (uint8_t)ch);

//    while (RESET == USART_GetFlagStatus(USART1, USART_FLAG_TC))
//    {
//    }

//    return (ch);
//}

#endif

/***********************************************************************************************************************
  * @brief  Initialize LED GPIO pin
  * @note   none
  * @param  none
  * @retval none
  *********************************************************************************************************************/
//void PLATFORM_InitLED(void)
//{
//    GPIO_InitTypeDef GPIO_InitStruct;

//    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);

//    PLATFORM_LED_Enable(LED1, DISABLE);
//    PLATFORM_LED_Enable(LED2, DISABLE);
//    PLATFORM_LED_Enable(LED3, DISABLE);
//    PLATFORM_LED_Enable(LED4, DISABLE);

//    GPIO_StructInit(&GPIO_InitStruct);
//    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_10 | GPIO_Pin_15;
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
//    GPIO_Init(GPIOA, &GPIO_InitStruct);
//}

/***********************************************************************************************************************
  * @brief  LED on or off
  * @note   none
  * @param  LEDn : LED index
  * @arg    LED1, LED2, LED3, LED4
  * @param  State
  * @arg    ENABLE, DISABLE
  * @retval none
  *********************************************************************************************************************/
//void PLATFORM_LED_Enable(LEDn_TypeDef LEDn, FunctionalState State)
//{
//    switch (LEDn)
//    {
//        case LED1:
//            GPIO_WriteBit(GPIOA, GPIO_Pin_15, (ENABLE == State) ? Bit_RESET : Bit_SET);
//            break;

//        case LED2:
//            GPIO_WriteBit(GPIOA, GPIO_Pin_10, (ENABLE == State) ? Bit_RESET : Bit_SET);
//            break;

//        case LED3:
//            GPIO_WriteBit(GPIOA, GPIO_Pin_6, (ENABLE == State) ? Bit_RESET : Bit_SET);
//            break;

//        case LED4:
//            GPIO_WriteBit(GPIOA, GPIO_Pin_5, (ENABLE == State) ? Bit_RESET : Bit_SET);
//            break;

//        default:
//            break;
//    }
//}

/***********************************************************************************************************************
  * @brief  LED toggle display
  * @note   none
  * @param  LEDn : LED index
  * @arg    LED1, LED2, LED3, LED4
  * @retval none
  *********************************************************************************************************************/
//void PLATFORM_LED_Toggle(LEDn_TypeDef LEDn)
//{
//    switch (LEDn)
//    {
//        case LED1:
//            GPIO_WriteBit(GPIOA, GPIO_Pin_15, GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15) ? Bit_RESET : Bit_SET);
//            break;

//        case LED2:
//            GPIO_WriteBit(GPIOA, GPIO_Pin_10, GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_10) ? Bit_RESET : Bit_SET);
//            break;

//        case LED3:
//            GPIO_WriteBit(GPIOA, GPIO_Pin_6, GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_6) ? Bit_RESET : Bit_SET);
//            break;

//        case LED4:
//            GPIO_WriteBit(GPIOA, GPIO_Pin_5, GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_5) ? Bit_RESET : Bit_SET);
//            break;

//        default:
//            break;
//    }
//}

/***********************************************************************************************************************
  * @brief  Initialize Platform
  * @note   none
  * @param  none
  * @retval none
  *********************************************************************************************************************/
void PLATFORM_Init(void)
{
    PLATFORM_InitDelay();

//    PLATFORM_InitLED();

//    PLATFORM_InitConsole(115200);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/********************************************** (C) Copyright MindMotion **********************************************/

