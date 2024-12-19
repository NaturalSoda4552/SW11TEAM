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
class ShopSceneManager {
public:
	int shop_key;
	int shopItemIdx; // 0: 체력 1: 판매 2: 패시브 3: 액티브 4: 나가기

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

	void drawItemsOutLine(); // 상점 판매 항목들 테두리
	void drawShopPlayerInfo();
	void drawItemArrow();
	void deleteItemArrow();

	void drawPassivRemove(); // 패시브 제거 
	void drawPassiveItem();
	void drawActiveItem();

	void drawItemExplanation(); // 상점 항목에 대한 설명
								// 랜덤으로 뜨는 아이템 설명은 밑에 쓰기
	void SellingPassiveItem(); // 패시브 제거 항목 선택 시 또 다른 창에서 키입력 반복
	void drawSellingArrow(int idx); // 패시브 제거 항목에서의 화살표 그리기
	void deleteSellingArrow(int idx); // 패시브 제거 항목에서의 화살표 지우기
	void drawDeleteItemExplanation(int idx); // 패시브 제거 항목에서의 설명창

	void ApplyItem(); // 선택한 항목 적용 (회복, 제거, 구매 등)
	
	void drawShopAsset();
	
	void drawItemCheck();
	void drawCheckExplanation(int colIdx, int rowIdx);
	void drawCheckArrow(int colIdx, int rowIdx);
	void deleteCheckArrow(int colIdx, int rowIdx);
};
