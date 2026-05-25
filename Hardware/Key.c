#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "menu.h"

uint8_t Key_Num = 0;

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_2 | GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void)
{
	if (Key_Num)
	{
		uint8_t temp=0;
		temp=Key_Num;
		Key_Num=0;
		return temp;
	}
	else return 0;
	
}

uint8_t Key_GetState(void)
{
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0)
	{
		return 1;
	}
	else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0)
	{
		return 2;
	}
	else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
	{
		return 3;
	}
	else return 0;
}

void Key_Tick(void)
{
	static uint8_t CurrentSta,PreSta;

	PreSta = CurrentSta;
	CurrentSta = Key_GetState();
	if(PreSta!=0&&CurrentSta==0)
	{
		Key_Num = PreSta;
	}
	//用于led模拟开关机,确保模拟关机后不进行其他操作
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)==1)
	{
		Key_Num = 0;
	}
}

void Key3_Tick(void)
{
	static uint16_t Key3_Count=0;
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
	{
		if(Key3_Count++>200)
		{
			//关机
			if(Key3_Count>300)
			{
				Key_Num=4;
				Key3_Count=0;
				return;
			}
			//开机
			else if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)==1) 
			{
				//开机状态
				GPIO_SetBits(GPIOB, GPIO_Pin_13);
				GPIO_ResetBits(GPIOB, GPIO_Pin_12);
//				clear_erro=0;
				Key3_Count=0;
				return;
			}
		}
		
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1) Key3_Count=0;
}
