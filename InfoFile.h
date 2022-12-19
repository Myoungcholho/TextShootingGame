#pragma once
#include "structHeader.h"
#include "main.h"

extern char* fileStartPoint[FILE_MAX_NUM];
extern int f_count;
extern Enemy _Enemy[ENEMYNUM];

short my_atoi(short* input);
void stageInput(); //char* fileStartPoint[10], int p_count, Enemy e[20]
int InitFile(const char* str); //, char* fileStartPoint[10]