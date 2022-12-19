#include <stdio.h>
#include <memory.h>
#include <Windows.h>
#include "Console.h"
#include "structHeader.h"
#include "InfoFile.h"
#include "EnemyMove.h"
#include "main.h"

/*전역변수*/
char szScreenBuffer[Screen_X][Screen_y];
Bullet _Bullet[MY_BULLET];

Bullet Enemy_Bullet[ENEMYNUM];
Character player = {5, 20,20 };


bool Enemy_Init = false;
bool mode_check = true;

char* fileStartPoint[FILE_MAX_NUM];
Enemy _Enemy[ENEMYNUM];
int f_count = 0;
int p_iCnt;

/*전역변수*/

/* g_Scene*/
int g_Scene = TITLE;


/* MAIN */
int main(void)
{
	cs_Initial();
	
	p_iCnt = InitFile("stageinfo.txt"); //, fileStartPoint

	while (1)
	{
		{	
			switch (g_Scene)
			{
			case TITLE:
				UpdateTitle();
				break;
				
			case LOADING:
				Loding();
				break;

			case GAME:
				UpdateGame();
				break;

			case CLEAR:
				UpdateClear();
				break;

			case END:
				UpdateEnd();
				break;

			case OVER:
				return 0;


			}

		}
		Sleep(100);
		// 프레임 맞추기용 대기 10 Frame
	}
}

void Loding()
{
	if (p_iCnt > f_count) {
		stageInput(); //fileStartPoint, f_count, _Enemy
		++f_count;
		g_Scene = GAME;
	}
	else {
		g_Scene = OVER;
	}
}

void UpdateEnd()
{
	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		g_Scene = OVER;
	}
	End_Rendering();
}

void End_Rendering()
{
	Buffer_Clear();
	// End
	Sprite_Draw(20, 9, 'E');;
	Sprite_Draw(21, 9, 'N');
	Sprite_Draw(22, 9, 'D');

	Buffer_Flip();
}

void UpdateTitle()
{
	if ((GetAsyncKeyState(VK_UP) & 0x8001))
		mode_check = true;
	if ((GetAsyncKeyState(VK_DOWN) & 0x8001))
		mode_check = false;

	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		if (mode_check)
			g_Scene = LOADING;
		else
			g_Scene = OVER;
	}
	Start_Rendering();
}

void UpdateClear()
{
	if ((GetAsyncKeyState(VK_UP) & 0x8001))
		mode_check = true;
	if ((GetAsyncKeyState(VK_DOWN) & 0x8001))
		mode_check = false;

	if ((GetAsyncKeyState(VK_RETURN) & 0x8001))
	{
		if (mode_check) {
			/* 다음 스테이지로 넘어감*/
			/* 스테이지 전부 소모했으면 END*/
			if (p_iCnt == f_count)
				g_Scene = END;
			else {
				g_Scene = LOADING;
			}
		}
		else {
			g_Scene = END;
		}
	}
	Clear_Rendering();
}

void Clear_Rendering()
{
	Buffer_Clear();

	for (int i = 8; i < 72; ++i)
		Sprite_Draw(i, 4, '-');

	// Next Level 
	Sprite_Draw(20, 9, 'N');
	Sprite_Draw(21, 9, 'e');
	Sprite_Draw(22, 9, 'x');
	Sprite_Draw(23, 9, 't');
	Sprite_Draw(24, 9, ' ');
	Sprite_Draw(25, 9, 'L');
	Sprite_Draw(26, 9, 'e');
	Sprite_Draw(27, 9, 'v');
	Sprite_Draw(28, 9, 'e');
	Sprite_Draw(29, 9, 'l');

	Sprite_Draw(24, 14, 'N');
	Sprite_Draw(25, 14, 'e');
	Sprite_Draw(26, 14, 'x');
	Sprite_Draw(27, 14, 't');

	Sprite_Draw(23, 17, 'e');
	Sprite_Draw(24, 17, 'x');
	Sprite_Draw(25, 17, 'i');
	Sprite_Draw(26, 17, 't');


	if (mode_check) {
		Sprite_Draw(29, 14, '<');
		Sprite_Draw(30, 14, '-');
	}
	else {
		Sprite_Draw(29, 17, '<');
		Sprite_Draw(30, 17, '-');
	}

	for (int i = 8; i < 72; ++i)
		Sprite_Draw(i, 20, '-');

	Buffer_Flip();
}

void UpdateGame()
{
	/*적 무브*/
	EnemyMove(); //_Enemy

	/* hp char 변환*/
	player.char_Hp = player.C_Hp + 48;

	// 사용자 움직이는 키
	if ((GetAsyncKeyState(VK_LEFT) & 0x8001))
		--player.C_x;
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8001))
		++player.C_x;
	if ((GetAsyncKeyState(VK_UP) & 0x8001))
		--player.C_y;
	if ((GetAsyncKeyState(VK_DOWN) & 0x8001))
		++player.C_y;

	if (player.C_y > 23)
		player.C_y = 23;
	else if (player.C_y < 0)
		player.C_y = 0;

	if (player.C_x > 79)
		player.C_x = 79;
	else if (player.C_x < 0)
		player.C_x = 0;
	//사용자 총 쏘는 키
	player_shot();
	if ((GetAsyncKeyState(VK_SPACE) & 0x8001)) {
		for (int i = 0; i < MY_BULLET; ++i)
		{
			if (_Bullet[i].B_create == false)
			{
				_Bullet[i].B_create = true;
				_Bullet[i].B_tpye = true;
				_Bullet[i].B_x = player.C_x;
				_Bullet[i].B_y = player.C_y - 1;
				break;
			}

		}
	}
	//사용자의 총에 적군이 맞았다면
	for (int i = 0; i < MY_BULLET; i++)
	{
		if (_Bullet[i].B_create) {
			for (int Cntj = 0; Cntj < ENEMYNUM; Cntj++)
			{
				if (_Enemy[Cntj].isValid)
				{
					if (_Bullet[i].B_x == _Enemy[Cntj].E_x && _Bullet[i].B_y == _Enemy[Cntj].E_y)
					{
						_Enemy[Cntj].E_Hp = _Enemy[Cntj].E_Hp - 1;

						if (_Enemy[Cntj].E_Hp <= 0) {
							_Enemy[Cntj].E_Hp = 0;
							_Enemy[Cntj].isValid = false;
						}
					}
				}
			}
		}
	}

	/* 적군 총 쏘는 로직*/
	for (int i = 0; i < ENEMYNUM; ++i)
	{
		if (Enemy_Bullet[i].B_create)
		{
			Enemy_Bullet[i].B_y += 1;
			if (Enemy_Bullet[i].B_y > 23) {
				Enemy_Bullet[i].B_create = false;
			}
		}
	}
	for (int i = 0; i < ENEMYNUM; ++i)
	{
		if (_Enemy[i].isValid == true && Enemy_Bullet[i].B_create == false) // 아 살아있으니까 계속 초기화하네;; 그래서 죽으니까 내려가는거였구만
		{
			Enemy_Bullet[i].B_create = true;
			Enemy_Bullet[i].B_tpye = false;
			Enemy_Bullet[i].B_x = _Enemy[i].E_x;
			Enemy_Bullet[i].B_y = _Enemy[i].E_y + 1;
		}
	}

	//적군의 총에 아군이 맞았다면
	for (int i = 0; i < ENEMYNUM; i++)
	{
		if (Enemy_Bullet[i].B_create) {
			if (player.C_x == Enemy_Bullet[i].B_x && player.C_y == Enemy_Bullet[i].B_y)
			{
				player.C_Hp -= 1;
				if (player.C_Hp <= 0) {
					player.C_Hp = 0;

					// OVER로 게임 종료
					g_Scene = END;
				}
			}
		}
	}

	/*몬스터 다 잡았으면*/
	{
		bool mapClear = 0;
		for (int i = 0; i < ENEMYNUM; ++i)
		{
			if (_Enemy[i].isValid)
				++mapClear;
		}

		if (mapClear == 0) {
			g_Scene = CLEAR;
		}

	}
	/* 랜더부 */
	Rendering();
}

void Start_Rendering()
{
	Buffer_Clear();
	
	for(int i=8; i<72; ++i)
		Sprite_Draw(i, 4, '-');
	
	// Start End
	Start_RenderingDraw(); 
	if (mode_check) {
		Sprite_Draw(29, 14, '<');
		Sprite_Draw(30, 14, '-');
	}
	else {
		Sprite_Draw(29, 17, '<');
		Sprite_Draw(30, 17, '-');
	}

	for (int i = 8; i < 72; ++i)
		Sprite_Draw(i, 20, '-');

	Buffer_Flip();
}

void Start_RenderingDraw()
{
	Sprite_Draw(20, 9, 's');
	Sprite_Draw(21, 9, 'h');
	Sprite_Draw(22, 9, 'o');
	Sprite_Draw(23, 9, 'o');
	Sprite_Draw(24, 9, 't');
	Sprite_Draw(25, 9, 'i');
	Sprite_Draw(26, 9, 'n');
	Sprite_Draw(27, 9, 'g');
	Sprite_Draw(28, 9, ' ');
	Sprite_Draw(29, 9, 'g');
	Sprite_Draw(30, 9, 'a');
	Sprite_Draw(31, 9, 'm');
	Sprite_Draw(32, 9, 'e');

	Sprite_Draw(23, 14, 's');
	Sprite_Draw(24, 14, 't');
	Sprite_Draw(25, 14, 'a');
	Sprite_Draw(26, 14, 'r');
	Sprite_Draw(27, 14, 't');

	Sprite_Draw(23, 17, 'e');
	Sprite_Draw(24, 17, 'x');
	Sprite_Draw(25, 17, 'i');
	Sprite_Draw(26, 17, 't');
}

void Rendering()
{
	Buffer_Clear();

	/* Drawing */
	Sprite_Draw(76, 0, 'H');
	Sprite_Draw(77, 0, 'P');
	Sprite_Draw(78, 0, ':');
	Sprite_Draw(79, 0, player.char_Hp);
	

	Sprite_Draw(player.C_x, player.C_y, '#');

	for (int i = 0; i < ENEMYNUM; ++i)
	{
		if (_Enemy[i].isValid)
		{
			Sprite_Draw(_Enemy[i].E_x, _Enemy[i].E_y, '@');
		}
	}

	//아군 총알
	for (int i = 0; i < 14; ++i)
	{
		if (_Bullet[i].B_create)
		{
			Sprite_Draw(_Bullet[i].B_x, _Bullet[i].B_y, '^');
		}
	}

	//적군 총알
	for (int i = 0; i < ENEMYNUM; ++i)
	{
		if (Enemy_Bullet[i].B_create)
		{
			Sprite_Draw(Enemy_Bullet[i].B_x, Enemy_Bullet[i].B_y, 'o');
		}
	}

	/* Drawing */

	Buffer_Flip();
}

void player_shot()
{
	for (int i = 0; i < MY_BULLET; ++i)
	{
		if (_Bullet[i].B_create)
		{
			_Bullet[i].B_y -= 1;

			if (_Bullet[i].B_y < 0)
				_Bullet[i].B_create = false;
		}
	}
}

void Buffer_Flip(void)
{
	int iCnt;
	for (iCnt = 0; iCnt < Screen_X; iCnt++)
	{
		cs_MoveCursor(0, iCnt);
		printf(szScreenBuffer[iCnt]);
	}
	
	
}

void Buffer_Clear(void)
{
	int iCnt;
	memset(szScreenBuffer, ' ', Screen_y * Screen_X);

	for (iCnt = 0; iCnt < Screen_X; iCnt++)
	{
		szScreenBuffer[iCnt][Screen_y - 1] = '\0';
	}

}
void Sprite_Draw(int iX, int iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= Screen_y - 1 || iY >= Screen_X)
		return;

	szScreenBuffer[iY][iX] = chSprite;
}




