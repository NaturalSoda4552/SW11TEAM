#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <conio.h>
#include <windows.h>

// ���� ���� ����ϴ� �Լ�

// ���α׷� ���� ���� 1ȸ�� ���
extern int isMapExplanation;
extern int isShopExplanation;
extern int isBattleExplanation;

// ���� ȭ�� ����â
// ��ü���� ����, ���� ���� ��ư�� ���ؼ��� �̸� �� ���� �Է� �߰� ����
void drawMainExplanation();
void deleteMainExplanation();

// �� ����â
void drawMapExplanation();
void deleteMapExplanation();
void drawMapExplanationByIdx(int idx);

//  ���� ����â
void drawShopExplanation();
void deleteShopExplanation();
void drawShopExplanationByIdx(int idx);

//  ���� ����â
void drawBattleExplanation();
void deleteBattleExplanation();
void drawBattleExplanationByIdx(int idx);

//  �̺�Ʈ ����â
void drawEventExplanation();
void deleteEventExplanation();

