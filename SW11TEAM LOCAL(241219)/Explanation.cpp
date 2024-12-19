

#include "Data.h"
#include "Explanation.h"

HANDLE hCO = GetStdHandle(STD_OUTPUT_HANDLE);

int startX = 70;
int startY = 2;

// �� ����â
void drawMapExplanation() {
	// Ű �Է��� ���� ������ ���, �Ǵ� ����â �ѱ��
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
			// space�� -> ����â Ż��
			if (key == 32) {
				// �ִ� ������ŭ �� �����ָ�
				if (mapExplanationIdx >= 1) {
					// ����â ����� + ���� ��� ������ �����
					// drawSquare(35, 2, 15, 6);
					for (int i = 0; i < 8; i++) {
						gotoPos(68, 1 + i);  cout << "                                  ";
					}
					break;
				}
				else { // �� �Ⱥ����ָ�
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
	// ����â ����� �׵θ� �ٽ� �׸���
	SetConsoleTextAttribute(hCO, 3);
	drawSquare((startX - 2) / 2, 1, 16, 7);
	SetConsoleTextAttribute(hCO, 7);

	gotoPos(startX + 18, startY + 5); cout << "[SPACE] " << idx + 1 << "/2";
	switch (idx) {
	case 0:
		gotoPos(startX, startY + 0); cout << "�� ȭ���Դϴ�.";
		gotoPos(startX, startY + 1); cout << "���� Ŭ���� �� �������� �̵�";
		gotoPos(startX, startY + 2); cout << "��: �̵� ��� ON";
		gotoPos(startX, startY + 3); cout << "��: �̵� ��� OFF";
		
		break;
	case 1:
		gotoPos(startX, startY + 0); cout << "��: �̵� ��� �� ���� �̵�";
		gotoPos(startX, startY + 1); cout << "��: �̵� ��� �� �Ʒ��� �̵�";
		gotoPos(startX, startY + 2); cout << "Space: �̵�";
		gotoPos(startX, startY + 3); cout << "Tab: ����â Ȯ�� ���";
		
		break;
	}
}

void drawShopExplanation() {
	// Ű �Է��� ���� ������ ���, �Ǵ� ����â �ѱ��
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
			// space�� -> ����â Ż��
			if (key == 32) {
				// �ִ� ������ŭ �� �����ָ�
				if (shopExplanationIdx >= 1) {
					// ����â ����� + ���� ��� ������ �����
					// drawSquare(35, 2, 15, 6);
					for (int i = 0; i < 8; i++) {
						gotoPos(68, 1 + i);  cout << "                                  ";
					}
					break;
				}
				else { // �� �Ⱥ����ָ�
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
	// ����â ����� �׵θ� �ٽ� �׸���
	SetConsoleTextAttribute(hCO, 3);
	drawSquare((startX-2)/2, 1, 16, 7);
	SetConsoleTextAttribute(hCO, 7);

	gotoPos(startX + 18, startY + 5); cout << "[SPACE] " << idx + 1 << "/2";
	switch (idx) {
	case 0:
		gotoPos(startX, startY + 0); cout << "���� ȭ���Դϴ�.";
		gotoPos(startX, startY + 1); cout << "�׸� �籸�� �Ұ�";
		// gotoPos(startX, startY + 2); cout << "Q: ���� ��Ƽ�� Ȯ��";
		// gotoPos(startX, startY + 3); cout << "W: ���� �нú� Ȯ��";
		break;
	case 1:
		gotoPos(startX, startY + 0); cout << "��: ������ ��ǰ���� �̵�";
		gotoPos(startX, startY + 1); cout << "��: ���� ��ǰ���� �̵�";
		gotoPos(startX, startY + 2); cout << "Q: ���� ������ Ȯ��";
		gotoPos(startX, startY + 3); cout << "Space: ����";
		break;
	}
}

void drawBattleExplanation() {
	// Ű �Է��� ���� ������ ���, �Ǵ� ����â �ѱ��
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
			// space�� -> ����â Ż��
			if (key == 32) {
				// �ִ� ������ŭ �� �����ָ�
				if (battleExplanationIdx >= 1) {
					// ����â ����� + ���� ��� ������ �����
					// drawSquare(35, 2, 15, 6);
					for (int i = 0; i < 8; i++) {
						gotoPos(68, 1 + i);  cout << "                                  ";
					}
					break;
				}
				else { // �� �Ⱥ����ָ�
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
	// ����â ����� �׵θ� �ٽ� �׸���
	SetConsoleTextAttribute(hCO, 3);
	drawSquare((startX - 2) / 2, 1, 16, 7);
	SetConsoleTextAttribute(hCO, 7);

	gotoPos(startX + 18, startY + 5); cout << "[SPACE] " << idx + 1 << "/2";
	switch (idx) {
	case 0:
		gotoPos(startX, startY + 0); cout << "���� ȭ���Դϴ�.";
		gotoPos(startX, startY + 2); cout << "ī�� ���� ����, �� ��";
		gotoPos(startX, startY + 3); cout << "���� �� ������&��ų ��� ����";
		break;
	case 1:
		gotoPos(startX, startY + 0); cout << "��: ������ ������ �̵�";
		gotoPos(startX, startY + 1); cout << "��: ������ ���� �̵�";
		gotoPos(startX, startY + 2); cout << "��,��: ������ ���Ʒ� �̵�"; 
		gotoPos(startX, startY + 3); cout << "Space: ����";
		break;
	}
}