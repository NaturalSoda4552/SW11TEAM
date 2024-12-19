
// ���� ȭ��

#include "Data.h"
#include "MainBattle.h"

#include "BattleScene.h"

#include "Character.h"

#include "Explanation.h"

// ��Ʋ 
MainBattle mb;

// ������
BattleSceneManager::BattleSceneManager() {
    battle_key = 1;
    action_selected = 0;
    action_key = 1;
    round_key = 1;
}
// �Ҹ���
BattleSceneManager::~BattleSceneManager() {

}

void BattleSceneManager::inputKey() {
    // while() �ȿ� �����ϱ� ������ SceneManager���� ����� ���� 1ȸ�� draw() ȣ��
    if (battle_key) {
        deleteScene(); // ȭ�� �� �����

        // ���� �������� ���� ��
        if (!isBoss) {
            enemy.Init_Basic_Enemy();
            // enemy.HandSize = 3 + MapCount; // ���� �ڵ� ������ ����
        }
        // ���� �������� ���� ��
        if (isBoss) enemy.Init_Boss1();

        battle_key = 0; // ���� ���� �� ��Ȱ��ȭ
        action_selected = 0; // ȭ�� ��ȯ �� �ൿ ���� �ε��� �ʱ�ȭ ('����' �׸�)
        action_key = 1; // �ൿ ������ ���� ���� �ʱ�ȭ
        drawBattleScene(); // ���� ȭ�� ���
    }
    // �� ����
    if (!isBattleExplanation) {

        // ����â �׸���
        drawBattleExplanation();
        // �� ���� �׸��� <- ����â�߸� ������ �������� ������ �ٽ� �׸���
        drawBattleScene();

        isBattleExplanation = 1;
    }
    
    if (round_key) {
        // ���帶�� ������ �κ� �ֱ�
        drawEnemySelectedCard();

        round_key = 0;
    }

    int key = 0;
    if (_kbhit() != 0) {
        key = _getch();
        // ����Ű �Է�
        if (key == 224) {
            key = _getch();

            // ������
            if (action_key && key == 77) { 
                if (action_selected == 0 || action_selected == 2) action_selected++;
            }
            // ���� 
            if (action_key && key == 75) {
                if (action_selected == 1 || action_selected == 3) action_selected--;
            }
            // ��
            if (action_key && key == 72) {
                if (action_selected >= 2 && action_selected <= 3) action_selected -= 2;
            }
            // �Ʒ�
            if (action_key && key == 80) {
                if (action_selected <= 1 && action_selected >= 0) action_selected += 2;
            }

            drawActionSelectArrow();
            // drawActionBar();
        }
        if (key == 113) { // Q: �нú� �� ���� Ȯ��
            // drawItemCheck();
        }

        if (key == 32) { // space ��
            if (action_key && action_selected == 0) { // ���� �ൿ ��
                
                action_key = 0; // �ൿ ��Ȱ��ȭ
                drawActionSelectArrow(); 

                // ���� �ൿ���� �Ѿ
                if (action_Select() == -1) {
                    // -1 return�� ��� = ���� ����
                    return;
                }

                round_key = 1;
                // mb.enemyTurn();
            }
            else if (action_key && action_selected == 1) { // item �ൿ ��
                action_key = 0; // �ൿ ��Ȱ��ȭ
                drawActionSelectArrow();

                mb.itemTurn(); // func input

                action_key = 1;
                drawActionSelectArrow();
                drawHand();
            }
            else if (action_key && action_selected == 2) { // skill �ൿ ��
                action_key = 0; // �ൿ ��Ȱ��ȭ
                drawActionSelectArrow();

                mb.skillTurn(); // func input

                action_key = 1;
                drawActionSelectArrow();
                drawHand();
            }
            else if (action_key && action_selected == 3) { // ����ġ�� �ൿ ��
                action_key = 0; // �ൿ ��Ȱ��ȭ
                drawActionSelectArrow();

                // ���� ���� ���� ���
                drawSquare(36, 17, 10, 2);
                gotoPos(74, 18); cout << "����ġ�ðڽ��ϱ�?";
                gotoPos(78, 20); cout << "��";
                gotoPos(78, 21); cout << "�ƴϿ�";

                int runIdx = 0;
                gotoPos(76, 20); cout << "��";
                while (1) {
                    if (_kbhit() != 0) {
                        key = _getch();
                        if (key == 224) {
                            key = _getch();
                            // ��
                            if (runIdx == 1 && key == 72) {
                                gotoPos(76, 21); cout << "  ";
                                runIdx--;
                                gotoPos(76, 20); cout << "��";
                            }
                            // �Ʒ�
                            if (runIdx == 0 && key == 80) {
                                gotoPos(76, 20); cout << "  ";
                                runIdx++;
                                gotoPos(76, 21); cout << "��";
                            }
                        }
                        if (key == 32) {
                            // erase
                            for (int k = 0; k <= 6; k++) {
                                gotoPos(72, 17 + k); cout << "                      ";
                            }

                            if (runIdx == 0) { // ��
                                // ü���� 11 �̻��� ���� ����
                                if (p.HP > 10) {
                                    p.HP -= 10;

                                    drawSquare(36, 17, 10, 2);
                                    gotoPos(74, 18); cout << "������ �����ƴ�!";

                                    // �� ȭ������ ����
                                    SceneManager = 4;
                                    battle_key = 1;
                                    round_key = 1;
                                }
                                else {
                                    drawSquare(36, 17, 10, 2);
                                    gotoPos(74, 18); cout << "����ĥ �� ����";
                                }
                                gotoPos(78, 20); cout << "[SPACE]";

                                while (1) {
                                    if (_kbhit() != 0) {
                                        key = _getch();
                                        if (key == 32) {
                                            // erase
                                            for (int k = 0; k <= 6; k++) {
                                                gotoPos(72, 17 + k); cout << "                      ";
                                            }
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                            else { // �ƴϿ�
                                // erase
                                for (int k = 0; k <= 6; k++) {
                                    gotoPos(72, 17 + k); cout << "                      ";
                                }
                                break;
                            }
                        }

                    }
                }
                action_key = 1;
                drawActionSelectArrow();
                drawHand();
            }
        }
        if (key == 27) { // esc - debug

            // �� ȭ������ ����
            SceneManager = 4;
            battle_key = 1;
            round_key = 1;
        }
    }
}

void BattleSceneManager::drawBattleScene() {
    // card info
    mb.start();
    mb.enemyTurn();
    
    // �ൿ ��
    drawActionBar();
    drawActionSelectArrow();

    // �÷��̾� �� ���
    // drawUnit();
    // ���� ĭ 
    drawBonusBook();

    // �ڵ� �� - ������
    drawHandOutLine();
    drawHand();
    
}
void BattleSceneManager::drawUnit() {
    // �÷��̾� �� ���� ����
    gotoPos(MAP_OUTLINE_X / 2 - 14, MAP_OUTLINE_Y / 2 + 2); printf("P"); // �÷��̾�
    gotoPos(MAP_OUTLINE_X / 2 + 10, MAP_OUTLINE_Y / 2 - 8); printf("BOSS"); // ����
    
}
void BattleSceneManager::drawBonusBook() {
    int startX = 2;
    int startY = 1;
    
    gotoPos(startX, startY); cout << " �� + ��  : +5";
    gotoPos(startX, startY + 1); cout << " 4 + 4  : +15";
    gotoPos(startX, startY + 2); cout << " A + A  : +50";
    gotoPos(startX, startY + 3); cout << " K + K  : Dx2"; // 13
    gotoPos(startX, startY + 4); cout << " Q + Q  : Heal"; // 12
    gotoPos(startX, startY + 5); cout << " J + J  : $x2"; // 11
    
}

void BattleSceneManager::drawActionBar() {
    // �÷��̾� �ൿ UI
    // ����(�÷��̾�� ��� ��� 2�� ����) -> ������ �� ��ų ��� -> ��()

    // �׵θ�
    int action_start_X = 1;
    int action_end_X = MAP_OUTLINE_X / 2 / 2;

    int action_start_Y = MAP_OUTLINE_Y - 7;
    int action_end_Y = MAP_OUTLINE_Y - 1;

    for (int i = action_start_Y + 1; i < action_end_Y;i++) {
        gotoPos(action_start_X, i); printf("��");
        gotoPos(action_end_X, i); printf("��");
    }
    for (int i = 2; i < action_end_X; i++) {
        gotoPos(i, action_start_Y); printf("��");
        gotoPos(i, action_end_Y); printf("��");
    }

    gotoPos(action_start_X, action_start_Y); printf("��");
    gotoPos(action_end_X, action_start_Y); printf("��");
    gotoPos(action_start_X, action_end_Y);  printf("��");
    gotoPos(action_end_X, action_end_Y);  printf("��");

    // �޴�
    int action_center_X = (action_end_X + action_start_X) / 2;
    int action_center_Y = (action_end_Y + action_start_Y) / 2;

    gotoPos(action_center_X / 2, action_center_Y - 1); printf("����");
    gotoPos(action_center_X / 2, action_center_Y + 1); printf("��ų");
    gotoPos(action_center_X + 3, action_center_Y - 1); printf("������");
    gotoPos(action_center_X + 3, action_center_Y + 1); printf("����ġ��");
}
void BattleSceneManager::drawActionSelectArrow() {
    // �׵θ�
    int action_start_X = 1;
    int action_end_X = MAP_OUTLINE_X / 2 / 2;

    int action_start_Y = MAP_OUTLINE_Y - 7;
    int action_end_Y = MAP_OUTLINE_Y - 1;
    // �޴�
    int action_center_X = (action_end_X + action_start_X) / 2;
    int action_center_Y = (action_end_Y + action_start_Y) / 2;

    COORD arrowPos[4];
    arrowPos[0] = { (short)(action_center_X / 2 - 4), (short)(action_center_Y - 1) };
    arrowPos[1] = { (short)(action_center_X / 2 + 1), (short)(action_center_Y - 1) };
    arrowPos[2] = { (short)(action_center_X / 2 - 4), (short)(action_center_Y + 1) };
    arrowPos[3] = { (short)(action_center_X / 2 + 1), (short)(action_center_Y + 1) };

    if (action_key) {
        for (int i = 0; i < 4; i++) {
            if (i == action_selected) {
                gotoPos(arrowPos[i].X * 2 - 1, arrowPos[i].Y); printf("��");
            }
            else {
                gotoPos(arrowPos[i].X * 2 - 1, arrowPos[i].Y); printf("  ");
            }
        }
    }
    else {
        for (int i = 0; i < 4; i++) {
            gotoPos(arrowPos[i].X * 2 - 1, arrowPos[i].Y); printf("  ");
        }
    }

}

void BattleSceneManager::drawHandOutLine() {
    // �׵θ�
    int hand_start_X = MAP_OUTLINE_X / 2 / 2 + 1;
    int hand_end_X = MAP_OUTLINE_X - 1;

    int hand_start_Y = MAP_OUTLINE_Y - 7;
    int hand_end_Y = MAP_OUTLINE_Y - 1;

    for (int i = hand_start_Y + 1; i < hand_end_Y; i++) {
        gotoPos(hand_start_X, i); printf("��");
        gotoPos(hand_end_X, i); printf("��");
    }
    for (int i = hand_start_X + 1; i < hand_end_X; i++) {
        gotoPos(i, hand_start_Y); printf("��");
        gotoPos(i, hand_end_Y); printf("��");
    }

    gotoPos(hand_start_X, hand_start_Y); printf("��");
    gotoPos(hand_end_X, hand_start_Y); printf("��");
    gotoPos(hand_start_X, hand_end_Y);  printf("��");
    gotoPos(hand_end_X, hand_end_Y);  printf("��");

    // submit
    // gotoPos(40, 22); printf("[SUBMIT]");
}
void BattleSceneManager::drawHand() {
    // �׵θ�
    int hand_start_X = MAP_OUTLINE_X / 2 / 2+1;
    int hand_end_X = MAP_OUTLINE_X - 1;

    int hand_start_Y = MAP_OUTLINE_Y - 7;
    int hand_end_Y = MAP_OUTLINE_Y - 1;

    // ��� �����
    for (int i = hand_start_X + 1; i < hand_end_X - 1; i++) {
        for (int j = hand_start_Y + 1; j < hand_end_Y; j++) {
            gotoPos(i, j); printf("  ");
        }
    }
    
   
   
    // gotoPos(MAP_OUTLINE_X/2, MAP_OUTLINE_Y/2); printf("%d", mb.Hand[0].size());

    for (int i = 0; i < mb.hand[1].size(); i++) { 
        // each
        gotoPos(hand_start_X + 2 + i * 4, hand_start_Y + 1); printf("��");
        gotoPos(hand_start_X + 3 + i * 4, hand_start_Y + 1); printf("��");
        gotoPos(hand_start_X + 4 + i * 4, hand_start_Y + 1); printf("��");
        gotoPos(hand_start_X + 5 + i * 4, hand_start_Y + 1); printf("��");
        for (int j = hand_start_Y + 2; j < hand_end_Y - 1; j++) {
            gotoPos(hand_start_X + 2 + i * 4, j); printf("��");
        }
        gotoPos(hand_start_X + 2 + i * 4, hand_end_Y - 1); printf("��");
        gotoPos(hand_start_X + 3 + i * 4, hand_end_Y - 1); printf("��");
        gotoPos(hand_start_X + 4 + i * 4, hand_end_Y - 1); printf("��");
        gotoPos(hand_start_X + 5 + i * 4, hand_end_Y - 1); printf("��");
        
        // num, shape
        mb.showHandNumber(1, hand_start_Y + 1 + 1, hand_start_X + i * 4 + 4, i);
        mb.showHandShape(1, hand_start_Y + 1 + 2, hand_start_X + i * 4 + 4, i);

        if (i == mb.hand[1].size() - 1) {
            gotoPos(hand_start_X + i * 4 + 8, hand_end_Y - 1); printf("��");
            gotoPos(hand_start_X + i * 4 + 8, hand_start_Y + 1); printf("��");
            gotoPos(hand_start_X + 7 + i * 4, hand_end_Y - 1); printf("��");
            gotoPos(hand_start_X + 7 + i * 4 - 1, hand_end_Y - 1); printf("��");
            gotoPos(hand_start_X + 7 + i * 4, hand_start_Y + 1); printf("��");
            gotoPos(hand_start_X + 7 + i * 4 - 1, hand_start_Y + 1); printf("��");
            for (int j = hand_start_Y + 2; j < hand_end_Y - 1; j++) {
                gotoPos(hand_start_X + i * 4 + 8, j); printf("��");
            }
        }
    }

    
}

void BattleSceneManager::drawEnemySelectedCard() {
    int hand_start_X = 14;
    // int hand_end_X = hand_start_X + 4*2;

    int hand_start_Y = 5;
    //int hand_end_Y = hand_start_Y + 5;

    // ��� ���� ī�� �׵θ�
    drawSquare(hand_start_X - 1, hand_start_Y - 1, 9, 6);

    for (int i = 0; i < mb.buffer[0].size(); i++) {
        // each
        drawSquare(hand_start_X + i * 4, hand_start_Y, 3, 4);
        // ���� ī���̹Ƿ� �ϴ� �Ⱥ��̰� ����
        // num, shape
    }
    mb.showBufferNumber(0, hand_start_Y + 1, (hand_start_X + 0 * 4 + 1) * 2, 0);
    mb.showBufferShape(0, hand_start_Y + 1 + 1, (hand_start_X + 0 * 4 + 1) * 2, 0);

    // left card display
    drawSquare(23, 8, 1, 2);
    gotoPos(50, 9); cout << "x" << mb.hand[0].size();

}

int BattleSceneManager::action_Select() {

    if (mb.playerTurn())
    {
        action_key = 1;
        drawActionSelectArrow();
        drawHand();
        return 0;
    }
    switch (mb.endTurn()) {
    case -1: // �÷��̾ ��� ��
        drawGameOverScene();
        // exit(-1);
        battle_key = 1;
        round_key = 1;
        return -1;
    case 1: // �÷��̾ �̱� ��
        // ���� �߰�
        
        round_key = 1;
        SceneManager = 4;
        battle_key = 1;
        break;
    case 0:
        mb.enemyTurn();
        break;
    }
    

    // SUBMIT ��
    drawHand();

    action_key = 1;
    drawActionSelectArrow();
}

void BattleSceneManager::drawGameOverScene() {
    // ȭ�� �� �����
    deleteScene();

    // �й�ȭ�� �׸���
    // ���ӿ��� ����
    int startX = 11;
    int startY = 5;
    drawSquare(4, startY-2, 43, 10);
    
    gotoPos(startX, startY);
    cout << "   ####     ###    ##   ##  #######             ###     ##  ##  #######  ## ###  ";
    gotoPos(startX, startY+1);
    cout << "  ##  ##   ## ##   ### ###   ##   #            ## ##   ##   ##   ##   #  ###  ## ";
    gotoPos(startX, startY+2);
    cout << " ##       ##   ##  #######   ##               ##   ##  ##   ##   ##      ##   ## ";
    gotoPos(startX, startY+3);
    cout << " ##  ###  #######  ## # ##   ####             ##   ##  ##   ##   ####    ######  ";
    gotoPos(startX, startY+4);
    cout << " ##   ##  ##   ##  ##   ##   ##               ##   ##  ##  ##    ##      ## ##   ";
    gotoPos(startX, startY+5);
    cout << "  ## ###  ##   ##  ##   ##   ##   #            ## ##    ####     ##   #  ##  ### ";
    gotoPos(startX, startY+6);
    cout << "   ### #  ##   ##  ##   ##  #######             ###      ##     #######  ##   ## ";


    // ���� �нú� ��� ǥ�� -> ?

    // ���� ǥ�� �� ����
    drawSquare(17, 15, 17, 5);
    gotoPos(49, 16); cout << "[SCORE]";

    // ���� �ջ��ϱ�
    for (int i = 0; i < p.Defeat; i++) p.Accum_Score(1); // �� óġ
    for (int i = 0; i < p.Move; i++) p.Accum_Score(3); // �̵�
    p.Accum_Score(4); // ���� ���� �� 

    gotoPos(48, 18); cout << p.Score; // ���� ���

    // Ű �Է� �ޱ� -> �絵�� or ����ȭ��
    drawSquare(22, 22, 8, 2);
    gotoPos(50, 23); cout << "RETRY";

    drawSquare(22, 26, 8, 2);
    gotoPos(47, 27); cout << "BACK TO MAIN";


    int goSceneIdx = 0;
    drawGoSceneArrow(goSceneIdx);

    while (1) {
        int key = 0;
        if (_kbhit() != 0) {
            key = _getch();
            // ����Ű �Է�
            if (key == 224) {
                key = _getch();

                if (key == 72) { // ��
                    if (goSceneIdx == 1) {
                        deleteGoSceneArrow(goSceneIdx);
                        goSceneIdx--;
                        drawGoSceneArrow(goSceneIdx);
                    }
                }
                if (key == 80) { // �Ʒ�
                    if (goSceneIdx == 0) {
                        deleteGoSceneArrow(goSceneIdx);
                        goSceneIdx++;
                        drawGoSceneArrow(goSceneIdx);
                    }
                }
            }
            // space
            if (key == 32) {
                if (goSceneIdx == 0) { // retry
                    SceneManager = 4;
                }
                else { // back to main
                    SceneManager = 0;
                    break;
                }
            }

        }
    }
    //
}
void BattleSceneManager::drawGoSceneArrow(int idx) {
    gotoPos(42, 23 + idx * 4); cout << "��";
}
void BattleSceneManager::deleteGoSceneArrow(int idx) {
    gotoPos(42, 23 + idx * 4); cout << "  ";
}

void BattleSceneManager::drawItemCheck() {
    // "������ Ȯ��" -> "������ Ȯ�� ���"
    cout << "                ";
    gotoPos(20, 8); printf("������ Ȯ�� ���");

    // Ȯ�� â ����
    int w = 30;
    int h = 14;
    int ew = w / 3;

    drawSquare(7, 10, w, h);
    for (int i = 1; i < 3; i++) {
        for (int j = 1; j < h; j++) {
            gotoPos((7 + ew * i) * 2, 10 + j);
            printf("��");
        }
    }
    gotoPos(16, 11); cout << "���� ��Ƽ��";
    gotoPos(16 + ew * 2, 11); cout << "���� �нú�";
    gotoPos(16 + ew * 4, 11); cout << "���� �����";

    // ��� ������ ���
    int listStartX = 18; // + n*2*ew
    int listStartY = 13; // y�� ����

    // ��Ƽ��
    for (int i = 0; i < 4; i++) {
        gotoPos(listStartX, listStartY + i);
        cout << S.ActiveBook[i].Name << " x" << p.ActiveManager[i];
    }
    // �нú�
    for (int i = 0; i < 10; i++) {
        gotoPos(listStartX + 2 * ew, listStartY + i);
        cout << S.PassiveBook[i].Name << " x" << p.PassiveManager[i];
    }
    for (int i = 0; i < 2; i++) {
        gotoPos(listStartX + 4 * ew, listStartY + i);
        cout << S.DebuffBook[i].Name << " x" << p.DebuffManager[i];
    }

    // ���� �ݺ��� ����
    int colIdx = 0; // �� �ε���
    int rowIdx = 0; // �� �ε���

    drawCheckArrow(colIdx, rowIdx);
    drawCheckExplanation(colIdx, rowIdx);

    while (1) {
        int key = 0;
        if (_kbhit() != 0) {
            key = _getch();
            // ����Ű �Է�
            if (key == 224) {
                key = _getch();
                if (key == 77) { // ������ 
                    if (colIdx < 2) {
                        deleteCheckArrow(colIdx, rowIdx);
                        colIdx++;
                        rowIdx = 0;
                        drawCheckArrow(colIdx, rowIdx);
                    }
                }
                if (key == 75) { // ���� 
                    if (colIdx > 0) {
                        deleteCheckArrow(colIdx, rowIdx);
                        colIdx--;
                        rowIdx = 0;
                        drawCheckArrow(colIdx, rowIdx);
                    }
                }

                if (key == 80) { // down
                    int eachRowMaxIdx = 0;
                    switch (colIdx) {
                    case 0: eachRowMaxIdx = 3; break;
                    case 1: eachRowMaxIdx = 9; break;
                    case 2: eachRowMaxIdx = 1; break;
                    }

                    if (rowIdx < eachRowMaxIdx) {
                        deleteCheckArrow(colIdx, rowIdx);
                        rowIdx++;
                        drawCheckArrow(colIdx, rowIdx);
                    }
                }
                if (key == 72) { // up
                    if (rowIdx > 0) {
                        deleteCheckArrow(colIdx, rowIdx);
                        rowIdx--;
                        drawCheckArrow(colIdx, rowIdx);
                    }
                }
                drawCheckExplanation(colIdx, rowIdx);
            }

            if (key == 113) { // Q: ��Ƽ�� Ȯ�� ���
                // �� ���� �����

                

                break;
            }
        }
    }
}
void BattleSceneManager::drawCheckExplanation(int colIdx, int rowIdx) {
    // ���� â �����
    for (int i = 21; i < 51; i++) {
        for (int j = 26; j < 31; j++) {
            gotoPos(i * 2, j); printf("  ");
        }
    }

    int desX = 42;
    int desY = 26;

    if (colIdx == 0) { // ��Ƽ�� ����
        gotoPos(desX, desY); cout << "[���� ��Ƽ��]";
        gotoPos(desX, desY + 2); cout << S.ActiveBook[rowIdx].Name;
        gotoPos(desX, desY + 4); cout << S.ActiveBook[rowIdx].Description;
    }
    else if (colIdx == 1) { // �нú� ����
        gotoPos(desX, desY); cout << "[���� �нú�]";
        gotoPos(desX, desY + 2); cout << S.PassiveBook[rowIdx].Name;
        gotoPos(desX, desY + 4); cout << S.PassiveBook[rowIdx].Description;
    }
    else if (colIdx == 2) { // ����� ����
        gotoPos(desX, desY); cout << "[���� �����]";
        gotoPos(desX, desY + 2); cout << S.DebuffBook[rowIdx].Name;
        gotoPos(desX, desY + 4); cout << S.DebuffBook[rowIdx].Description;
    }
}

void BattleSceneManager::drawCheckArrow(int colIdx, int rowIdx) {
    gotoPos(16 + 20 * colIdx, 13 + rowIdx); cout << "��";
}
void BattleSceneManager::deleteCheckArrow(int colIdx, int rowIdx) {
    gotoPos(16 + 20 * colIdx, 13 + rowIdx); cout << "  ";
}