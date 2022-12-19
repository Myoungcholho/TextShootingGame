#pragma once

#define FILE_MAX_NUM 10
#define FILE_MAX_NAME 20
#define Screen_X 24
#define Screen_y 81
#define TITLE 0
#define GAME 1
#define CLEAR 2
#define OVER 3
#define END 4
#define MY_BULLET 14
#define ENEMYNUM 20
#define LOADING 5

/*메소드 부분*/
void Buffer_Flip(void);
void Buffer_Clear(void);
void Sprite_Draw(int iX, int iY, char chSprite);
void Rendering();
void player_shot();
void UpdateGame();
void Start_Rendering();
void Start_RenderingDraw();
void UpdateTitle();
void UpdateClear();
void Clear_Rendering();
void UpdateEnd();
void End_Rendering();
void Loding();