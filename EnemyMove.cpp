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
				//type 1 ���� 2 ���� 2
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

7. ���� �̵��� ���� index

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


��� �������� �̵� ������ 5���� �����̸� static mCnt ������ �����̰� �ֽ��ϴ�.
�̴� ��� ���� ������ �׻� �Ȱ��̸� ������ �� �ִٴ� ���� �Դϴ�.

�������� �̵� ������ ������ �ٸ��ٸ�, ������ ���� ������ �ٸ��ٸ� ��� �Ǵ� ���ϱ�� ?

EnemyMove ���� ����ϴ� static int mCnt ������ �������� ���������� �����ؾ��ϴ� ��� �Դϴ�.






# �̿ܿ��� ū ������ ������ cpp �и��� �Լ��� �и��� ���� �ƽ����ϴ�.

�Լ��� ���� �κ��̳� cpp ���� �κ��� �ʹ� ���������� �ܿ�ܿ� �и� �� �����Դϴ�.
���� �Լ��� ���������� ���� �κе�, cpp �� �и��Ǹ� ���� �κе��� �� ����� �Ǿ� �ֽ��ϴ�.


���α׷��� ��ü�� �ʹ� �ͼ����� �ʽ��ϴ�. �پ��� ���α׷����� ������ �ʿ��մϴ�.


*/