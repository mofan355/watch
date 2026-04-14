#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"
#include "menu.h"
#include "Timer.h"

int main(void)
{
	OLED_Init();
	OLED_Clear();

	Peripheral_Init();
	Timer_Init();

	int clkflag1=First_Page_Clock();
	
	while (1)
	{
		if(clkflag1==1){}
		else if(clkflag1==2){SettingPage();}
	}
}
