#ifndef _MENU_H
#define _MENU_H

void Peripheral_Init(void);
void Show_Clock_UI(void);
int First_Page_Clock(void);
void SettingPage(void);
void Menu(void);
void Set_Selection(uint8_t move_flag,uint8_t Pre_Selection,uint8_t New_Selection);
void Menu_Animation(void);
void MoveToFunction(void);
void StopWatch(void);
void Show_StopWatch_UI(void);
void StopWatch_Tick(void);
void Show_LED_UI(void);
void LED(void);
void MPU6050(void);
void MPU6050_Calculation(void);
void Show_MPU6050_UI(void);
void Show_SelectGame_UI(void);
void SelectGame(void);
void Emoji(void);
void Show_Emoji_UI(void);
void Show_Gradienter_UI(void);
void Gradienter(void);
#endif
