#include "stm32f10x.h"                  // Device header
#include "menu.h"
#include "MyRTC.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"

uint8_t KeyNum = 0;

void Peripheral_Init(void)
{
    MyRTC_Init();
    Key_Init();
    LED_Init();
}

void Show_Clock_UI(void)
{
    MyRTC_ReadTime();
    OLED_Printf(0,0,OLED_6X8,"%d-%d-%d",MyRTC_Time[0],MyRTC_Time[1],MyRTC_Time[2]);
    OLED_Printf(16,16,OLED_12X24,"%02d:%02d:%02d",MyRTC_Time[3],MyRTC_Time[4],MyRTC_Time[5]);
    OLED_ShowString(0,48,"菜单",OLED_8X16);
    OLED_ShowString(96,48,"设置",OLED_8X16);
}

/*
clkflag值为1时选中菜单，值为2时选中设置
*/
int clkflag=1;
int First_Page_Clock(void)
{
    while(1)
    {
        KeyNum = Key_GetNum();
        if(KeyNum == 1)//上一项
        {
            clkflag--;
            if(clkflag<1) clkflag=2;
        }
        else if(KeyNum == 2)//下一项
        {
            clkflag++;
            if(clkflag>2) clkflag=1;
        }
        else if(KeyNum == 3)//确定
        {
            OLED_Clear();
            OLED_Update();
            return clkflag;
        }

        switch(clkflag)
        {
            case 1:
                Show_Clock_UI();
                OLED_ReverseArea(0,48,32,16);
                OLED_Update();
                break;
            case 2:
                Show_Clock_UI();
                OLED_ReverseArea(96,48,32,16);
                OLED_Update();
                break;
            default:
                break;
        }
    }
}

void Show_SettingPage_UI(void)
{
    OLED_ShowImage(0,0,16,16,Return);
    OLED_ShowString(0,16,"日期时间设置",OLED_8X16);
}

/*
settingflag值为2时选中日期时间设置，值为1时选中返回
*/
int settingflag=2;
void SettingPage(void)
{
    uint8_t settingflag_temp=0;
    while(1)
    { 
        KeyNum = Key_GetNum();
        
        if(KeyNum == 1)//上一项
        {
            settingflag--;
            if(settingflag<1) settingflag=2;
        }
        else if(KeyNum == 2)//下一项
        {
            settingflag++;
            if(settingflag>2) settingflag=1;
        }
        else if(KeyNum == 3)//确定
        {
            OLED_Clear();
            OLED_Update();
            settingflag_temp=settingflag;
        }

        if(settingflag_temp==1) {return;}
        else if(settingflag_temp==2) {}

        switch(settingflag)
        {
            case 1:
                Show_SettingPage_UI();
                OLED_ReverseArea(0,0,16,16);
                OLED_Update();
                break;
            case 2:
                Show_SettingPage_UI();
                OLED_ReverseArea(0,16,96,16);
                OLED_Update();
                break;
            default:
                break;
        }
    }
}
