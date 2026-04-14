#ifndef _SETTIME_H
#define _SETTIME_H

#include "stm32f10x.h"                  // Device header

void Show_SetTimePage_FirstUI(void);
void Show_SetTimePage_SecondUI(void);
void SetYear(void);
void SetMonth(void);
void SetDay(void);
void SetHour(void);
void SetMinute(void);
void SetSecond(void);
void SetTimePage(void);
void ChangeRTC_Time(uint8_t timeflag,uint8_t changeflag);

#endif
