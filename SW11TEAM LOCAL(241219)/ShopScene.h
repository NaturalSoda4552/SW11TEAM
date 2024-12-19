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
class ShopSceneManager {
public:
	int shop_key;
	int shopItemIdx; // 0: ü�� 1: �Ǹ� 2: �нú� 3: ��Ƽ�� 4: ������

	int randomPassiveItemIdx;
	int randomActiveItemIdx;

	int isHpSold;
	int isDebuffSellingSold;
	int isActiveSold;
	int isPassiveSold;

	int cost_h;
	int cost_d;
	int cost_p;
	int cost_a;

public:
	ShopSceneManager();
	~ShopSceneManager();

	/*void gotoPos(int x, int y);
	void drawOutLine();
	void drawSquare(int startX, int startY, int dx, int dy);*/

	void inputKey();

	void drawShopScene();

	void drawItemsOutLine(); // ���� �Ǹ� �׸�� �׵θ�
	void drawShopPlayerInfo();
	void drawItemArrow();
	void deleteItemArrow();

	void drawPassivRemove(); // �нú� ���� 
	void drawPassiveItem();
	void drawActiveItem();

	void drawItemExplanation(); // ���� �׸� ���� ����
								// �������� �ߴ� ������ ������ �ؿ� ����
	void SellingPassiveItem(); // �нú� ���� �׸� ���� �� �� �ٸ� â���� Ű�Է� �ݺ�
	void drawSellingArrow(int idx); // �нú� ���� �׸񿡼��� ȭ��ǥ �׸���
	void deleteSellingArrow(int idx); // �нú� ���� �׸񿡼��� ȭ��ǥ �����
	void drawDeleteItemExplanation(int idx); // �нú� ���� �׸񿡼��� ����â

	void ApplyItem(); // ������ �׸� ���� (ȸ��, ����, ���� ��)
	
	void drawShopAsset();
	
	void drawItemCheck();
	void drawCheckExplanation(int colIdx, int rowIdx);
	void drawCheckArrow(int colIdx, int rowIdx);
	void deleteCheckArrow(int colIdx, int rowIdx);
};
