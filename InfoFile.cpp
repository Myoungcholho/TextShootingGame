#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "InfoFile.h"


short my_atoi(short* input)
{
	char* imsi = (char*)input;
	short a = 0;

	for (int i = 0; i < 2; ++i)
	{
		a = a * 10 + (*imsi - '0');
		++imsi;
	}

	return a;
}


void stageInput() //char* fileStartPoint[FILE_MAX_NUM], int f_count, Enemy _Enemy[ENEMYNUM]
{
	FILE* pfile = NULL;
	int pileSize;

	pfile = fopen(fileStartPoint[f_count], "rt");
	if (pfile == NULL)
	{
		printf("���� �� �� ����");
		return;
	}

	fseek(pfile, 0, SEEK_END);
	pileSize = ftell(pfile);
	rewind(pfile);

	char* fileMemory = (char*)malloc(pileSize);
	char* fileMemory_reset = fileMemory;

	if (1 != fread(fileMemory, pileSize, 1, pfile))
	{
		// "rt"�� 0d 0A�� �ƴ϶�  1�� ��ȯ���� �ʰ� ����,, ��� ó���ؾ� �ұ�
	}

	int iCnt = 0;
	while (*fileMemory != 0x0a)
	{
		iCnt = iCnt*10 + (*fileMemory -'0');

		++fileMemory;
	}
	++fileMemory;

	for (int i = 0; i < iCnt; ++i)
	{
		_Enemy[i].isValid = *fileMemory - '0';
		fileMemory += 2;

		_Enemy[i].E_Hp = my_atoi((short*)fileMemory);
		fileMemory += 3;

		_Enemy[i].E_x = my_atoi((short*)fileMemory);
		fileMemory += 3;

		_Enemy[i].E_y = my_atoi((short*)fileMemory);
		fileMemory += 3;

		_Enemy[i].type = *fileMemory - '0';
		fileMemory += 2;
	}

	free(fileMemory_reset);
	fclose(pfile);
}

/* �������� ���� �о����*/
/* �ѹ��� �� �� */
int InitFile(const char* str) //, char* fileStartPoint[FILE_MAX_NUM]
{
	FILE* pfile;
	int pileSize;

	pfile = fopen(str, "rt");
	if (pfile == NULL)
	{
		printf("���� ���� ����");
		return 0;
	}
	fseek(pfile, 0, SEEK_END);
	pileSize = ftell(pfile);
	rewind(pfile);

	char* fileMemory = (char*)malloc(pileSize);
	char* fileMemory_reset = fileMemory;

	if (1 != fread(fileMemory, pileSize, 1, pfile))
	{

	}

	char* fileName[FILE_MAX_NUM];

	int p_iCnt = *fileMemory - '0';
	fileMemory += 2;

	for (int i = 0; i < p_iCnt; ++i)
	{
		fileName[i] = (char*)malloc(FILE_MAX_NAME);
		fileStartPoint[i] = fileName[i];
		// ���߿� free �ٵ� ���������� �س��µ� �Լ� ������ �ʱ�ȭ�Ǹ鼭 �����ʹ� �����־
		// ���ڱ� �ٸ� ������ �� �޸� ���� �����ϴ� ��찡 ���⳪?
		// ������ free�ؾ��� �� ������,, ��� �������� �ؾ�����
	}

	for (int i = 0; i < p_iCnt; ++i)
	{
		while (*fileMemory != 0x0a)
		{
			*fileName[i] = *fileMemory;

			++fileName[i];
			++fileMemory;
		}
		*fileName[i] = '\0';
		++fileMemory;
	}

	free(fileMemory_reset);

	return p_iCnt;
}