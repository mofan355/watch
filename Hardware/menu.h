#ifndef _MENU_H
#define _MENU_H

void Peripheral_Init(void);
void Show_Clock_UI(void);
int First_Page_Clock(void);
void SettingPage(void);
void Menu(void);
void Set_Selection(uint8_t move_flag,uint8_t Pre_Selection,uint8_t New_Selection);
void Menu_Animation(void);

#endif
