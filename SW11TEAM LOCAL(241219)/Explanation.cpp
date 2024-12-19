

#include "Data.h"
#include "Explanation.h"

HANDLE hCO = GetStdHandle(STD_OUTPUT_HANDLE);

int startX = 70;
int startY = 2;

// 맵 설명창
void drawMapExplanation() {
	// 키 입력을 받을 때까지 대기, 또는 설명창 넘기기
	int mapExplanationIdx = 0;
	drawMapExplanationByIdx(mapExplanationIdx);

	while (1) {
		int key = 0;
		if (_kbhit() != 0) {
			key = _getch();
			if (key == 224) {
				key = _getch();

				if (key == 75) {

				}
				if (key == 77) {

				}
			}
			// space바 -> 설명창 탈출
			if (key == 32) {
				// 최대 개수만큼 다 보여주면
				if (mapExplanationIdx >= 1) {
					// 설명창 지우기 + 설명 요소 디자인 지우기
					// drawSquare(35, 2, 15, 6);
					for (int i = 0; i < 8; i++) {
						gotoPos(68, 1 + i);  cout << "                                  ";
					}
					break;
				}
				else { // 다 안보여주면
					mapExplanationIdx++;
					drawMapExplanationByIdx(mapExplanationIdx);
				}
			}
		}
	}
}
void deleteMapExplanation() {

}
void drawMapExplanationByIdx(int idx) {
	// 설명창 지우고 테두리 다시 그리기
	SetConsoleTextAttribute(hCO, 3);
	drawSquare((startX - 2) / 2, 1, 16, 7);
	SetConsoleTextAttribute(hCO, 7);

	gotoPos(startX + 18, startY + 5); cout << "[SPACE] " << idx + 1 << "/2";
	switch (idx) {
	case 0:
		gotoPos(startX, startY + 0); cout << "맵 화면입니다.";
		gotoPos(startX, startY + 1); cout << "보스 클리어 시 다음으로 이동";
		gotoPos(startX, startY + 2); cout << "→: 이동 명령 ON";
		gotoPos(startX, startY + 3); cout << "←: 이동 명령 OFF";
		
		break;
	case 1:
		gotoPos(startX, startY + 0); cout << "↑: 이동 명령 중 위로 이동";
		gotoPos(startX, startY + 1); cout << "↓: 이동 명령 중 아래로 이동";
		gotoPos(startX, startY + 2); cout << "Space: 이동";
		gotoPos(startX, startY + 3); cout << "Tab: 상태창 확인 토글";
		
		break;
	}
}

void drawShopExplanation() {
	// 키 입력을 받을 때까지 대기, 또는 설명창 넘기기
	int shopExplanationIdx = 0;
	drawShopExplanationByIdx(shopExplanationIdx);

	while (1) {
		int key = 0;
		if (_kbhit() != 0) {
			key = _getch();
			if (key == 224) {
				key = _getch();

				if (key == 75) {

				}
				if (key == 77) {

				}
			}
			// space바 -> 설명창 탈출
			if (key == 32) {
				// 최대 개수만큼 다 보여주면
				if (shopExplanationIdx >= 1) {
					// 설명창 지우기 + 설명 요소 디자인 지우기
					// drawSquare(35, 2, 15, 6);
					for (int i = 0; i < 8; i++) {
						gotoPos(68, 1 + i);  cout << "                                  ";
					}
					break;
				}
				else { // 다 안보여주면
					shopExplanationIdx++;
					drawShopExplanationByIdx(shopExplanationIdx);
				}
			}
		}
	}
}
void deleteShopExplanation() {

}
void drawShopExplanationByIdx(int idx) {
	// 설명창 지우고 테두리 다시 그리기
	SetConsoleTextAttribute(hCO, 3);
	drawSquare((startX-2)/2, 1, 16, 7);
	SetConsoleTextAttribute(hCO, 7);

	gotoPos(startX + 18, startY + 5); cout << "[SPACE] " << idx + 1 << "/2";
	switch (idx) {
	case 0:
		gotoPos(startX, startY + 0); cout << "상점 화면입니다.";
		gotoPos(startX, startY + 1); cout << "항목 재구매 불가";
		// gotoPos(startX, startY + 2); cout << "Q: 보유 액티브 확인";
		// gotoPos(startX, startY + 3); cout << "W: 보유 패시브 확인";
		break;
	case 1:
		gotoPos(startX, startY + 0); cout << "→: 오른쪽 상품으로 이동";
		gotoPos(startX, startY + 1); cout << "←: 왼쪽 상품으로 이동";
		gotoPos(startX, startY + 2); cout << "Q: 보유 아이템 확인";
		gotoPos(startX, startY + 3); cout << "Space: 선택";
		break;
	}
}

void drawBattleExplanation() {
	// 키 입력을 받을 때까지 대기, 또는 설명창 넘기기
	int battleExplanationIdx = 0;
	drawBattleExplanationByIdx(battleExplanationIdx);

	while (1) {
		int key = 0;
		if (_kbhit() != 0) {
			key = _getch();
			if (key == 224) {
				key = _getch();

				if (key == 75) {

				}
				if (key == 77) {

				}
			}
			// space바 -> 설명창 탈출
			if (key == 32) {
				// 최대 개수만큼 다 보여주면
				if (battleExplanationIdx >= 1) {
					// 설명창 지우기 + 설명 요소 디자인 지우기
					// drawSquare(35, 2, 15, 6);
					for (int i = 0; i < 8; i++) {
						gotoPos(68, 1 + i);  cout << "                                  ";
					}
					break;
				}
				else { // 다 안보여주면
					battleExplanationIdx++;
					drawBattleExplanationByIdx(battleExplanationIdx);
				}
			}
		}
	}
}
void deleteBattleExplanation() {

}
void drawBattleExplanationByIdx(int idx) {
	// 설명창 지우고 테두리 다시 그리기
	SetConsoleTextAttribute(hCO, 3);
	drawSquare((startX - 2) / 2, 1, 16, 7);
	SetConsoleTextAttribute(hCO, 7);

	gotoPos(startX + 18, startY + 5); cout << "[SPACE] " << idx + 1 << "/2";
	switch (idx) {
	case 0:
		gotoPos(startX, startY + 0); cout << "전투 화면입니다.";
		gotoPos(startX, startY + 2); cout << "카드 두장 선택, 합 비교";
		gotoPos(startX, startY + 3); cout << "선택 전 아이템&스킬 사용 가능";
		break;
	case 1:
		gotoPos(startX, startY + 0); cout << "→: 선택지 오른쪽 이동";
		gotoPos(startX, startY + 1); cout << "←: 선택지 왼쪽 이동";
		gotoPos(startX, startY + 2); cout << "↑,↓: 선택지 위아래 이동"; 
		gotoPos(startX, startY + 3); cout << "Space: 선택";
		break;
	}
}