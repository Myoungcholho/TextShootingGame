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
		printf("파일 열 수 없음");
		return;
	}

	fseek(pfile, 0, SEEK_END);
	pileSize = ftell(pfile);
	rewind(pfile);

	char* fileMemory = (char*)malloc(pileSize);
	char* fileMemory_reset = fileMemory;

	if (1 != fread(fileMemory, pileSize, 1, pfile))
	{
		// "rt"라서 0d 0A가 아니라  1을 반환하지 않고 있음,, 어떻게 처리해야 할까
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

/* 스테이지 파일 읽어오기*/
/* 한번만 할 것 */
int InitFile(const char* str) //, char* fileStartPoint[FILE_MAX_NUM]
{
	FILE* pfile;
	int pileSize;

	pfile = fopen(str, "rt");
	if (pfile == NULL)
	{
		printf("파일 오픈 실패");
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
		// 나중에 free 근데 지역변수로 해놨는데 함수 끝나고 초기화되면서 데이터는 남아있어도
		// 갑자기 다른 곳에서 이 메모리 번지 참조하는 경우가 생기나?
		// 끝날때 free해야할 것 같은데,, 어느 지점에서 해야하지
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