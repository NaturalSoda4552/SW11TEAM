
#include "Data.h"
#include "MainScene.h"
#include "HowToPlayScene.h"
#include "ScoreScene.h"

#include "MapScene.h"
#include "ShopScene.h"
#include "BattleScene.h"
#include "EventScene.h"

#include "Character.h"
#include "Item.h"

#include "Explanation.h"

// ȭ�� ���� Ű��
int SceneManager; 
// 0: ���� ȭ�� / 1: ���� ��� / 2: ���� Ȯ�� / 4: �� ȭ��
// 5: ���� ȭ�� / 6: �̺�Ʈ ȭ�� / 7: ���� ȭ��
// 0 -> 4: �̸� �Է� �� ���� ���� ȭ��
// 7 -> 0: �й� ȭ��

// �� ī��Ʈ
int MapCount;
// 1~5 (�� �ݺ� Ƚ��)

// ����â ����
int isMapExplanation;
int isShopExplanation;
int isBattleExplanation;
// ���α׷� ���� �� �� �� ���� �� ���� 1ȸ�� ����

void initGameSetting() {
    // �ܼ� ũ��� ���� ����
    char command[100];
    snprintf(command, sizeof(command), "mode con cols=%d lines=%d | title %s", CONSOLE_SIZE_X, CONSOLE_SIZE_Y, TITLE);
    // ��ɾ� ����
    system(command);

    SceneManager = 0; // ���� ȭ�� ����, ����Ʈ�� 0 (���� ȭ��)
    MapCount = 0; // �� ī��Ʈ, ����Ʈ�� 1 (�ִ� 5) : �ʿ� ���ڸ��� 1

    isMapExplanation = 0; // �� ���� ����
    isShopExplanation = 0; // ���� ���� ����
    isBattleExplanation = 0; // ���� ���� ����

    disableCursor(); // Ŀ�� ��Ȱ��ȭ
    drawOutLine(); // ������ �׵θ� �׸���
}

int main() {
    // ���� ȭ�� Ŭ����
    MainSceneManager a;
    HTPSceneManager b;
    ScoreSceneManager c;

    // MapSceneManager e; // extern �������� ���� �ּ�ó����
    ShopSceneManager f;
    EventSceneManager g;
    BattleSceneManager h; 

    // ���� ����
    initGameSetting();
    //p.Init_Player_Info(); // ����׿�, ������ ���� ���� �� ȣ��

    while (1) {
        if (SceneManager == 0) a.inputKey(); // ���� ȭ��
        if (SceneManager == 1) b.inputKey(); // ���� ��� ȭ��
        if (SceneManager == 2) c.inputKey(); // ���� ȭ��

        if (SceneManager == 4) e.inputKey(); // �� ȭ��
        if (SceneManager == 5) f.inputKey(); // ���� ȭ��
        if (SceneManager == 6) g.inputKey(); // �̺�Ʈ ȭ��
        if (SceneManager == 7) h.inputKey(); // ���� ȭ��
    }
}
