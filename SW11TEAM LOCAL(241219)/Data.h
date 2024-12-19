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

using namespace std;


// �� ���� ����
int const MAP_MAX_X = 8; // 4 ���� ������
// �� ���� ����
int const MAP_MAX_Y = 3;

// ���� ���� �׵θ�
int const MAP_OUTLINE_X = (MAP_MAX_X+2) * 10 + 3;
int const MAP_OUTLINE_Y = (MAP_MAX_Y+1) * 8;

// �ܼ� ���� ����
#define CONSOLE_SIZE_X MAP_OUTLINE_X + 2 // �ܼ� �ʺ�
#define CONSOLE_SIZE_Y MAP_OUTLINE_Y + 1 // �ܼ� ����
#define TITLE "MAP v1"   // �ܼ� ����

// �������� Ÿ��
enum class RoomType {
	EMPTY,    // ��� ����
	DEFAULT,  // �⺻ 
	MONSTER,  // ���� 
	SHOP,     // ����
	EVENT,    // �̺�Ʈ 
	BOSS      // ���� 
};

void disableCursor();
void gotoPos(int x, int y);
void drawOutLine();
void drawSquare(int startX, int startY, int dx, int dy);
void deleteScene();



// �̰� ������ �۵� ����
extern int SceneManager;

extern int isBoss;

extern int MapCount;

