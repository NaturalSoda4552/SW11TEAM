
// 전투 화면

#include "Data.h"
#include "MainBattle.h"

#include "BattleScene.h"

#include "Character.h"

#include "Explanation.h"

// 배틀 
MainBattle mb;

// 생성자
BattleSceneManager::BattleSceneManager() {
    battle_key = 1;
    action_selected = 0;
    action_key = 1;
    round_key = 1;
}
// 소멸자
BattleSceneManager::~BattleSceneManager() {

}

void BattleSceneManager::inputKey() {
    // while() 안에 존재하기 때문에 SceneManager값이 변경된 최초 1회만 draw() 호출
    if (battle_key) {
        deleteScene(); // 화면 다 지우기

        // 몬스터 스테이지 진입 시
        if (!isBoss) {
            enemy.Init_Basic_Enemy();
            // enemy.HandSize = 3 + MapCount; // 적의 핸드 사이즈 조절
        }
        // 보스 스테이지 진입 시
        if (isBoss) enemy.Init_Boss1();

        battle_key = 0; // 최초 실행 시 비활성화
        action_selected = 0; // 화면 전환 시 행동 선택 인덱스 초기화 ('선택' 항목)
        action_key = 1; // 행동 선택을 위한 변수 초기화
        drawBattleScene(); // 전투 화면 출력
    }
    // 맵 설명
    if (!isBattleExplanation) {

        // 설명창 그리기
        drawBattleExplanation();
        // 맵 에셋 그리기 <- 설명창뜨면 에셋이 지워지기 때문에 다시 그리기
        drawBattleScene();

        isBattleExplanation = 1;
    }
    
    if (round_key) {
        // 라운드마다 실행할 부분 넣기
        drawEnemySelectedCard();

        round_key = 0;
    }

    int key = 0;
    if (_kbhit() != 0) {
        key = _getch();
        // 방향키 입력
        if (key == 224) {
            key = _getch();

            // 오른쪽
            if (action_key && key == 77) { 
                if (action_selected == 0 || action_selected == 2) action_selected++;
            }
            // 왼쪽 
            if (action_key && key == 75) {
                if (action_selected == 1 || action_selected == 3) action_selected--;
            }
            // 위
            if (action_key && key == 72) {
                if (action_selected >= 2 && action_selected <= 3) action_selected -= 2;
            }
            // 아래
            if (action_key && key == 80) {
                if (action_selected <= 1 && action_selected >= 0) action_selected += 2;
            }

            drawActionSelectArrow();
            // drawActionBar();
        }
        if (key == 113) { // Q: 패시브 및 족보 확인
            // drawItemCheck();
        }

        if (key == 32) { // space 바
            if (action_key && action_selected == 0) { // 선택 행동 시
                
                action_key = 0; // 행동 비활성화
                drawActionSelectArrow(); 

                // 선택 행동으로 넘어감
                if (action_Select() == -1) {
                    // -1 return된 경우 = 게임 오버
                    return;
                }

                round_key = 1;
                // mb.enemyTurn();
            }
            else if (action_key && action_selected == 1) { // item 행동 시
                action_key = 0; // 행동 비활성화
                drawActionSelectArrow();

                mb.itemTurn(); // func input

                action_key = 1;
                drawActionSelectArrow();
                drawHand();
            }
            else if (action_key && action_selected == 2) { // skill 행동 시
                action_key = 0; // 행동 비활성화
                drawActionSelectArrow();

                mb.skillTurn(); // func input

                action_key = 1;
                drawActionSelectArrow();
                drawHand();
            }
            else if (action_key && action_selected == 3) { // 도망치기 행동 시
                action_key = 0; // 행동 비활성화
                drawActionSelectArrow();

                // 도망 여부 문구 출력
                drawSquare(36, 17, 10, 2);
                gotoPos(74, 18); cout << "도망치시겠습니까?";
                gotoPos(78, 20); cout << "예";
                gotoPos(78, 21); cout << "아니오";

                int runIdx = 0;
                gotoPos(76, 20); cout << "▶";
                while (1) {
                    if (_kbhit() != 0) {
                        key = _getch();
                        if (key == 224) {
                            key = _getch();
                            // 위
                            if (runIdx == 1 && key == 72) {
                                gotoPos(76, 21); cout << "  ";
                                runIdx--;
                                gotoPos(76, 20); cout << "▶";
                            }
                            // 아래
                            if (runIdx == 0 && key == 80) {
                                gotoPos(76, 20); cout << "  ";
                                runIdx++;
                                gotoPos(76, 21); cout << "▶";
                            }
                        }
                        if (key == 32) {
                            // erase
                            for (int k = 0; k <= 6; k++) {
                                gotoPos(72, 17 + k); cout << "                      ";
                            }

                            if (runIdx == 0) { // 예
                                // 체력이 11 이상일 때만 가능
                                if (p.HP > 10) {
                                    p.HP -= 10;

                                    drawSquare(36, 17, 10, 2);
                                    gotoPos(74, 18); cout << "무사히 도망쳤다!";

                                    // 맵 화면으로 복귀
                                    SceneManager = 4;
                                    battle_key = 1;
                                    round_key = 1;
                                }
                                else {
                                    drawSquare(36, 17, 10, 2);
                                    gotoPos(74, 18); cout << "도망칠 수 없다";
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
                            else { // 아니요
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

            // 맵 화면으로 복귀
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
    
    // 행동 바
    drawActionBar();
    drawActionSelectArrow();

    // 플레이어 및 상대
    // drawUnit();
    // 족보 칸 
    drawBonusBook();

    // 핸드 바 - 딜레이
    drawHandOutLine();
    drawHand();
    
}
void BattleSceneManager::drawUnit() {
    // 플레이어 및 상대방 발판
    gotoPos(MAP_OUTLINE_X / 2 - 14, MAP_OUTLINE_Y / 2 + 2); printf("P"); // 플레이어
    gotoPos(MAP_OUTLINE_X / 2 + 10, MAP_OUTLINE_Y / 2 - 8); printf("BOSS"); // 상대방
    
}
void BattleSceneManager::drawBonusBook() {
    int startX = 2;
    int startY = 1;
    
    gotoPos(startX, startY); cout << " ♤ + ♤  : +5";
    gotoPos(startX, startY + 1); cout << " 4 + 4  : +15";
    gotoPos(startX, startY + 2); cout << " A + A  : +50";
    gotoPos(startX, startY + 3); cout << " K + K  : Dx2"; // 13
    gotoPos(startX, startY + 4); cout << " Q + Q  : Heal"; // 12
    gotoPos(startX, startY + 5); cout << " J + J  : $x2"; // 11
    
}

void BattleSceneManager::drawActionBar() {
    // 플레이어 행동 UI
    // 선택(플레이어와 상대 모두 2장 선택) -> 아이템 및 스킬 사용 -> 비교()

    // 테두리
    int action_start_X = 1;
    int action_end_X = MAP_OUTLINE_X / 2 / 2;

    int action_start_Y = MAP_OUTLINE_Y - 7;
    int action_end_Y = MAP_OUTLINE_Y - 1;

    for (int i = action_start_Y + 1; i < action_end_Y;i++) {
        gotoPos(action_start_X, i); printf("│");
        gotoPos(action_end_X, i); printf("│");
    }
    for (int i = 2; i < action_end_X; i++) {
        gotoPos(i, action_start_Y); printf("─");
        gotoPos(i, action_end_Y); printf("─");
    }

    gotoPos(action_start_X, action_start_Y); printf("┌");
    gotoPos(action_end_X, action_start_Y); printf("┐");
    gotoPos(action_start_X, action_end_Y);  printf("└");
    gotoPos(action_end_X, action_end_Y);  printf("┘");

    // 메뉴
    int action_center_X = (action_end_X + action_start_X) / 2;
    int action_center_Y = (action_end_Y + action_start_Y) / 2;

    gotoPos(action_center_X / 2, action_center_Y - 1); printf("선택");
    gotoPos(action_center_X / 2, action_center_Y + 1); printf("스킬");
    gotoPos(action_center_X + 3, action_center_Y - 1); printf("아이템");
    gotoPos(action_center_X + 3, action_center_Y + 1); printf("도망치기");
}
void BattleSceneManager::drawActionSelectArrow() {
    // 테두리
    int action_start_X = 1;
    int action_end_X = MAP_OUTLINE_X / 2 / 2;

    int action_start_Y = MAP_OUTLINE_Y - 7;
    int action_end_Y = MAP_OUTLINE_Y - 1;
    // 메뉴
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
                gotoPos(arrowPos[i].X * 2 - 1, arrowPos[i].Y); printf("▶");
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
    // 테두리
    int hand_start_X = MAP_OUTLINE_X / 2 / 2 + 1;
    int hand_end_X = MAP_OUTLINE_X - 1;

    int hand_start_Y = MAP_OUTLINE_Y - 7;
    int hand_end_Y = MAP_OUTLINE_Y - 1;

    for (int i = hand_start_Y + 1; i < hand_end_Y; i++) {
        gotoPos(hand_start_X, i); printf("│");
        gotoPos(hand_end_X, i); printf("│");
    }
    for (int i = hand_start_X + 1; i < hand_end_X; i++) {
        gotoPos(i, hand_start_Y); printf("─");
        gotoPos(i, hand_end_Y); printf("─");
    }

    gotoPos(hand_start_X, hand_start_Y); printf("┌");
    gotoPos(hand_end_X, hand_start_Y); printf("┐");
    gotoPos(hand_start_X, hand_end_Y);  printf("└");
    gotoPos(hand_end_X, hand_end_Y);  printf("┘");

    // submit
    // gotoPos(40, 22); printf("[SUBMIT]");
}
void BattleSceneManager::drawHand() {
    // 테두리
    int hand_start_X = MAP_OUTLINE_X / 2 / 2+1;
    int hand_end_X = MAP_OUTLINE_X - 1;

    int hand_start_Y = MAP_OUTLINE_Y - 7;
    int hand_end_Y = MAP_OUTLINE_Y - 1;

    // 모두 지우기
    for (int i = hand_start_X + 1; i < hand_end_X - 1; i++) {
        for (int j = hand_start_Y + 1; j < hand_end_Y; j++) {
            gotoPos(i, j); printf("  ");
        }
    }
    
   
   
    // gotoPos(MAP_OUTLINE_X/2, MAP_OUTLINE_Y/2); printf("%d", mb.Hand[0].size());

    for (int i = 0; i < mb.hand[1].size(); i++) { 
        // each
        gotoPos(hand_start_X + 2 + i * 4, hand_start_Y + 1); printf("┌");
        gotoPos(hand_start_X + 3 + i * 4, hand_start_Y + 1); printf("─");
        gotoPos(hand_start_X + 4 + i * 4, hand_start_Y + 1); printf("─");
        gotoPos(hand_start_X + 5 + i * 4, hand_start_Y + 1); printf("─");
        for (int j = hand_start_Y + 2; j < hand_end_Y - 1; j++) {
            gotoPos(hand_start_X + 2 + i * 4, j); printf("│");
        }
        gotoPos(hand_start_X + 2 + i * 4, hand_end_Y - 1); printf("└");
        gotoPos(hand_start_X + 3 + i * 4, hand_end_Y - 1); printf("─");
        gotoPos(hand_start_X + 4 + i * 4, hand_end_Y - 1); printf("─");
        gotoPos(hand_start_X + 5 + i * 4, hand_end_Y - 1); printf("─");
        
        // num, shape
        mb.showHandNumber(1, hand_start_Y + 1 + 1, hand_start_X + i * 4 + 4, i);
        mb.showHandShape(1, hand_start_Y + 1 + 2, hand_start_X + i * 4 + 4, i);

        if (i == mb.hand[1].size() - 1) {
            gotoPos(hand_start_X + i * 4 + 8, hand_end_Y - 1); printf("┘");
            gotoPos(hand_start_X + i * 4 + 8, hand_start_Y + 1); printf("┐");
            gotoPos(hand_start_X + 7 + i * 4, hand_end_Y - 1); printf("─");
            gotoPos(hand_start_X + 7 + i * 4 - 1, hand_end_Y - 1); printf("─");
            gotoPos(hand_start_X + 7 + i * 4, hand_start_Y + 1); printf("─");
            gotoPos(hand_start_X + 7 + i * 4 - 1, hand_start_Y + 1); printf("─");
            for (int j = hand_start_Y + 2; j < hand_end_Y - 1; j++) {
                gotoPos(hand_start_X + i * 4 + 8, j); printf("│");
            }
        }
    }

    
}

void BattleSceneManager::drawEnemySelectedCard() {
    int hand_start_X = 14;
    // int hand_end_X = hand_start_X + 4*2;

    int hand_start_Y = 5;
    //int hand_end_Y = hand_start_Y + 5;

    // 상대 선택 카드 테두리
    drawSquare(hand_start_X - 1, hand_start_Y - 1, 9, 6);

    for (int i = 0; i < mb.buffer[0].size(); i++) {
        // each
        drawSquare(hand_start_X + i * 4, hand_start_Y, 3, 4);
        // 상대방 카드이므로 일단 안보이게 설정
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
    case -1: // 플레이어가 사망 시
        drawGameOverScene();
        // exit(-1);
        battle_key = 1;
        round_key = 1;
        return -1;
    case 1: // 플레이어가 이길 시
        // 점수 추가
        
        round_key = 1;
        SceneManager = 4;
        battle_key = 1;
        break;
    case 0:
        mb.enemyTurn();
        break;
    }
    

    // SUBMIT 시
    drawHand();

    action_key = 1;
    drawActionSelectArrow();
}

void BattleSceneManager::drawGameOverScene() {
    // 화면 다 지우기
    deleteScene();

    // 패배화면 그리기
    // 게임오버 문구
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


    // 가진 패시브 등등 표시 -> ?

    // 점수 표시 및 저장
    drawSquare(17, 15, 17, 5);
    gotoPos(49, 16); cout << "[SCORE]";

    // 점수 합산하기
    for (int i = 0; i < p.Defeat; i++) p.Accum_Score(1); // 적 처치
    for (int i = 0; i < p.Move; i++) p.Accum_Score(3); // 이동
    p.Accum_Score(4); // 게임 오버 시 

    gotoPos(48, 18); cout << p.Score; // 점수 출력

    // 키 입력 받기 -> 재도전 or 메인화면
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
            // 방향키 입력
            if (key == 224) {
                key = _getch();

                if (key == 72) { // 위
                    if (goSceneIdx == 1) {
                        deleteGoSceneArrow(goSceneIdx);
                        goSceneIdx--;
                        drawGoSceneArrow(goSceneIdx);
                    }
                }
                if (key == 80) { // 아래
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
    gotoPos(42, 23 + idx * 4); cout << "▶";
}
void BattleSceneManager::deleteGoSceneArrow(int idx) {
    gotoPos(42, 23 + idx * 4); cout << "  ";
}

void BattleSceneManager::drawItemCheck() {
    // "아이템 확인" -> "아이템 확인 취소"
    cout << "                ";
    gotoPos(20, 8); printf("아이템 확인 취소");

    // 확인 창 구성
    int w = 30;
    int h = 14;
    int ew = w / 3;

    drawSquare(7, 10, w, h);
    for (int i = 1; i < 3; i++) {
        for (int j = 1; j < h; j++) {
            gotoPos((7 + ew * i) * 2, 10 + j);
            printf("│");
        }
    }
    gotoPos(16, 11); cout << "보유 액티브";
    gotoPos(16 + ew * 2, 11); cout << "보유 패시브";
    gotoPos(16 + ew * 4, 11); cout << "보유 디버프";

    // 모든 아이템 출력
    int listStartX = 18; // + n*2*ew
    int listStartY = 13; // y는 고정

    // 액티브
    for (int i = 0; i < 4; i++) {
        gotoPos(listStartX, listStartY + i);
        cout << S.ActiveBook[i].Name << " x" << p.ActiveManager[i];
    }
    // 패시브
    for (int i = 0; i < 10; i++) {
        gotoPos(listStartX + 2 * ew, listStartY + i);
        cout << S.PassiveBook[i].Name << " x" << p.PassiveManager[i];
    }
    for (int i = 0; i < 2; i++) {
        gotoPos(listStartX + 4 * ew, listStartY + i);
        cout << S.DebuffBook[i].Name << " x" << p.DebuffManager[i];
    }

    // 무한 반복문 진입
    int colIdx = 0; // 열 인덱스
    int rowIdx = 0; // 행 인덱스

    drawCheckArrow(colIdx, rowIdx);
    drawCheckExplanation(colIdx, rowIdx);

    while (1) {
        int key = 0;
        if (_kbhit() != 0) {
            key = _getch();
            // 방향키 입력
            if (key == 224) {
                key = _getch();
                if (key == 77) { // 오른쪽 
                    if (colIdx < 2) {
                        deleteCheckArrow(colIdx, rowIdx);
                        colIdx++;
                        rowIdx = 0;
                        drawCheckArrow(colIdx, rowIdx);
                    }
                }
                if (key == 75) { // 왼쪽 
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

            if (key == 113) { // Q: 액티브 확인 취소
                // 그 영역 지우기

                

                break;
            }
        }
    }
}
void BattleSceneManager::drawCheckExplanation(int colIdx, int rowIdx) {
    // 설명 창 지우기
    for (int i = 21; i < 51; i++) {
        for (int j = 26; j < 31; j++) {
            gotoPos(i * 2, j); printf("  ");
        }
    }

    int desX = 42;
    int desY = 26;

    if (colIdx == 0) { // 액티브 설명
        gotoPos(desX, desY); cout << "[보유 액티브]";
        gotoPos(desX, desY + 2); cout << S.ActiveBook[rowIdx].Name;
        gotoPos(desX, desY + 4); cout << S.ActiveBook[rowIdx].Description;
    }
    else if (colIdx == 1) { // 패시브 설명
        gotoPos(desX, desY); cout << "[보유 패시브]";
        gotoPos(desX, desY + 2); cout << S.PassiveBook[rowIdx].Name;
        gotoPos(desX, desY + 4); cout << S.PassiveBook[rowIdx].Description;
    }
    else if (colIdx == 2) { // 디버프 설명
        gotoPos(desX, desY); cout << "[보유 디버프]";
        gotoPos(desX, desY + 2); cout << S.DebuffBook[rowIdx].Name;
        gotoPos(desX, desY + 4); cout << S.DebuffBook[rowIdx].Description;
    }
}

void BattleSceneManager::drawCheckArrow(int colIdx, int rowIdx) {
    gotoPos(16 + 20 * colIdx, 13 + rowIdx); cout << "▶";
}
void BattleSceneManager::deleteCheckArrow(int colIdx, int rowIdx) {
    gotoPos(16 + 20 * colIdx, 13 + rowIdx); cout << "  ";
}