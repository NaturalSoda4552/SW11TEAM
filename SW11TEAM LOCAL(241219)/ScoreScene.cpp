
// ���� ���� ȭ��

#include "Data.h"
#include "ScoreScene.h"

// ������
ScoreSceneManager::ScoreSceneManager() {
    score_key = 1;
}
// �Ҹ���
ScoreSceneManager::~ScoreSceneManager() {

}

void ScoreSceneManager::inputKey() {
    // while() �ȿ� �����ϱ� ������ SceneManager���� ����� ���� 1ȸ�� draw() ȣ��
    if (score_key) {
        deleteScene();

        drawScoreScene();
        score_key = 0;
    }

    int key = 0;
    if (_kbhit() != 0) {
        key = _getch();
        // ����Ű �Է�
        if (key == 224) {
            key = _getch();
        }
        if (key == 27) { // esc
            // ����ȭ������ ����
            SceneManager = 0;
            score_key = 1;
        }
    }
}

void ScoreSceneManager::drawScoreScene() {
    gotoPos(MAP_OUTLINE_X / 2 - 6, MAP_OUTLINE_Y / 2 - 8);
    printf("���� �����Դϴ�.");
}