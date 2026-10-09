/***********************************************************************************************************************
    @file    main.c
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
/* Define to prevent recursive inclusion */
#define _MAIN_C_

/* Files include */
#include "platform.h"
#include "tim1_pwm_output.h"
#include "main.h"
	
int pwm_dim = 0;
int pwm_dim2 = 0;
extern u32 SystemCoreClock;
u8 PWM_button_press = 0;
u8 button_press = 0;
u8 current_pwm_state = 3;
u8 prev_pwm_State = 0;
u8 pwm_counter = 0;
u8 button_flag = 0;
u8 dim_count = 0;
u8 new_counter = 0;

///////////////
u32 pwm_value_set = 100;
u32 led_flag = 0;
u32 led_on = 0;
u32 delayTime = 600;

bool pwm_flag = false;
bool pwm_change = true;
bool pwm_change1 = false;
bool pwm_change2 = false;
bool pwm_level_adjusted = false;
bool longcheckFlag = false;
bool in_pwm = false;
bool pwm_long_press = false;
bool pwm_long_press1 = false;
bool fade_flag = true;
bool dim_check_flag = false;
bool lamp_state = false;
bool input_switch_active = false;
bool lamp_state1 = false;


volatile uint32_t Counter = 0;
volatile uint32_t counter_pwm = 0;
volatile uint8_t short_press = 0;
volatile uint8_t long_press = 0;
volatile uint8_t pwm_press = 0;
volatile uint8_t button_was_pressed = 0;
volatile uint8_t pwm_button_was_pressed = 0;
volatile uint8_t button_was_pressed1 = 0;

volatile u8 current_long_press = 0;
volatile uint32_t input_switch_counter = 0;

volatile uint8_t first_pass_event_ignored = 0;

float pwm_percent_val = 2;
float min_val = 0;
float max_val = 0;

///////////////////
uint8_t input_switch_check = 0;
uint8_t input_switch_short_press = 0;
uint8_t input_switch_long_press = 0;
////////////////////////

typedef enum {
  dimmer_state,
  pwm_state,
  constant_on_state,
  dimmer_state1,
  idle,
}
current_state;
current_state prev_system_state = idle;
current_state system_state = idle;

u8 pwm_levels[] = {
  100,
  68,
  45,
  16
}; // Only three levels
int pwm_index = 1;
int pwm_index1 = 1;
void pwm(void);
void pwm_new(void);

void SysTick_Handler(void) {
  //	TimingDelayDecrement();
  button_press = GPIO_ReadInputDataBit(GPIOA, Normal_Switch);
  PWM_button_press = GPIO_ReadInputDataBit(GPIOA, PWM_Switch);
  input_switch_check = GPIO_ReadInputDataBit(GPIOA, Input_Switch_Pin);
//  button_was_pressed = PWM_button_press;

if (input_switch_check == 0) {
    input_switch_counter++;

    // trigger long press immediately while holding
    if (input_switch_counter == 350) {

        // ignore first false startup pulse
        if (first_pass_event_ignored == 0) {
            first_pass_event_ignored = 1;
        } 
				
    }

} else if (input_switch_check == 1) {

    // short press on release
    if (input_switch_counter > 0 && input_switch_counter <= 350) {

        // ignore first false startup pulse
        if (first_pass_event_ignored == 0) {
            first_pass_event_ignored = 1;
        } else {
            input_switch_long_press = 1;
        }
				
    }
		else if(input_switch_counter > 350) {
            input_switch_long_press = 1;
        }

    input_switch_counter = 0;
}
  if (PWM_button_press == 1) // enter pwm mode only if the lamp is constant on
  {
					pwm_button_was_pressed = 1;

    counter_pwm++;
    if ((counter_pwm >= 500 && counter_pwm <=1000)  && lamp_state == true) {

      if (new_counter == 0 && led_on == 0) //for the pwm mode activation

      {
        system_state = pwm_state;
				lamp_state = false;
        pwm_press = 1;
        //					LED2_OFF();
        pwm_change1 = false;
        //					pwm_level_adjusted = false;
        pwm_change = false;
        pwm_long_press = false;
        //					current_long_press = false;
        dim_check_flag = false;
        fade_flag = true;
        min_val = 20;
        max_val = 80;
				pwm_button_was_pressed = 0;
				pwm_long_press1 = false;
//				counter_pwm = 0;
      } else if (new_counter == 1) //to switch from fade in fade out to dimmer mode
      {
        system_state = dimmer_state;
        prev_system_state = dimmer_state;
        led_on = 1;
        pwm_change1 = true;
        pwm_change = true;
        new_counter = 0;
        pwm_long_press = true;
        dim_count = 1;
        fade_flag = false;
				pwm_long_press1 = true;
				 dim_check_flag = true;
        //			pwm_level_adjusted = true;
//        counter_pwm = 0;
        PLATFORM_DelayMS(1);
        return;
      }
    }

  } else if (PWM_button_press == 0 && pwm_button_was_pressed == 1) {

    //	if(counter_pwm > 0 && counter_pwm < 350 && lamp_state == true)
    //	{
    //		lamp_state1 = true;
    //	}
		
		//
		pwm_button_was_pressed = 0;
    if ( (counter_pwm > 0 && counter_pwm < 350 && lamp_state == true && pwm_long_press1 == true) ||(counter_pwm > 0 && counter_pwm < 350 && pwm_level_adjusted == true && pwm_long_press == true)) {
      pwm_change = true;
      system_state = dimmer_state;
      prev_system_state = dimmer_state;
      pwm_change1 = true;
        pwm_long_press = false; ////////////////////changed from true to false
      led_on = 0;
      lamp_state1 = true;
//			lamp_state = true;
			
    }

    if (counter_pwm > 0 && counter_pwm < 350 && dim_check_flag == true && lamp_state == true) {
      pwm_change = true;
      pwm_change2 = true;
      button_was_pressed = 1;
      led_on = 0;
      system_state = dimmer_state1;
			      prev_system_state = dimmer_state;

			        pwm_long_press = false;

    }
    new_counter = 0; ///////////
    counter_pwm = 0;
    led_on = 0;
		pwm_long_press1 = false;
    //				current_long_press = 0
  }
  if (button_press == 1) {
    pwm_press = 0;
    new_counter = 0;
    current_long_press = 0;
    pwm_long_press = false;

    Counter++;
//		if(Counter > 350 )
//		{
//			Counter = 0;
//		}
button_was_pressed1 = 1;
	}

	
   if (button_press == 0 && button_was_pressed1 == 1) {
    if (Counter > 0 && Counter < 350) {
			button_was_pressed1 = 0;
//      LED1_OFF();
      short_press = 1;
      pwm_change1 = true;
      led_on = 0;
			if (pwm_flag == 1){
			lamp_state = true;
				pwm_flag = 0;
			}
			
      //in_pwm = false ;
		}
	

    Counter = 0;
    //			in_pwm = false;
  }

}

void Systick_init() {
  if (SysTick_Config(RCC_GetSysClockFreq() / 1000)) {
    // Capture error
    while (1);
  }
  // Configure the SysTick handler priority
  NVIC_SetPriority(SysTick_IRQn, 0x0); //SysTickinterrupt priority class set
}
float ICHECK = 0;

void pass()
{
	    if (input_switch_long_press == 1) { //INPUT SWITCH LONG PRESS LOGIC (HORN BLINK)
      int i;

      // Blink twice
      LED1_OFF();
//      for (i = 0; i < 1; i++) {
        //			  SetPWMDutyCyclePercent(0);
        //        LED2_OFF();
        //			  LED1_OFF();
        //				PLATFORM_DelayMS(5);
        SetPWMDutyCyclePercent(100);
        LED2_ON();
        LED1_ON();
        PLATFORM_DelayMS(5);
        SetPWMDutyCyclePercent(0);
        LED2_OFF();
        LED1_OFF();
        PLATFORM_DelayMS(5);
//      }
			if (lamp_state == true){
				LED1_ON();
				LED2_ON();
				SetPWMDutyCyclePercent(100);

			}

      prev_system_state = system_state;
      //		system_state = idle;
      if (prev_system_state == dimmer_state1 || prev_system_state == dimmer_state) {
        current_long_press = 1;
//        pwm_change2 = false;
				lamp_state1 = false;
				pwm_change1 = false;
        SetPWMDutyCyclePercent(pwm_levels[pwm_dim]);
        LED2_ON();
        LED1_ON();

        //system_state = idle;
      }
      if (prev_system_state == pwm_state) {
        fade_flag = true;
        pwm_change = false;
        prev_system_state = idle;
      }

      input_switch_long_press = 0;
      input_switch_active = true;

    }
}


s32 main(void) {
   TIM1_Configure();
  Systick_init();
  LED_Init();
  LED2_GPIO_Init();
	PLATFORM_InitDelay();
//  TimerPinConfig(); // Set PA9 as PWM output
//  Tim1InitSetting(999, (SystemCoreClock / 1000000) - 1); // 1kHz
//  Tim1PwmOutputInitSetting(0); // 10% duty initially
//  TimerEnable();
  SetPWMDutyCyclePercent(0);

  while (1) {
		//10 -- 22 percent
		//36 = 50%
		//58 = 75%
//SetPWMDutyCyclePercent(58);
//	 for (ICHECK = 0; ICHECK <= pwm_value_set; ICHECK++) {
//		  SetPWMDutyCyclePercent(ICHECK);
//		 LED1_ON();
//        PLATFORM_DelayUS(99);
//	 }
//	 for (ICHECK = pwm_value_set; ICHECK >= 0; ICHECK--) {
//		SetPWMDutyCyclePercent(ICHECK);
//		 LED1_OFF();
//        PLATFORM_DelayUS(99);
//	 } 
//		pwm_new();
// system_clock1 = RCC_GetSysClockFreq() ;
    if (input_switch_short_press == 1) {

      //INPUT SWITCH SHORT PRESS LOGIC (HORN BLINK)

      int i;
      LED1_OFF();
      //			 SetPWMDutyCyclePercent(0);
//      for (i = 0; i < 1; i++) {
        //        SetPWMDutyCyclePercent(0);
        //        LED2_OFF();
        //				LED1_OFF();
        //        PLATFORM_DelayMS(5);
        SetPWMDutyCyclePercent(100);
        LED2_ON();
        LED1_ON();
        PLATFORM_DelayMS(5);
        SetPWMDutyCyclePercent(0);
        LED2_OFF();
        LED1_OFF();
        PLATFORM_DelayMS(5);

        if (lamp_state == true) {
          SetPWMDutyCyclePercent(100);
          LED2_ON();
          LED1_ON();
        }

//      }
      prev_system_state = system_state;
      //		system_state = idle;
      if (prev_system_state == dimmer_state1 || prev_system_state == dimmer_state) {
        current_long_press = 1;
//      pwm_change2 = false;
				lamp_state1 = false;
				pwm_change1 = false;
        SetPWMDutyCyclePercent(pwm_levels[pwm_dim]);
        LED2_ON();
        LED1_ON();

        //system_state = idle;
      }
      if (prev_system_state == pwm_state) {
        fade_flag = true;
        pwm_change = false;
        prev_system_state = idle;
      }

      input_switch_short_press = 0;
      input_switch_active = true;

    }

    if (input_switch_long_press == 1) { //INPUT SWITCH LONG PRESS LOGIC (HORN BLINK)
      int i;

      // Blink twice
      LED1_OFF();
//      for (i = 0; i < 1; i++) {
        //			  SetPWMDutyCyclePercent(0);
        //        LED2_OFF();
        //			  LED1_OFF();
        //				PLATFORM_DelayMS(5);
        SetPWMDutyCyclePercent(100);
        LED2_ON();
        LED1_ON();
        PLATFORM_DelayMS(5);
        SetPWMDutyCyclePercent(0);
        LED2_OFF();
        LED1_OFF();
        PLATFORM_DelayMS(5);
//      }
			if (lamp_state == true){
				LED1_ON();
				LED2_ON();
				SetPWMDutyCyclePercent(100);

			}

      prev_system_state = system_state;
      //		system_state = idle;
      if (prev_system_state == dimmer_state1 || prev_system_state == dimmer_state) {
        current_long_press = 1;
//        pwm_change2 = false;
				lamp_state1 = false;
				pwm_change1 = false;
        SetPWMDutyCyclePercent(pwm_levels[pwm_dim]);
        LED2_ON();
        LED1_ON();

        //system_state = idle;
      }
      if (prev_system_state == pwm_state) {
        fade_flag = true;
        pwm_change = false;
        prev_system_state = idle;
      }

      input_switch_long_press = 0;
      input_switch_active = true;

    }

    //////////////////////////PASS END/////////////////////////////////////////////

//    if (long_press == 1 || prev_system_state == constant_on_state) {

//      if (pwm_level_adjusted == true) //|| in_pwm == true
//      {
//        long_press = 0;
//        //					LED1_OFF();
//        longcheckFlag = true;
//        //					in_pwm = false;
//        //					break;
//      }
//      if (longcheckFlag == false) {
//        SetPWMDutyCyclePercent(100);
//        LED1_ON();
//        LED2_ON();
//        current_long_press = 1;
//        dim_check_flag = true;
//        long_press = 0;
//      }

//    }
    if (short_press == 1 && lamp_state == false) {
      LED1_ON();
      LED2_ON();
      SetPWMDutyCyclePercent(100);
      pwm_index1 = 1; 
			prev_pwm_State =0;
			
			 pwm_value_set = 100;
          delayTime = 600;
          pwm_percent_val = 2;
         dim_check_flag = true;
						pwm_dim = 0;
			pwm_index =1;

      short_press = 0;
      current_long_press = 1;
      lamp_state = true;
			
//      lamp_state1 = true;

    }

    if (short_press == 1 && lamp_state == true) {
      LED1_OFF();
      LED2_OFF();
      SetPWMDutyCyclePercent(0);
      current_long_press = 0;
      pwm_long_press = false; 
			pwm_index1 = 1; 
			prev_pwm_State = 0;
			pwm_index =1;
			pwm_value_set = 100;
      delayTime = 600;
      pwm_percent_val = 2;
		 
      short_press = 0;
			pwm_dim = 0;
      system_state = idle;
      lamp_state = false;
      lamp_state1 = false;

			
			
    }
    if ((lamp_state1 == true) || pwm_press == 1 || prev_system_state == pwm_state) {

      if (pwm_change == false) {

        in_pwm = true;
        pwm_new();
        pwm_level_adjusted = false;
        //					dim_count = dim_count + 1;
        new_counter = 1;
        fade_flag = true;
      }

      //				if(pwm_flag == true && pwm_change1 ==true)
      if ((lamp_state1 == true) || pwm_change1 == true && prev_system_state == dimmer_state) {

        lamp_state1 = false;
				lamp_state = true;
        //					pwm_change = false
        pwm_change1 = false;
        //pwm_flag = false;
        if (dim_count == 1 && pwm_level_adjusted == false) {
          pwm_index = prev_pwm_State;
          prev_system_state = idle; ///////////////////
        }

        LED1_OFF();
        LED2_OFF();

        SetPWMDutyCyclePercent(pwm_levels[pwm_index]);
        pwm_dim = pwm_index;

        PLATFORM_DelayMS(7);
        LED1_ON(); // optional
        LED2_ON();
        if (pwm_index == 0) {
          pwm_value_set = 100;
          delayTime = 600;
          pwm_percent_val = 2;
         
        } else if (pwm_index == 1) {
          pwm_value_set = 75;
          delayTime = 350;
          pwm_percent_val = 0.75;
          min_val = 10;
          max_val = 50;
        } else if (pwm_index == 2) {
          pwm_value_set = 50;
          delayTime = 250;
          pwm_percent_val = 0.35;
          min_val = 5;
          max_val = 30;
        } else if (pwm_index == 3) {
          pwm_value_set = 30;
          delayTime = 150;
          pwm_percent_val = 0.2;
          min_val = 0;
          max_val = 15;
        }

        // Step to next level
        prev_pwm_State = pwm_index;
        pwm_index++;

        // Wrap back to beginning if end reached
        if (pwm_index >= 4) {
          pwm_index = 0;
        }

        prev_system_state = idle;
        pwm_level_adjusted = true;

      }

    }
    if ((pwm_change2 == true && lamp_state== true)  || prev_system_state == dimmer_state1) {
      pwm_change2 = false;

      LED1_OFF();
      LED2_OFF();

      if (input_switch_active) {
        if (pwm_levels[prev_pwm_State] == 0) {
          // Lamp was OFF ? keep it OFF
          SetPWMDutyCyclePercent(0);
          LED1_OFF();
          LED2_OFF();
        }
        // Case: returning from horn ? restore last brightness
        SetPWMDutyCyclePercent(pwm_levels[prev_pwm_State]);
        pwm_dim = prev_pwm_State;

        // Reset flag so next normal press works as usual
        input_switch_active = false;

      } else {
        // Case: normal dimmer cycle
        SetPWMDutyCyclePercent(pwm_levels[pwm_index1]);
        pwm_dim = pwm_index1;

        PLATFORM_DelayMS(5);
        LED1_ON();
        LED2_ON();

        prev_pwm_State = pwm_index1;
        pwm_index1++;
        if (pwm_index1 >= 4) {
          pwm_index1 = 0;
        }

      }

      PLATFORM_DelayMS(5);
      LED1_ON();
      LED2_ON();

      prev_system_state = idle;
      pwm_level_adjusted = true;
    }

  }
}

void pwm_new(void) {
  float i;
  u32 k; // inner delay loop

  pwm_flag = true;
  lamp_state = true;
  if (fade_flag == true) {
    // -----------------------------
    // FADE IN
    // -----------------------------
    LED1_ON();
    LED2_ON();
			pass();
    for (i = 0; i <= pwm_value_set; i += pwm_percent_val) {
			pass();
      if (short_press == 1 && lamp_state == true) {
				      short_press = 0;

        pwm_press = 0;
        led_on = 0;
        LED1_OFF();
        LED2_OFF();
				 
				pwm_long_press = false; 
//      short_press = 0;
      system_state = idle;
      lamp_state = false;
      lamp_state1 = false;
        SetPWMDutyCyclePercent(0);
         
        return;
      }

      SetPWMDutyCyclePercent((int)i);

      for (k = 0; k < delayTime; k++) {
        PLATFORM_DelayUS(1);
        if (short_press == 1 && lamp_state == true) {
					      short_press = 0;

          pwm_press = 0;
          led_on = 0;
          LED1_OFF();
          LED2_OFF();
					 
          SetPWMDutyCyclePercent(0);
          pwm_long_press = false; 
//      short_press = 0;
      system_state = idle;
      lamp_state = false;
      lamp_state1 = false;
          return;
        }
				
      }

      if (pwm_change1 == true) {
        fade_flag = false;
        return; // exit smoothly at current brightness (no blink)
      }
    }
        PLATFORM_DelayMS(7);

    // -----------------------------
    // FADE OUT
    // -----------------------------
    for (i = pwm_value_set; i >= 0; i -= pwm_percent_val) {
			pass();
      if (short_press == 1 && lamp_state == true) {
				      short_press = 0;

        pwm_press = 0;
        led_on = 0;
        LED1_OFF();
        LED2_OFF();
				 
        SetPWMDutyCyclePercent(0);
        pwm_long_press = false; 
      system_state = idle;
      lamp_state = false;
      lamp_state1 = false;
        return;
      }

      SetPWMDutyCyclePercent((int)i);

      for (k = 0; k < delayTime; k++) {
        PLATFORM_DelayUS(1);
        if (short_press == 1 && lamp_state == true) {
					short_press = 0;
          pwm_press = 0;
          led_on = 0;
          LED1_OFF();
          LED2_OFF();
					 
          SetPWMDutyCyclePercent(0);
          pwm_long_press = false; 
      
      system_state = idle;
      lamp_state = false;
      lamp_state1 = false;
          return;
        }
      }

      if (pwm_change1 == true) {
        fade_flag = false;
        return; // smooth exit, keep current PWM brightness
      }

      if (input_switch_long_press == 1 || input_switch_short_press == 1) {
        fade_flag = false;
        pwm_change = true;
        return; // exit gracefully, no LED off
      }
    }

    // -----------------------------
    // POST FADE CLEANUP
    // -----------------------------
    if (fade_flag == true) {
      LED1_OFF();
      LED2_OFF();
			
      SetPWMDutyCyclePercent(0);
      PLATFORM_DelayMS(5);
    }
  }
}

