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


// 한 맵의 가로
int const MAP_MAX_X = 8; // 4 이하 오류남
// 한 맵의 세로
int const MAP_MAX_Y = 3;

// 실제 맵의 테두리
int const MAP_OUTLINE_X = (MAP_MAX_X+2) * 10 + 3;
int const MAP_OUTLINE_Y = (MAP_MAX_Y+1) * 8;

// 콘솔 관련 정보
#define CONSOLE_SIZE_X MAP_OUTLINE_X + 2 // 콘솔 너비
#define CONSOLE_SIZE_Y MAP_OUTLINE_Y + 1 // 콘솔 높이
#define TITLE "MAP v1"   // 콘솔 제목

// 스테이지 타입
enum class RoomType {
	EMPTY,    // 비어 있음
	DEFAULT,  // 기본 
	MONSTER,  // 몬스터 
	SHOP,     // 상점
	EVENT,    // 이벤트 
	BOSS      // 보스 
};

void disableCursor();
void gotoPos(int x, int y);
void drawOutLine();
void drawSquare(int startX, int startY, int dx, int dy);
void deleteScene();



// 이거 없으면 작동 안함
extern int SceneManager;

extern int isBoss;

extern int MapCount;

