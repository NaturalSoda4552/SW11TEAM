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


// ���� ��� ȭ��
class EventSceneManager {
public:
	int event_key = 0;

	int randomEventKey;

	int HpAndGold_event_key; // 0: ���� �� /  1: 1�� ������ �� / 2: 2�� ������ �� / 3: ���ٸ���
	int HG_isLeft2;
	int HG_isRight2;
	int HG_isLeft3;
	int HG_isRight3;

	int Gold_event_key; // 0: ���� ���� �� / 1: ���� �� ��
	int G_event; // 1 ~ 70: ��� ȹ�� / 71~99: ��� ���� / 100: ���� ��� ȹ��
	int G_random_gold; // ���� �߻��� ��带 ������ ����

public:
	EventSceneManager();
	~EventSceneManager();

	/*void gotoPos(int x, int y);
	void drawOutLine();
	void drawSquare(int startX, int startY, int dx, int dy);*/

	void inputKey();

	void drawShopPlayerInfo();

	void drawEventScene();				// ���� �̺�Ʈ �߻� - �Լ� ���ο��� ó��

	void drawHpAndGoldScene();			// 1. ü�� ȸ��
	void drawHGScene(int idx);
    void drawHGSceneExplanation(int idx);
	void drawHGSelectButton(int idx);
	void drawHGSelectArrow(int idx);
	void deleteHGSelectArrow(int idx);

	void drawGoldScene();				// 2. ��� ȹ��
	void drawGScene(int idx);
	void drawGSceneExplanation(int idx);
	void drawGSelectButton(int idx);
	void drawGSelectArrow(int idx);
	void deleteGSelectArrow(int idx);



	void drawRandomDebuffScene();		// 3. ���� ����� ȹ��
	void drawDbScene(int idx);
	void drawDbSceneExplanation(int idx);


	void drawGameOverScene();
	void drawGoSceneArrow(int idx);
	void deleteGoSceneArrow(int idx);
};
