SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files\Microchip\xc8\v3.00\bin;C:\Program Files (x86)\Vector CANdb++ 3.1\Exec32;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin\;C:\Program Files\IVI Foundation\VISA\Win64\Bin\;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin;C:\Program Files\dotnet\;C:\Program Files\Git\cmd;C:\Users\PC\AppData\Local\Programs\Python\Python310\Scripts\;C:\Users\PC\AppData\Local\Programs\Python\Python310\;C:\Users\PC\AppData\Local\Microsoft\WindowsApps;C:\Users\PC\AppData\Local\Programs\Microsoft VS Code\bin;C:\Users\PC\AppData\Local\GitHubDesktop\bin;C:\Users\PC\.dotnet\tools
SET ARMCC5_ASMOPT=--diag_suppress=9931
SET ARMCC5_CCOPT=--diag_suppress=9931
SET ARMCC5_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=MM32G0001A1TC
SET CPU_VENDOR=MindMotion
SET UV2_TARGET=TIM1_PWM_Output
SET CPU_CLOCK=0x00B71B00
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\mm32g0001_it.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\tim1_pwm_output.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\platform.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hal_adc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hal_crc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hal_dbg.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hal_exti.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hal_flash.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hal_gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hal_i2c.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hal_iwdg.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hal_misc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hal_pwr.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hal_rcc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hal_spi.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hal_tim.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hal_uid.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\hal_usart.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\system_mm32g0001.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\objects\startup_mm32g0001_keil._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\Objects\Dimmer_INVERSE_G_v4_1_0_01102026_updated.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\Objects\Dimmer_INVERSE_G_v4_1_0_01102026_updated.axf" --i32combined --output ".\Objects\Dimmer_INVERSE_G_v4_1_0_01102026_updated.hex"
