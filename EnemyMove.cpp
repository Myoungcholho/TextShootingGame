#include "EnemyMove.h"

void Enemy_Move_1(Enemy* e, int mCnt)
{
	int move[] = { 1,1,1,-1,-1,-1 };

	e->E_x = e->E_x + move[mCnt];
}

void Enemy_Move_0(Enemy* e, int mCnt)
{
	int move[] = { 1,1,1,-1,-1,-1 };

	e->E_y = e->E_y + move[mCnt];
}

void EnemyMove()
{
	static int mCnt = 0;
	for (int i = 0; i < ENEMYNUM; ++i)
	{
		if (_Enemy[i].isValid) {
			if (_Enemy[i].type == 0)
			{
				// type 0 
				Enemy_Move_0(&_Enemy[i], mCnt);
			}

			else if (_Enemy[i].type == 1)
			{
				//type 1 오른 2 왼쪽 2
				Enemy_Move_1(&_Enemy[i], mCnt);
			}
		}
	}
	if (mCnt < 5)
		++mCnt;
	else
		mCnt = 0;
}

/*

7. 적군 이동의 패턴 index

void EnemyMove(Enemy* e)
{
	static int mCnt = 0;
	...
	Enemy_Move_0(&e[i], mCnt);
	Enemy_Move_1(&e[i], mCnt);

	if (mCnt < 5)
		++mCnt;
	else
		mCnt = 0;


모든 적군들의 이동 패턴이 5개로 고정이며 static mCnt 값으로 움직이고 있습니다.
이는 모든 적이 언제나 항상 똑같이만 움직일 수 있다는 설계 입니다.

적군마다 이동 패턴의 개수가 다르다면, 적군의 생성 시점이 다르다면 어떻게 되는 것일까요 ?

EnemyMove 에서 사용하는 static int mCnt 변수는 적군마다 개별적으로 존재해야하는 대상 입니다.






# 이외에는 큰 문제는 없으나 cpp 분리나 함수의 분리가 조금 아쉽습니다.

함수로 나눈 부분이나 cpp 나눈 부분은 너무 억지스럽게 겨우겨우 분리 한 느낌입니다.
정작 함수로 나누어지면 좋을 부분들, cpp 가 분리되면 좋을 부분들은 한 덩어리로 되어 있습니다.


프로그래밍 자체가 너무 익숙하지 않습니다. 다양한 프로그래밍의 연습이 필요합니다.


*/