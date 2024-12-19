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


// 전투 화면
class BattleSceneManager {
public:
	int battle_key;

	int action_key; // 0: 비활성화, 1: 활성화
	int action_selected; // 0: 선택, 1: 아이템, 2: 스킬, 3: EMPTY
	
	int round_key; // 매 라운드 시작 시 0, 아니면 1 (라운드당 최초 1회)
	

public:
	BattleSceneManager();
	~BattleSceneManager();

	/*void gotoPos(int x, int y);
	void drawOutLine();
	void drawSquare(int startX, int startY, int dx, int dy);*/

	void inputKey();

	// 전투 화면
	void drawBattleScene();

	// 플레이어와 상대
	void drawUnit();

	// 체력바 그리기
	void drawHealthBar();
	// 덱 & 쓰레기통 정보 그리기 - 토글
	void drawDeckAndTrash();
	// 액티브 스킬 그리기 - 토글
	void drawItems();

	// 플레이어 핸드 테두리 그리기
	void drawHandOutLine();
	// 플레이어 핸드 그리기
	void drawHand();
	// 카드 정보를 인자로 받아 그리는 함수
	void drawEachCard();

	// 플레이어 행동 선택지
	void drawActionBar();
	// 플레이어 행동 선택 화살표
	void drawActionSelectArrow();

	// 상대방이 낸 카드 그리기
	void drawEnemySelectedCard();

	// 행동 - 선택
	int action_Select();
	// 행동 - 아이템

	// 행동 - 스킬

	// 행동 - 

	// 족보 그리기
	void drawBonusBook();
	// 승리 화면 - 몬스터만 쓰러뜨리고 정보창처럼 네모 영역에 얻은 골드 등 표시
	
	// 게임오버 화면
	void drawGameOverScene();
	void drawGoSceneArrow(int idx);
	void deleteGoSceneArrow(int idx);

	void drawItemCheck();
	void drawCheckExplanation(int colIdx, int rowIdx);
	void drawCheckArrow(int colIdx, int rowIdx);
	void deleteCheckArrow(int colIdx, int rowIdx);
};
