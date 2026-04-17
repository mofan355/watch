#include "stm32f10x.h"                  // Device header
#include "menu.h"
#include "MyRTC.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"
#include "SetTime.h"
#include "Delay.h"
#include "MPU6050.h"
#include "math.h"

uint8_t KeyNum = 0;

void Peripheral_Init(void)
{
    MyRTC_Init();
    Key_Init();
    LED_Init();
    MPU6050_Init();
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
        else if(settingflag_temp==2) 
        {
            SetTimePage();
            settingflag_temp=0;
        }

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

int menu_flag=0;
uint8_t move_flag=1;
uint8_t pre_Selection;
uint8_t new_Selection;
uint8_t x_pre=48;
uint8_t Speed=4;
void Menu(void)
{
    uint8_t menu_flag_temp=1;
    uint8_t DirectFlag=2;
    while(1)
    { 
        KeyNum = Key_GetNum();
        
        if(KeyNum == 1)//上一项
        {
            menu_flag_temp--;
            DirectFlag=1;
            move_flag=1;
            if(menu_flag_temp<1) menu_flag_temp=7;
        }
        else if(KeyNum == 2)//下一项
        {
            menu_flag_temp++;
            DirectFlag=2;
            move_flag=1;
            if(menu_flag_temp>7) menu_flag_temp=1;
        }
        else if(KeyNum == 3)//确定
        {
            OLED_Clear();
            OLED_Update();

            menu_flag=menu_flag_temp;
            if(menu_flag==1) 
            {
                MoveToFunction();
                return;
            }
            else if(menu_flag==2) 
            {
                MoveToFunction();
                StopWatch();
            }
            else if(menu_flag==3) 
            {
                MoveToFunction();
                LED();
            }
            else if(menu_flag==4) 
            {
                MoveToFunction();
                MPU6050();
            }
            else if(menu_flag==5) 
            {
                
            }
            else if(menu_flag==6) 
            {
                
            }
            else if(menu_flag==7) 
            {
                
            }
        }
        
        if(menu_flag_temp==1&&DirectFlag==2) Set_Selection(move_flag,6,0);
        else if(menu_flag_temp==7&&DirectFlag==1) Set_Selection(move_flag,0,6);
        else 
        {
            if(DirectFlag==1) Set_Selection(move_flag,menu_flag_temp,menu_flag_temp-1);
            else if(DirectFlag==2) Set_Selection(move_flag,menu_flag_temp-2,menu_flag_temp-1);
        }
        
    }
}

void Set_Selection(uint8_t move_flag,uint8_t Pre_Selection,uint8_t New_Selection)
{
    if(move_flag==1)
    {
        pre_Selection=Pre_Selection;
        new_Selection=New_Selection;
    }

    Menu_Animation();
}

void Menu_Animation(void)
{
    OLED_Clear();
    OLED_ShowImage(42,10,44,44,Frame);

    if(pre_Selection>new_Selection)
    {
        if(pre_Selection==6&&new_Selection==0)
        {
            x_pre-=Speed;
            if(x_pre==0)
            {
                x_pre=48;
                move_flag=0;
                //更新pre_Selection
                pre_Selection=0;
            }
        }
        else 
        {
            x_pre+=Speed;
            if(x_pre==96)
            {
                x_pre=48;
                move_flag=0;
                //更新pre_Selection
                --pre_Selection;
            }
        }
    }

    if(pre_Selection<new_Selection)
    {
        if(pre_Selection==0&&new_Selection==6)
        {
            x_pre+=Speed;
            if(x_pre==96)
            {
                x_pre=48;
                move_flag=0;
                //更新pre_Selection
                pre_Selection=6;
            }
        }
        else 
        {
           x_pre-=Speed;
           if(x_pre==0)
            {
                x_pre=48;
                move_flag=0;
                //更新pre_Selection
                ++pre_Selection;
            } 
        }
    }

    int temp1=pre_Selection-2;
    int temp2=pre_Selection-1;
    OLED_ShowImage(x_pre-96,16,32,32,
        Menu_Graph[(temp1>=0)?temp1:7+temp1]);
    OLED_ShowImage(x_pre-48,16,32,32,
        Menu_Graph[(temp2>=0)?temp2:7+temp2]);
    OLED_ShowImage(x_pre,16,32,32,Menu_Graph[pre_Selection]);
    OLED_ShowImage(x_pre+48,16,32,32,Menu_Graph[(pre_Selection+1)%7]);
    OLED_ShowImage(x_pre+96,16,32,32,Menu_Graph[(pre_Selection+2)%7]);
	
	OLED_Update();
}

void MoveToFunction(void)
{
    int temp1=pre_Selection-1;
    int temp2=pre_Selection+1;
    temp1=((temp1>0)?temp1:7+temp1);
    temp2%=7;
    for(uint8_t i=1;i<7;i++)
    {
		OLED_Clear();
        OLED_ShowImage(x_pre-48,16+8*i,32,32,Menu_Graph[temp1]);
        OLED_ShowImage(x_pre,16+8*i,32,32,Menu_Graph[pre_Selection]);
        OLED_ShowImage(x_pre+48,16+8*i,32,32,Menu_Graph[temp2]);
		OLED_Update();
    }
}

uint8_t StopWatch_flag=0;
uint8_t BackStopWatch_flag=0;//控制是否后台计时
uint8_t hour=0,minute=0,second=0;

void StopWatch_Tick(void)
{
    static uint8_t count=0;
    if(StopWatch_flag==4)
    {
        count=0;
        hour=0;
        minute=0;
        second=0;
    }
    if(StopWatch_flag==2||StopWatch_flag==1&&BackStopWatch_flag==1)
    {
        if(++count>100)
        {
            if(second++>59)
            {
                second=0;
                if(minute++>59)
                {
                    minute=0;
                    hour++;
                }
            }
            count=0;
        }
    }
    
}

void Show_StopWatch_UI(void)
{
    OLED_ShowImage(0,0,16,16,Return);
    OLED_Printf(32,20,OLED_8X16,"%02d:%02d:%02d",hour,minute,second);
	OLED_ShowString(8,44,"开始",OLED_8X16);
	OLED_ShowString(48,44,"停止",OLED_8X16);
	OLED_ShowString(88,44,"清除",OLED_8X16);
}

void StopWatch(void)
{
    uint8_t StopWatchFlag_temp=1;
    while(1)
    {
        KeyNum=Key_GetNum();
        if(KeyNum==1)//上一项
        {
            StopWatchFlag_temp--;
            if(StopWatchFlag_temp<1) StopWatchFlag_temp=4;
        }
        else if(KeyNum==2)//下一项
        {
            StopWatchFlag_temp++;
            if(StopWatchFlag_temp>4) StopWatchFlag_temp=1;
        }
        else if(KeyNum==3)
        {
            StopWatch_flag=StopWatchFlag_temp;
            if(StopWatch_flag==1) return;
            if(StopWatch_flag==2) BackStopWatch_flag=1;
            if(StopWatch_flag==3||StopWatch_flag==4) BackStopWatch_flag=0;
        }

        switch(StopWatchFlag_temp)
        {
            case 1:
                Show_StopWatch_UI();
                OLED_ReverseArea(0,0,16,16);
                OLED_Update();
                break;
            case 2:
                Show_StopWatch_UI();
                OLED_ReverseArea(8,44,32,16);
                OLED_Update();
                break;
            case 3:
                Show_StopWatch_UI();
                OLED_ReverseArea(48,44,32,16);
                OLED_Update();
                break;
            case 4:
                Show_StopWatch_UI();
                OLED_ReverseArea(88,44,32,16);
                OLED_Update();
                break;
            default:
                break;
        }
    }
}

uint8_t LEDflag=0;
void Show_LED_UI(void)
{
    OLED_ShowImage(0,0,16,16,Return);
	OLED_ShowString(20,20,"ON",OLED_12X24);
    OLED_ShowString(72,20,"OFF",OLED_12X24);
}

void LED(void)
{
    uint8_t LEDflag_temp=1;
    while(1)
    {
        KeyNum=Key_GetNum();
        if(KeyNum==1)
        {
            LEDflag_temp--;
            if(LEDflag_temp<1) LEDflag_temp=3;
        }
        else if(KeyNum==2)
        {
            LEDflag_temp++;
            if(LEDflag_temp>3) LEDflag_temp=1;
        }
        else if(KeyNum==3)
        {
            LEDflag=LEDflag_temp;
        }

        if(LEDflag==1)
        {
            LEDflag=0;
            return;
        }
        else if(LEDflag==2) LED1_ON();
        else if(LEDflag==3) LED1_OFF();

        switch(LEDflag_temp)
        {
            case 1:
                Show_LED_UI();
                OLED_ReverseArea(0,0,16,16);
                OLED_Update();
                break;
            case 2:
                Show_LED_UI();
                OLED_ReverseArea(20,20,24,24);
                OLED_Update();
                break;
            case 3:
                Show_LED_UI();
                OLED_ReverseArea(72,20,36,24);
                OLED_Update();
                break;
            default:
                break;
        }
    }
}

#define PI 3.141592653f
#define RAD_TO_DEG 57.29578f //角度转弧度系数

#define ACCEL_SENSITIVITY 2048.0f
#define GYRO_SENSITIVITY  16.4f

float Roll  = 0;  // X 轴
float Pitch = 0;  // Y 轴
float Yaw   = 0;  // Z 轴 
float Delta_t = 0.005f;  // 5ms 采样周期
float Kp = 0.1f;         // 滤波系数


void Show_MPU6050_UI(void)
{
    OLED_ShowImage(0,0,16,16,Return);
	OLED_Printf(0,16,OLED_8X16,"Roll: %.2f",Roll);
	OLED_Printf(0,32,OLED_8X16,"Pitch:%.2f",Pitch);
	OLED_Printf(0,48,OLED_8X16,"Yaw:  %.2f",Yaw);
}

int16_t ax, ay, az;
int16_t gx, gy, gz;
float ax_f, ay_f, az_f;
float gx_f, gy_f, gz_f;
float pitch_a, roll_a;

void MPU6050_Calculation(void)
{
    Delay_ms(5);
    

	// 1. 读取数据
	MPU6050_GetData(&ax, &ay, &az, &gx, &gy, &gz);

	// 2. 单位转换
	ax_f = (float)ax / ACCEL_SENSITIVITY;
	ay_f = (float)ay / ACCEL_SENSITIVITY;
	az_f = (float)az / ACCEL_SENSITIVITY;

	gx_f = (float)gx / GYRO_SENSITIVITY;
	gy_f = (float)gy / GYRO_SENSITIVITY;
	gz_f = (float)gz / GYRO_SENSITIVITY;

    // 解决Yaw自增
    if(-8.5<gz_f&&gz_f<0)
    {
        gz_f = 0;
    }
    if(gz_f<0) gz_f+=8.5;
    if(gz_f>0) gz_f*=2;

    // 3. 陀螺仪积分
    Roll  += gx_f * Delta_t;   // X 轴
	Pitch += gy_f * Delta_t;   // Y 轴
	Yaw   += gz_f * Delta_t;   // Z 轴

    // 4. 加速度计计算（只能算 X/Y 轴）,atan2 (对边，邻边) → 输出【倾斜的弧度】
    pitch_a = atan2(-ax_f, sqrt(ay_f*ay_f + az_f*az_f)) * RAD_TO_DEG;
	roll_a  = atan2(ay_f, az_f) * RAD_TO_DEG;

    // 5. 互补滤波（稳定 X/Y 轴）
    Roll  = Roll  * (1-Kp) + roll_a  * Kp;
	Pitch = Pitch * (1-Kp) + pitch_a * Kp;
}

void Show_MPU6050_InitialData(void)
{
    MPU6050_GetData(&ax, &ay, &az, &gx, &gy, &gz);
    OLED_ShowSignedNum(1, 16, ax, 5,OLED_8X16);					//OLED显示数据
	OLED_ShowSignedNum(1, 32, ay, 5,OLED_8X16);
	OLED_ShowSignedNum(1, 48, az, 5,OLED_8X16);
	OLED_ShowSignedNum(72, 16, gx, 5,OLED_8X16);
	OLED_ShowSignedNum(72, 32, gy, 5,OLED_8X16);
	OLED_ShowSignedNum(72, 48, gz, 5,OLED_8X16);
    OLED_Update();
}

void MPU6050(void)
{
    while(1)
    {
        KeyNum=Key_GetNum();
        if(KeyNum==3)
        {
            OLED_Clear();
            OLED_Update();
            return;
        }

        OLED_Clear();
        // Show_MPU6050_InitialData();
        MPU6050_Calculation();
        Show_MPU6050_UI();
        OLED_ReverseArea(0,0,16,16);
        OLED_Update();
    }
}
