/***********************************************************************************************************************
    @file    tim1_pwm_output.c
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
#define _TIM1_PWM_OUTPUT_C_

/* Files include */
#include <stdio.h>
#include "platform.h"
#include "tim1_pwm_output.h"

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
  * @brief
  * @note   none
  * @param  none
  * @retval none
  *********************************************************************************************************************/
	//volatile uint32_t cpu_freq = 0;
	uint16_t arr = 0;
    uint16_t compare = 0;
void TIM1_Configure(void)
{
    GPIO_InitTypeDef        GPIO_InitStruct;
    TIM_OCInitTypeDef       TIM_OCInitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;

    /* Compute the value to be set in ARR regiter to generate signal frequency at 100 Khz */
    uint32_t TimerPeriod = 999 ;//(RCC_GetPCLK1Freq() / 100000 ) - 1;

    /* Compute CCR1 value to generate a duty cycle at 80% for channel 1 */
    uint32_t Channel1Pulse = ((uint32_t)0 * (TimerPeriod - 1)) / 1000;

//    /* Compute CCR2 value to generate a duty cycle at 40% for channel 2 */
//    uint32_t Channel2Pulse = ((uint32_t)400 * (TimerPeriod - 1)) / 1000;

//    /* Compute CCR3 value to generate a duty cycle at 25% for channel 3 */
//    uint32_t Channel3Pulse = ((uint32_t)250 * (TimerPeriod - 1)) / 1000;

    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM1, ENABLE);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStruct);
    TIM_TimeBaseStruct.TIM_Prescaler         = (SystemCoreClock / 1000000) - 1;
    TIM_TimeBaseStruct.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseStruct.TIM_Period            = TimerPeriod;
    TIM_TimeBaseStruct.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStruct);

    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode       = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState  = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse        = 0;
    TIM_OCInitStruct.TIM_OCPolarity   = TIM_OCPolarity_High;
    TIM_OCInitStruct.TIM_OCIdleState  = TIM_OCIdleState_Set;

    TIM_OCInitStruct.TIM_Pulse = Channel1Pulse;
    TIM_OC1Init(TIM1, &TIM_OCInitStruct);

//    TIM_OCInitStruct.TIM_Pulse = Channel2Pulse;
//    TIM_OC2Init(TIM1, &TIM_OCInitStruct);

//    TIM_OCInitStruct.TIM_Pulse = Channel3Pulse;
//    TIM_OC3Init(TIM1, &TIM_OCInitStruct);

    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_2);  /* TIM1_CH1  */
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_1);  /* TIM1_CH2  */
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_4);  /* TIM1_CH3  */

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    TIM_Cmd(TIM1, ENABLE);

    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

/***********************************************************************************************************************
  * @brief  TIM3
  * @note   none
  * @param  none
  * @retval none
  *********************************************************************************************************************/
	//volatile uint32_t cpu_freq = 0;
//void TIM3_Configure(void)
//{
//    GPIO_InitTypeDef        GPIO_InitStruct;
//    TIM_OCInitTypeDef       TIM_OCInitStruct;
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;

//    /* Compute the value to be set in ARR regiter to generate signal frequency at 100 Khz */
//    uint32_t TimerPeriod = (RCC_GetPCLK1Freq() / 100000 ) - 1;

//    uint32_t Channel1Pulse = 0;
//uint32_t Channel2Pulse = 0;
//uint32_t Channel3Pulse = 0;
//	
//	
//    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3, ENABLE);

//    TIM_TimeBaseStructInit(&TIM_TimeBaseStruct);
//    TIM_TimeBaseStruct.TIM_Prescaler         = 3;
//    TIM_TimeBaseStruct.TIM_CounterMode       = TIM_CounterMode_Up;
//    TIM_TimeBaseStruct.TIM_Period            = TimerPeriod;
//    TIM_TimeBaseStruct.TIM_ClockDivision     = TIM_CKD_DIV1;
//    TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;
//    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct);

//    TIM_OCStructInit(&TIM_OCInitStruct);
//    TIM_OCInitStruct.TIM_OCMode       = TIM_OCMode_PWM1;
//    TIM_OCInitStruct.TIM_OutputState  = TIM_OutputState_Enable;
//    TIM_OCInitStruct.TIM_Pulse        = 0;
//    TIM_OCInitStruct.TIM_OCPolarity   = TIM_OCPolarity_High;
//    TIM_OCInitStruct.TIM_OCIdleState  = TIM_OCIdleState_Set;

//    TIM_OCInitStruct.TIM_Pulse = Channel1Pulse;
//    TIM_OC1Init(TIM3, &TIM_OCInitStruct);

//    TIM_OCInitStruct.TIM_Pulse = Channel2Pulse;
//    TIM_OC2Init(TIM3, &TIM_OCInitStruct);

//    TIM_OCInitStruct.TIM_Pulse = Channel3Pulse;
//    TIM_OC3Init(TIM3, &TIM_OCInitStruct);

//    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);

//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_4);  /* TIM3_CH1  */
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_4);  /* TIM3_CH2  */
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_4);  /* TIM3_CH3  */

//    GPIO_StructInit(&GPIO_InitStruct);
//    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_11 | GPIO_Pin_2 | GPIO_Pin_0;
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
//    GPIO_Init(GPIOA, &GPIO_InitStruct);

//    TIM_Cmd(TIM3, ENABLE);

//    TIM_CtrlPWMOutputs(TIM3, ENABLE);
//}

/***********************************************************************************************************************
  * @brief
  * @note   none
  * @param  none
  * @retval none
  *********************************************************************************************************************/
void TIM1_PWM_Output_Sample(void)
{
	
	
//    printf("\r\nTest %s", __FUNCTION__);

    TIM1_Configure();
//	  TIM3_Configure();
	
	

//    while (1)
//    {
//			//uint32_t cpu_freq = RCC_GetPCLK1Freq();
//        PLATFORM_LED_Toggle(LED1);
//        PLATFORM_DelayMS(100);
//    }
}
void SetPWMDutyCyclePercent(uint8_t percent) {
	arr = TIM1->ARR;
	compare = (arr + 1) * percent / 100;
    if (percent > 100) percent = 100;
    
    TIM_SetCompare1(TIM1, compare);
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

