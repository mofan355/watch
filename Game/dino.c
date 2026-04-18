#include "stm32f10x.h"
#include "dino.h"
#include "OLED.h"
#include "stdlib.h"
#include "Delay.h"
#include "Key.h"
#include "math.h"
#include "menu.h"

uint16_t Score=0;
uint8_t GroundCount=0;
uint8_t Cloud_pos=0;
void Dino_Show_Ground(void)
{
    if(GroundCount<=128)
    {
        for(uint8_t i=0;i<128;i++)
        {
            OLED_DisplayBuf[7][i]=Ground[i+GroundCount];
        }
    }
    else
    {
        uint8_t old_Ground=256-GroundCount;
        for(uint8_t i=0;i<old_Ground;i++)
        {
            OLED_DisplayBuf[7][i]=Ground[i+GroundCount];
        }
        for(uint8_t i=old_Ground;i<128;i++)
        {
            OLED_DisplayBuf[7][i]=Ground[i-old_Ground];
        }
    }
}

uint8_t barrier_flag=0;
uint8_t barrier_count=0;

struct Object_Position barrier;
void Dino_Show_Barrier(void)
{
    if(barrier_count>=143)
    {
        barrier_flag=rand()%3;
    }
    OLED_ShowImage(127-barrier_count,44,16,18,Barrier[barrier_flag]);

    barrier.minX=127-barrier_count;
	barrier.maxX=143-barrier_count;
	barrier.minY=44;
	barrier.maxY=62;
}

uint8_t dino_jump_flag=0;//0:奔跑，1:跳跃
extern uint8_t KeyNum;
uint16_t jump_t;
uint8_t Jump_Pos;
extern double PI;
struct Object_Position dino;
void Dino_ShowDino(void)
{
    KeyNum=Key_GetNum();
	if(KeyNum==1)dino_jump_flag=1;
	Jump_Pos=28*sin((float)(PI*jump_t/100));
	
	if(dino_jump_flag==0)
	{
		if(barrier_count%2==0)OLED_ShowImage(0,41,16,18,Dino[0]);
		else OLED_ShowImage(0,41,16,18,Dino[1]);
	}
	else
	{
		OLED_ShowImage(0,41-Jump_Pos,16,18,Dino[2]);
	}
	
	dino.minX=0;
	dino.maxX=16;
	dino.minY=44-Jump_Pos;
	dino.maxY=62-Jump_Pos;
}

int isColliding(struct Object_Position *a,struct Object_Position *b)
{
	if((a->maxX>b->minX)&&(a->minX<b->maxX)&&(a->maxY>b->minY)&&(a->minY<b->maxY))
	{
		OLED_Clear();
		OLED_ShowString(28,24,"Game Over",OLED_8X16);
		OLED_Update();
		Delay_s(1);
		OLED_Clear();
		OLED_Update();
		return 1;
	}
	return 0;
}

void DinoGame_Pos_Init(void)
{
	Score=GroundCount=barrier_count=Cloud_pos=Jump_Pos=0;
}

void DinoGame(void)
{
    uint8_t return_flag=0;
    while(1)
    {
        OLED_Clear();
        OLED_ShowNum(96,0,Score,5,OLED_6X8);
        Dino_Show_Ground();
		Dino_Show_Barrier();
		OLED_ShowImage(127-Cloud_pos,9,16,8,Cloud);
        Dino_ShowDino();
        OLED_Update();

        return_flag=isColliding(&dino,&barrier);
		if(return_flag==1)
		{
			return;
		}
    }
}

void Dino_Tick(void)
{
    static uint8_t Score_flag=0;
    static uint8_t Ground_flag=0;
	
    if(Score_flag++>9)//100ms得一分
    {
        Score++;
    }
    if(Ground_flag++>0)//每10ms地面向左移动一个像素
    {
        if(GroundCount++>255) GroundCount=0;
		if(barrier_count++>143) barrier_count=0;
        Ground_flag=0;
    }
	if(Cloud_pos++>143) Cloud_pos=0;

    if(dino_jump_flag==1)
	{
		jump_t++;
		if(jump_t>=100)
		{
			jump_t=0;
			dino_jump_flag=0;
		}
	}
}
