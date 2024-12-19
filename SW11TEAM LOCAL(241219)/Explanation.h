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

// 설명 툴팁 출력하는 함수

// 프로그램 실행 최초 1회만 출력
extern int isMapExplanation;
extern int isShopExplanation;
extern int isBattleExplanation;

// 메인 화면 설명창
// 전체적인 설명, 게임 시작 버튼에 대해서는 이름 및 직업 입력 추가 설명
void drawMainExplanation();
void deleteMainExplanation();

// 맵 설명창
void drawMapExplanation();
void deleteMapExplanation();
void drawMapExplanationByIdx(int idx);

//  상점 설명창
void drawShopExplanation();
void deleteShopExplanation();
void drawShopExplanationByIdx(int idx);

//  전투 설명창
void drawBattleExplanation();
void deleteBattleExplanation();
void drawBattleExplanationByIdx(int idx);

//  이벤트 설명창
void drawEventExplanation();
void deleteEventExplanation();

