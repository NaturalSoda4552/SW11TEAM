
// ���� ȭ��

#include "Data.h"
#include "MainScene.h"
#include "MapScene.h"

#include "Character.h"

MapSceneManager e;

// ������
MainSceneManager::MainSceneManager() {
    main_key = 1;
}
// �Ҹ���
MainSceneManager::~MainSceneManager() {

}

void MainSceneManager::inputKey() {
    // while() �ȿ� �����ϱ� ������ SceneManager���� ����� ���� 1ȸ�� draw() ȣ��
    if (main_key) {
        // ���� ���� �� 
        deleteScene();

        selectedMenuIdx = 0;
        menuArrow_X = MAP_OUTLINE_X / 2 - 14;
        menuArrow_Y = MAP_OUTLINE_Y / 2 - 3;


        drawStartScene();
        main_key = 0;
    }

    int key = 0;

    if (_kbhit() != 0) {
        key = _getch();
        // ����Ű �Է�
        if (key == 224) {
            key = _getch();
            if (key == 72) { // ��� �� ��
                if (selectedMenuIdx > 0)  selectedMenuIdx--;
            }
            else if (key == 80) { // ��� �� �Ʒ�
                if (selectedMenuIdx < 3) selectedMenuIdx++;
            }
            drawSelectArrow();
        }
        // �����̽� �� �Է�
        if (key == 32) {
            if (selectedMenuIdx == 0) { // ���� ����
                // ȭ�� �� ����� (���߿� �ִϸ��̼ǵ� �߰�)
                for (int i = 2; i < MAP_OUTLINE_X/2-1; i++) {
                    for (int j = 2; j < MAP_OUTLINE_Y-1; j++) {
                        gotoPos(i*2, j); printf("  ");
                    }
                }

                // �̸� �� ���� �Է¹ޱ�
                p.Get_Player_Name();
                p.Get_Player_Job();

                // ���� �� �ʱ�ȭ �׸���� ���⼭ �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
                e.initMapSetting(); // �� ���� �ʱ�ȭ
                p.Init_Player_Info(); // ĳ���� ���� �ʱ�ȭ
                MapCount = 1;

                // �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
                

                // SceneManager �� ���� 
                SceneManager = 4;
            }
            else if (selectedMenuIdx == 1) { // ���� ���
                deleteScene();

                // SceneManager �� ���� 
                SceneManager = 1;
            }
            else if (selectedMenuIdx == 2) { // ���� Ȯ��
                // ȭ�� �� ����� (���߿� �ִϸ��̼ǵ� �߰�)
                deleteScene();

                // SceneManager �� ���� 
                SceneManager = 2;
            }
            else if (selectedMenuIdx == 3) { // ���� ����
                exit(-1);
            }
            main_key = 1;
        }

    }
}

void MainSceneManager::drawStartScene() {
    // 1. �׵θ� �׸���
    drawOutLine();

    // 2. ���� �̸� ������ �� ���
    drawGameName();

    // 3. �� �� ���� �׸� ���
    drawGameMenu();

    // ����ȭ�� Ű�� 1, ������ 0 (Ű �Է� ���ǿ� ����ϱ� ����)
    drawSelectArrow();
}

void MainSceneManager::drawGameName() {
    int startX = 5;
    int startY = 2;

    gotoPos(startX, startY + 0); cout << "     ____       ______      ____        ____       ____        ______      __      __      ";
    gotoPos(startX, startY + 1); cout << "    /\\  _`\\    /\\  _  \\    /\\  _`\\     /\\  _`\\    /\\  _`\\     /\\  _  \\    /\\ \\  __/\\ \\     ";
    gotoPos(startX, startY + 2); cout << "    \\ \\ \\/\\_\\  \\ \\ \\L\\ \\   \\ \\ \\L\\ \\   \\ \\ \\/\\ \\  \\ \\ \\L\\ \\   \\ \\ \\L\\ \\   \\ \\ \\/\\ \\ \\ \\    ";
    gotoPos(startX, startY + 3); cout << "     \\ \\ \\/_/_  \\ \\  __ \\   \\ \\ ,  /    \\ \\ \\ \\ \\  \\ \\ ,  /    \\ \\  __ \\   \\ \\ \\ \\ \\ \\ \\   ";
    gotoPos(startX, startY + 4); cout << "      \\ \\ \\L\\ \\  \\ \\ \\/\\ \\   \\ \\ \\\\ \\    \\ \\ \\_\\ \\  \\ \\ \\\\ \\    \\ \\ \\/\\ \\   \\ \\ \\_/ \\_\\ \\  ";
    gotoPos(startX, startY + 5); cout << "       \\ \\____/   \\ \\_\\ \\_\\   \\ \\_\\ \\_\\   \\ \\____/   \\ \\_\\ \\_\\   \\ \\_\\ \\_\\   \\ `\\___x___/";
    gotoPos(startX, startY + 6); cout << "        \\/___/     \\/_/\\/_/    \\/_/\\/ /    \\/___/     \\/_/\\/ /    \\/_/\\/_/    '\\/__//__/ ";
/*
     ____       ______      ____        ____       ____        ______      __      __    
    /\  _`\    /\  _  \    /\  _`\     /\  _`\    /\  _`\     /\  _  \    /\ \  __/\ \   
    \ \ \/\_\  \ \ \L\ \   \ \ \L\ \   \ \ \/\ \  \ \ \L\ \   \ \ \L\ \   \ \ \/\ \ \ \  
     \ \ \/_/_  \ \  __ \   \ \ ,  /    \ \ \ \ \  \ \ ,  /    \ \  __ \   \ \ \ \ \ \ \ 
      \ \ \L\ \  \ \ \/\ \   \ \ \\ \    \ \ \_\ \  \ \ \\ \    \ \ \/\ \   \ \ \_/ \_\ \
       \ \ \L\/  \ \ \/\ \   \ \ \\ \    \ \ \_\ \  \ \ \\ \    \ \ \/\ \   \ \ \_/ \_\ \
        \/___/     \/_/\/_/    \/_/\/ /    \/___/     \/_/\/ /    \/_/\/_/    '\ / __//__/ 

*/

}
void MainSceneManager::drawGameMenu() {
    int s_x = MAP_OUTLINE_X / 2 - 10;
    int s_y = MAP_OUTLINE_Y / 2 - 4;

    for (int k = 0; k < 4; k++) {
        gotoPos(s_x, s_y + k * 4); printf("��");
        gotoPos(s_x + 20, s_y + k * 4);  printf("��");
        gotoPos(s_x, s_y + 2 + k * 4);  printf("��");
        gotoPos(s_x + 20, s_y + 2 + k * 4);  printf("��");
        for (int i = 1; i < 20; i++) {
            gotoPos(s_x + i, s_y + k * 4); printf("��");
            gotoPos(s_x + i, s_y + 2 + k * 4); printf("��");
        }
        for (int i = 1; i < 2; i++) {
            gotoPos(s_x, s_y + i + k * 4); printf("��");
            gotoPos(s_x + 20, s_y + i + k * 4); printf("��");
        }
    }

    // Menu name
    gotoPos(s_x + 5, s_y + 1); printf("Game Start");
    gotoPos(s_x + 5, s_y + 1 + 4); printf("How To Play");
    gotoPos(s_x + 5, s_y + 1 + 8); printf("Score");
    gotoPos(s_x + 5, s_y + 1 + 12); printf("Exit");

}
void MainSceneManager::drawSelectArrow() {
     // ȭ��ǥ ��� �����
     for (int i = 0; i < 4; i++) {
         gotoPos(menuArrow_X, menuArrow_Y + i * 4); printf("  ");
     }
     // ���� �ε����� '��' ���
     gotoPos(menuArrow_X, menuArrow_Y + selectedMenuIdx * 4); printf("��");
}
