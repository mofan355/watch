#ifndef _DINO_H
#define _DINO_H

struct Object_Position{
	uint8_t minX,minY,maxX,maxY;
};

void DinoGame(void);
void Dino_Tick(void);
void Dino_Show_Ground(void);
void Dino_Show_Barrier(void);
void Dino_ShowDino(void);
int isColliding(struct Object_Position *a,struct Object_Position *b);
void DinoGame_Pos_Init(void);
#endif
