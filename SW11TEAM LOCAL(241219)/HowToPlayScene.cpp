
// ���� ��� ȭ��

#include "Data.h"
#include "HowToPlayScene.h"

// ������
HTPSceneManager::HTPSceneManager() {
    htp_key = 1;
    htp_sceneIdx = 0;
}
// �Ҹ���
HTPSceneManager::~HTPSceneManager() {

}

void HTPSceneManager::inputKey() {
    // while() �ȿ� �����ϱ� ������ SceneManager���� ����� ���� 1ȸ�� draw() ȣ��
    if (htp_key) {
        deleteScene();

        drawHtpScene();
        htp_key = 0;
    }

    int key = 0;
    if (_kbhit() != 0) {
        key = _getch();
        // ����Ű �Է�
        if (key == 224) {
            key = _getch();
            if (key == 75) { // ��

            }
            else if (key == 77) { // ��

            }
            
        }
        if (key == 27) { // esc
            // ����ȭ������ ����
            SceneManager = 0;
            htp_key = 1;
        }
    }
}

void HTPSceneManager::drawHtpScene() {
    // ����, ������ ������ ����
    // ������ ���� ��, �������� ���� ����

    drawSquare(1, 1, 8, 2); 
    gotoPos(4, 2); cout << "���� ��Ģ";
}