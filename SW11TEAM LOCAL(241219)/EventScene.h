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


// 게임 방법 화면
class EventSceneManager {
public:
	int event_key = 0;

	int randomEventKey;

	int HpAndGold_event_key; // 0: 동굴 앞 /  1: 1차 갈림길 앞 / 2: 2차 갈림길 앞 / 3: 막다른길
	int HG_isLeft2;
	int HG_isRight2;
	int HG_isLeft3;
	int HG_isRight3;

	int Gold_event_key; // 0: 상자 열기 전 / 1: 상자 연 후
	int G_event; // 1 ~ 70: 골드 획득 / 71~99: 골드 감소 / 100: 많은 골드 획득
	int G_random_gold; // 랜덤 발생한 골드를 저장할 변수

public:
	EventSceneManager();
	~EventSceneManager();

	/*void gotoPos(int x, int y);
	void drawOutLine();
	void drawSquare(int startX, int startY, int dx, int dy);*/

	void inputKey();

	void drawShopPlayerInfo();

	void drawEventScene();				// 랜덤 이벤트 발생 - 함수 내부에서 처리

	void drawHpAndGoldScene();			// 1. 체력 회복
	void drawHGScene(int idx);
    void drawHGSceneExplanation(int idx);
	void drawHGSelectButton(int idx);
	void drawHGSelectArrow(int idx);
	void deleteHGSelectArrow(int idx);

	void drawGoldScene();				// 2. 골드 획득
	void drawGScene(int idx);
	void drawGSceneExplanation(int idx);
	void drawGSelectButton(int idx);
	void drawGSelectArrow(int idx);
	void deleteGSelectArrow(int idx);



	void drawRandomDebuffScene();		// 3. 랜덤 디버프 획득
	void drawDbScene(int idx);
	void drawDbSceneExplanation(int idx);


	void drawGameOverScene();
	void drawGoSceneArrow(int idx);
	void deleteGoSceneArrow(int idx);
};
