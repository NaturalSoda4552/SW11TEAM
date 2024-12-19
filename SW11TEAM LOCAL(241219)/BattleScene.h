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


// ���� ȭ��
class BattleSceneManager {
public:
	int battle_key;

	int action_key; // 0: ��Ȱ��ȭ, 1: Ȱ��ȭ
	int action_selected; // 0: ����, 1: ������, 2: ��ų, 3: EMPTY
	
	int round_key; // �� ���� ���� �� 0, �ƴϸ� 1 (����� ���� 1ȸ)
	

public:
	BattleSceneManager();
	~BattleSceneManager();

	/*void gotoPos(int x, int y);
	void drawOutLine();
	void drawSquare(int startX, int startY, int dx, int dy);*/

	void inputKey();

	// ���� ȭ��
	void drawBattleScene();

	// �÷��̾�� ���
	void drawUnit();

	// ü�¹� �׸���
	void drawHealthBar();
	// �� & �������� ���� �׸��� - ���
	void drawDeckAndTrash();
	// ��Ƽ�� ��ų �׸��� - ���
	void drawItems();

	// �÷��̾� �ڵ� �׵θ� �׸���
	void drawHandOutLine();
	// �÷��̾� �ڵ� �׸���
	void drawHand();
	// ī�� ������ ���ڷ� �޾� �׸��� �Լ�
	void drawEachCard();

	// �÷��̾� �ൿ ������
	void drawActionBar();
	// �÷��̾� �ൿ ���� ȭ��ǥ
	void drawActionSelectArrow();

	// ������ �� ī�� �׸���
	void drawEnemySelectedCard();

	// �ൿ - ����
	int action_Select();
	// �ൿ - ������

	// �ൿ - ��ų

	// �ൿ - 

	// ���� �׸���
	void drawBonusBook();
	// �¸� ȭ�� - ���͸� �����߸��� ����âó�� �׸� ������ ���� ��� �� ǥ��
	
	// ���ӿ��� ȭ��
	void drawGameOverScene();
	void drawGoSceneArrow(int idx);
	void deleteGoSceneArrow(int idx);

	void drawItemCheck();
	void drawCheckExplanation(int colIdx, int rowIdx);
	void drawCheckArrow(int colIdx, int rowIdx);
	void deleteCheckArrow(int colIdx, int rowIdx);
};
