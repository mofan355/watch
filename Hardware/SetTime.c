#include "SetTime.h"
#include "menu.h"
#include "OLED.h"
#include "Key.h"
#include "MyRTC.h"


uint8_t KeyNum_SetTime = 1;

void Show_SetTimePage_FirstUI(void)
{
    OLED_ShowImage(0,0,16,16,Return);
    OLED_Printf(0,16,OLED_8X16,"年:%4d",MyRTC_Time[0]);
    OLED_Printf(0,32,OLED_8X16,"月:%2d",MyRTC_Time[1]);
    OLED_Printf(0,48,OLED_8X16,"日:%2d",MyRTC_Time[2]);
}
void Show_SetTimePage_SecondUI(void)
{
    OLED_Printf(0,16,OLED_8X16,"时:%2d",MyRTC_Time[3]);
    OLED_Printf(0,32,OLED_8X16,"分:%2d",MyRTC_Time[4]);
    OLED_Printf(0,48,OLED_8X16,"秒:%2d",MyRTC_Time[5]);
}

void ChangeRTC_Time(uint8_t i,uint8_t flag)
{
    if(flag==1) {MyRTC_Time[i]++;}
    else if(flag==2) {MyRTC_Time[i]--;}
    else if(flag==3) {MyRTC_SetTime();}
}

void SetYear(void)
{
    while(1)
    {
        KeyNum_SetTime = Key_GetNum();
        if(KeyNum_SetTime==1) ChangeRTC_Time(0,1);
        else if(KeyNum_SetTime==2) 
        {
            ChangeRTC_Time(0,2);
            if(MyRTC_Time[0]<0) ChangeRTC_Time(0,1);
        }
        else if(KeyNum_SetTime==3) 
        {
            ChangeRTC_Time(0,3);
            return;
        }
        Show_SetTimePage_FirstUI();
        OLED_ReverseArea(24,16,32,16);
        OLED_Update();
    }
}

void SetMonth(void)
{
    while(1)
    {
        KeyNum_SetTime = Key_GetNum();
        if(KeyNum_SetTime==1) 
        {
            ChangeRTC_Time(1,1);
            if(MyRTC_Time[1]>12) 
            {
                MyRTC_Time[1]=1;
                MyRTC_SetTime();
            }
        }
        else if(KeyNum_SetTime==2) 
        {
            ChangeRTC_Time(1,2);
            if(MyRTC_Time[1]<1) 
            {
                MyRTC_Time[1]=12;
                MyRTC_SetTime();
            }
        }
        else if(KeyNum_SetTime==3) 
        {
            ChangeRTC_Time(1,3);
            return;
        }
        Show_SetTimePage_FirstUI();
        OLED_ReverseArea(24,32,32,16);
        OLED_Update();
    }
}

/*
闰平年每月天数待区分
*/
void SetDay(void)
{
    while(1)
    {
        KeyNum_SetTime = Key_GetNum();
        if(KeyNum_SetTime==1) 
        {
            ChangeRTC_Time(2,1);
            if(MyRTC_Time[2]>31) 
            {
                MyRTC_Time[2]=1;
                MyRTC_SetTime();
            }
        }
        else if(KeyNum_SetTime==2) 
        {
            ChangeRTC_Time(2,2);
            if(MyRTC_Time[2]<1) 
            {
                MyRTC_Time[2]=31;
                MyRTC_SetTime();
            }
        }
        else if(KeyNum_SetTime==3) 
        {
            ChangeRTC_Time(2,3);
            return;
        }
        Show_SetTimePage_FirstUI();
        OLED_ReverseArea(24,48,32,16);
        OLED_Update();
    }
}

void SetHour(void)
{
    while(1)
    {
        KeyNum_SetTime = Key_GetNum();
        if(KeyNum_SetTime==1) 
        {
            ChangeRTC_Time(3,1);
            if(MyRTC_Time[3]>23) 
            {
                MyRTC_Time[3]=0;
                MyRTC_SetTime();
            }
        }
        else if(KeyNum_SetTime==2) 
        {
            ChangeRTC_Time(3,2);
            if(MyRTC_Time[3]<0) 
            {
                MyRTC_Time[3]=23;
                MyRTC_SetTime();
            }
        }
        else if(KeyNum_SetTime==3) 
        {
            ChangeRTC_Time(3,3);
            return;
        }
        Show_SetTimePage_SecondUI();
        OLED_ReverseArea(24,0,16,16);
        OLED_Update();
    }
}

void SetMinute(void)
{
    while(1)
    {
        KeyNum_SetTime = Key_GetNum();
        if(KeyNum_SetTime==1) 
        {
            ChangeRTC_Time(4,1);
            if(MyRTC_Time[4]>59) 
            {
                MyRTC_Time[4]=0;
                MyRTC_SetTime();
            }
        }
        else if(KeyNum_SetTime==2) 
        {
            ChangeRTC_Time(4,2);
            if(MyRTC_Time[4]<0) 
            {
                MyRTC_Time[4]=59;
                MyRTC_SetTime();
            }
        }
        else if(KeyNum_SetTime==3) 
        {
            ChangeRTC_Time(4,3);
            return;
        }
        Show_SetTimePage_SecondUI();
        OLED_ReverseArea(24,16,16,16);
        OLED_Update();
    }
}

void SetSecond(void)
{
    while(1)
    {
        KeyNum_SetTime = Key_GetNum();
        if(KeyNum_SetTime==1) 
        {
            ChangeRTC_Time(5,1);
            if(MyRTC_Time[5]>59) 
            {
                MyRTC_Time[5]=0;
                MyRTC_SetTime();
            }
        }
        else if(KeyNum_SetTime==2) 
        {
            ChangeRTC_Time(5,2);
            if(MyRTC_Time[5]<0) 
            {
                MyRTC_Time[5]=59;
                MyRTC_SetTime();
            }
        }
        else if(KeyNum_SetTime==3) 
        {
            ChangeRTC_Time(5,3);
            return;
        }
        Show_SetTimePage_SecondUI();
        OLED_ReverseArea(24,32,16,16);
        OLED_Update();
    }
}

/*
返回-1
年-2
月-3
日-4
时-5
分-6
秒-7
*/
int setTimeflag=2;
void SetTimePage(void)
{
    uint8_t setTimeflag_temp=0;
    while(1)
    { 
        KeyNum_SetTime = Key_GetNum();
        
        if(KeyNum_SetTime == 1)//上一项
        {
            setTimeflag--;
            if(setTimeflag<1) setTimeflag=7;
        }
        else if(KeyNum_SetTime == 2)//下一项
        {
            setTimeflag++;
            if(setTimeflag>7) setTimeflag=1;
        }
        else if(KeyNum_SetTime == 3)//确定
        {
            OLED_Clear();
            OLED_Update();
            setTimeflag_temp=setTimeflag;
        }

        if(setTimeflag_temp==1) {return;}
        else if(setTimeflag_temp==2) {SetYear();}
        else if(setTimeflag_temp==3) {SetMonth();}
        else if(setTimeflag_temp==4) {SetDay();}
        else if(setTimeflag_temp==5) {SetHour();}
        else if(setTimeflag_temp==6) {SetMinute();}
        else if(setTimeflag_temp==7) {SetSecond();}

        switch(setTimeflag)
        {
            case 1:
                Show_SetTimePage_FirstUI();
                OLED_ReverseArea(0,0,16,16);
                OLED_Update();
                break;
            case 2:
                Show_SetTimePage_FirstUI();
                OLED_ReverseArea(0,16,16,16);
                OLED_Update();
                break;
            case 3:
                Show_SetTimePage_FirstUI();
                OLED_ReverseArea(0,32,16,16);
                OLED_Update();
                break;
            case 4:
                Show_SetTimePage_FirstUI();
                OLED_ReverseArea(0,48,16,16);
                OLED_Update();
                break;
            case 5:
                Show_SetTimePage_SecondUI();
                OLED_ReverseArea(0,64,16,16);
                OLED_Update();
                break;
            case 6:
                Show_SetTimePage_SecondUI();
                OLED_ReverseArea(0,80,16,16);
                OLED_Update();
                break;
            case 7:
                Show_SetTimePage_SecondUI();
                OLED_ReverseArea(0,96,16,16);
                OLED_Update();
                break;
            default:
                break;
        }
    }
}
