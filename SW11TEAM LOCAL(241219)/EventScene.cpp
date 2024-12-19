
// 이벤트 화면

#include "Data.h"
#include "EventScene.h"

#include "Character.h"
#include "Item.h"

// #include "SceneASCIIAsset.h"

// 생성자
EventSceneManager::EventSceneManager() {
    event_key = 1;
}
// 소멸자
EventSceneManager::~EventSceneManager() {

}

void EventSceneManager::inputKey() {
    // while() 안에 존재하기 때문에 SceneManager값이 변경된 최초 1회만 draw() 호출
    if (event_key) {
        deleteScene();

        // 각 이벤트 키값 초기화
        // HpAndGold
        HpAndGold_event_key = 0;
        HG_isLeft2 = 0;
        HG_isRight2 = 0;
        HG_isLeft3 = 0;
        HG_isRight3 = 0;
        // Gold
        Gold_event_key = 0;
        G_event = 0;
        G_random_gold = 0; 
        // DeBuff

        
        event_key = 0;
        drawEventScene();
    }

}

void EventSceneManager::drawShopPlayerInfo() {
    // 내용 지우기
    drawSquare(1, 1, 8, 4);
    // 내용 출력하기
    gotoPos(4, 2);  cout << p.Name;
    gotoPos(4, 3);  cout << "Hp: " << p.HP;
    gotoPos(4, 4);  cout << "Gold: " << p.Gold;
}

void EventSceneManager::drawEventScene() {
    // 플레이어 정보 출력
    drawShopPlayerInfo();

    // n가지 이벤트 중 랜덤 발생
    int randomEventKey = rand() % 2;
    // drawEventScene(randomEventKey);
    
    // debug
    // drawHpAndGoldScene();
    // drawGoldScene();
    drawRandomDebuffScene();

    
    /*switch (randomEventKey) {
    case 0:
        drawHpAndGoldScene();
        break;
    case 1:
        drawGoldScene();
        break;
    case 2:
        drawRandomDebuffScene();
        break;
    }*/
}

void EventSceneManager::drawHpAndGoldScene() {
    // 갈림길 컨셉 -> 랜덤으로? (나중에)
    // 동굴이 철창으로 막혀있다. 위험한 듯 하다(독가스) -> 들어간다(피해 X)
    // 갈림길이 나왔다-> 왼쪽 / 오른쪽 / (hp-2)
    // (왼쪽일 시) 갈림길이 나왔다 -> 왼쪽(없음) / 오른쪽(보물상자 - 회복 물약 2개 발견) / (hp-3)
    // (오른쪽일 시) 갈림길이 나왔다 -> 왼쪽(없음) / 오른쪽(보물상자 - 골드 50? 획득) / (hp-3)
    
    // 도중에 사망 시 게임오버처리

    drawHGScene(Gold_event_key);
    drawHGSelectButton(Gold_event_key);
    drawHGSceneExplanation(Gold_event_key);
    
    int arrowIdx = 0;
    drawHGSelectArrow(arrowIdx);

    int drawFlag = 1;

    while (1) {
        int key = 0;
        if (_kbhit() != 0) {
            key = _getch();
            // 방향키 입력
            if (key == 224) {
                key = _getch();
                if (HpAndGold_event_key == 0) {
                    if (key == 72) { // 위
                        if (arrowIdx > 0) {
                            deleteHGSelectArrow(arrowIdx);
                            arrowIdx--;
                            drawHGSelectArrow(arrowIdx);
                        }
                    }
                    if (key == 80) {// 아래
                        if (arrowIdx < 1) {
                            deleteHGSelectArrow(arrowIdx);
                            arrowIdx++;
                            drawHGSelectArrow(arrowIdx);
                        }
                    }
                }
                if (HpAndGold_event_key >= 1 && HpAndGold_event_key <= 2) {
                    if (key == 72) { // 위
                        if (arrowIdx > 0) {
                            deleteHGSelectArrow(arrowIdx);
                            arrowIdx--;
                            drawHGSelectArrow(arrowIdx);
                        }
                    }
                    if (key == 80) {// 아래
                        if (arrowIdx < 2) {
                            deleteHGSelectArrow(arrowIdx);
                            arrowIdx++;
                            drawHGSelectArrow(arrowIdx);
                        }
                    }
                }
            }

            // space 바 - 키값에 따라 다르게 처리
            if (key == 32) {
                if (HpAndGold_event_key == 0) { // 동굴 입구
                    if (arrowIdx == 0) { // 들어간다
                        HpAndGold_event_key++; // 전진

                        deleteHGSelectArrow(arrowIdx);
                        arrowIdx = 0; // 선택 화살표 인덱스 0으로 초기화
                        drawHGSelectArrow(arrowIdx);

                        drawHGScene(HpAndGold_event_key);
                        drawHGSelectButton(HpAndGold_event_key);
                        drawHGSceneExplanation(HpAndGold_event_key);
                    }
                    else if (arrowIdx == 1) { // 나간다
                        // 맵 화면으로 복귀
                        SceneManager = 4;
                        event_key = 1;
                        return;
                    }
                }
                else if (HpAndGold_event_key == 1) { // 첫번째 갈림길
                    if (arrowIdx == 0) { // 왼쪽
                        HpAndGold_event_key++; // 전진
                        HG_isLeft2 = 1;
                        p.HP -= 2;
                    }
                    else if (arrowIdx == 1) { // 오른쪽
                        HpAndGold_event_key++; // 전진
                        HG_isRight2 = 1;
                        p.HP -= 2;
                    }
                    else if (arrowIdx == 2) { // 뒤로가기
                        HpAndGold_event_key--; // 후퇴
                    }

                    deleteHGSelectArrow(arrowIdx);
                    arrowIdx = 0; // 선택 화살표 인덱스 0으로 초기화
                    drawHGSelectArrow(arrowIdx);

                    drawHGScene(HpAndGold_event_key);
                    drawHGSelectButton(HpAndGold_event_key);
                    drawHGSceneExplanation(HpAndGold_event_key);
                }
                else if (HpAndGold_event_key == 2) { // 두번째 갈림길
                    if (arrowIdx == 0) { // 왼쪽
                        HpAndGold_event_key++; // 전진
                        HG_isLeft3 = 1;
                        p.HP -= 3;

                        deleteHGSelectArrow(arrowIdx);
                        arrowIdx = 2;
                    }
                    else if (arrowIdx == 1) { // 오른쪽
                        HpAndGold_event_key++; // 전진
                        HG_isRight3 = 1;
                        p.HP -= 3;

                        deleteHGSelectArrow(arrowIdx);
                        arrowIdx = 2; 
                        
                    }
                    else if (arrowIdx == 2) { // 뒤로가기
                        HpAndGold_event_key--; // 후퇴
                        HG_isLeft2 = 0;
                        HG_isRight2 = 0;

                        deleteHGSelectArrow(arrowIdx);
                        arrowIdx = 0;
                    }
                    drawHGSelectArrow(arrowIdx);

                    drawHGScene(HpAndGold_event_key);
                    drawHGSelectButton(HpAndGold_event_key);
                    drawHGSceneExplanation(HpAndGold_event_key);

                    // display 
                    if (drawFlag) {
                        if (HG_isLeft2 && HG_isRight3) {
                            p.HP += 40;
                            if (p.HP > 100) p.HP = 100;
                        }
                        else if (HG_isRight2 && HG_isRight3) {
                            p.Gold += 40;
                        }

                        drawShopPlayerInfo();

                        drawFlag = 0;
                    }
                }
                else { // 끝 방
                    // 체력방 or 보물방 -> 탈출
                    if ((HG_isLeft2 && HG_isRight3) || (HG_isRight2 && HG_isRight3)) {
                        // 맵 화면으로 복귀
                        SceneManager = 4;
                        event_key = 1;
                        return;
                    }
                    else { // 빈 방
                        HpAndGold_event_key--; // 후퇴
                        HG_isLeft3 = 0;
                        HG_isRight3 = 0;

                        deleteHGSelectArrow(arrowIdx);
                        arrowIdx = 0;
                    }
                    drawHGSelectArrow(arrowIdx);

                    drawHGScene(HpAndGold_event_key);
                    drawHGSelectButton(HpAndGold_event_key);
                    drawHGSceneExplanation(HpAndGold_event_key);
                }
                if (p.HP <= 0) { // game over
                    drawGameOverScene();
                    event_key = 1;

                    return;
                }

                // 플레이어 정보 표시
                drawShopPlayerInfo();
            }
        }
    }
}
void EventSceneManager::drawHGScene(int idx) {
    // erase - 그림 영역만
    int startX = 26;
    int startY = 5;
    drawSquare(startX / 2 - 2, startY, 20, 18);

    switch (idx)
    {
    case 0:
        gotoPos(startX, startY + 1); cout << "       ____________";
        gotoPos(startX, startY + 2); cout << "    __/            \\____";
        gotoPos(startX, startY + 3); cout << "   /                    \\__";
        gotoPos(startX, startY + 4); cout << "  /     _________________  \\___";
        gotoPos(startX, startY + 5); cout << "  |    |_________________|     \\";
        gotoPos(startX, startY + 6); cout << "  |      / //_______// /       |";
        gotoPos(startX, startY + 7); cout << " /       | |+---+---+| |       |";
        gotoPos(startX, startY + 8); cout << " |       | |         | |        \\";
        gotoPos(startX, startY + 9); cout << " |       | |+---+---+| |        |";
        gotoPos(startX, startY + 10); cout << " |       | |         | |        |";
        gotoPos(startX, startY + 11); cout << " |       | |+---+-|■ | |        |";
        gotoPos(startX, startY + 12); cout << "/        | |       --| |        \\";
        gotoPos(startX, startY + 13); cout << "|        | |+---+---+| |        |";
        gotoPos(startX, startY + 14); cout << "|        | |         | |        |";
        gotoPos(startX, startY + 15); cout << "|        | |         | |        |";
        gotoPos(startX, startY + 16); cout << "---------------------------------";
        break;
    case 1:
        gotoPos(startX, startY + 1); cout << "       ____________";
        gotoPos(startX, startY + 2); cout << "    __/            \\_____";
        gotoPos(startX, startY + 3); cout << "   /    /\\             /\\\\__";
        gotoPos(startX, startY + 4); cout << "  /    / /      '      \\ \\  \\___";
        gotoPos(startX, startY + 5); cout << "  |   / /|     '        \\ \\     \\";
        gotoPos(startX, startY + 6); cout << "  |  / / |      '       |\\ \\    |";
        gotoPos(startX, startY + 7); cout << " /  / /  |     '        | \\ \\   |";
        gotoPos(startX, startY + 8); cout << " | / /   |     6        |  \\ \\   \\";
        gotoPos(startX, startY + 9); cout << " | \\/|   |   / I   \\    |  |\\/   |";
        gotoPos(startX, startY + 10); cout << " |   |   |  /_______\\   |  |     |";
        gotoPos(startX, startY + 11); cout << " |   |   |  ||     ||   |  |     |";
        gotoPos(startX, startY + 12); cout << "/    |   |  ||     ||   |  |     \\";
        gotoPos(startX, startY + 13); cout << "|   ---                    |     |";
        gotoPos(startX, startY + 14); cout << "|  / , \\_                  |     |";
        gotoPos(startX, startY + 15); cout << "|  \\    , \\                |     |";
        gotoPos(startX, startY + 16); cout << "----------------------------------";
        break;
    case 2:
        gotoPos(startX, startY + 1); cout << "       ____________";
        gotoPos(startX, startY + 2); cout << "    __/            \\_____";
        gotoPos(startX, startY + 3); cout << "   /    /\\     '       /\\\\__";
        gotoPos(startX, startY + 4); cout << "  /    / /     ' '     \\ \\  \\___";
        gotoPos(startX, startY + 5); cout << "  |   / /|      ' '     \\ \\     \\";
        gotoPos(startX, startY + 6); cout << "  |  / / |     ' '      |\\ \\    |";
        gotoPos(startX, startY + 7); cout << " /  / /  |      ' '     | \\ \\   |";
        gotoPos(startX, startY + 8); cout << " | / /   |     6 6      |  \\ \\   \\";
        gotoPos(startX, startY + 9); cout << " | \\/|   |   / I I \\    |  |\\/   |";
        gotoPos(startX, startY + 10); cout << " |   |   |  /_______\\   |  |     |";
        gotoPos(startX, startY + 11); cout << " |   |   |  ||     ||   |  |     |";
        gotoPos(startX, startY + 12); cout << "/    |   |  ||     ||   |  |   __\\";
        gotoPos(startX, startY + 13); cout << "|    |                    _|__/  |";
        gotoPos(startX, startY + 14); cout << "|    |                   /   ,   |";
        gotoPos(startX, startY + 15); cout << "|    |                  /  ,   ~ |";
        gotoPos(startX, startY + 16); cout << "----------------------------------";
        break;
    case 3:
        if (HG_isLeft2 && HG_isRight3) { // 체력방
            gotoPos(startX, startY + 1); cout << "       ____________";
            gotoPos(startX, startY + 2); cout << "    __/            \\_____";
            gotoPos(startX, startY + 3); cout << "   /                     \\__";
            gotoPos(startX, startY + 4); cout << "  /                         \\__";
            gotoPos(startX, startY + 5); cout << "  |                            \\";
            gotoPos(startX, startY + 6); cout << "  |                            |";
            gotoPos(startX, startY + 7); cout << " /                             |";
            gotoPos(startX, startY + 8); cout << " |          /@/  |@|            \\";
            gotoPos(startX, startY + 9); cout << " |        _/ /_ _| |            |";
            gotoPos(startX, startY + 10); cout << " |       /     /    \\           |";
            gotoPos(startX, startY + 11); cout << " |      /  ♥  /  ♥   \\          |";
            gotoPos(startX, startY + 12); cout << "/       \\     \\      /           \\";
            gotoPos(startX, startY + 13); cout << "|        \\____/\\____/            |";
            gotoPos(startX, startY + 14); cout << "|                                |";
            gotoPos(startX, startY + 15); cout << "|                                |";
            gotoPos(startX, startY + 16); cout << "----------------------------------";
        }
        else if (HG_isRight2 && HG_isRight3) { // 보물방
            gotoPos(startX, startY + 1); cout << "       ____________";
            gotoPos(startX, startY + 2); cout << "    __/            \\_____";
            gotoPos(startX, startY + 3); cout << "   /                     \\__";
            gotoPos(startX, startY + 4); cout << "  /                         \\__";
            gotoPos(startX, startY + 5); cout << "  |                            \\";
            gotoPos(startX, startY + 6); cout << "  |                            |";
            gotoPos(startX, startY + 7); cout << " /                             |";
            gotoPos(startX, startY + 8); cout << " |         _____________        \\";
            gotoPos(startX, startY + 9); cout << " |        /____________/\\        |";
            gotoPos(startX, startY + 10); cout << " |       /            / |        |";
            gotoPos(startX, startY + 11); cout << " |       |_____■______| |        |";
            gotoPos(startX, startY + 12); cout << "/        |            | |        \\";
            gotoPos(startX, startY + 13); cout << "|        |____________|/         |";
            gotoPos(startX, startY + 14); cout << "|                                |";
            gotoPos(startX, startY + 15); cout << "|                                |";
            gotoPos(startX, startY + 16); cout << "----------------------------------";
        }
        else { // 빈 방
            gotoPos(startX, startY + 1); cout << "       ____________";
            gotoPos(startX, startY + 2); cout << "    __/            \\_____";
            gotoPos(startX, startY + 3); cout << "   /                     \\__";
            gotoPos(startX, startY + 4); cout << "  /                         \\__";
            gotoPos(startX, startY + 5); cout << "  |                            \\";
            gotoPos(startX, startY + 6); cout << "  |                            |";
            gotoPos(startX, startY + 7); cout << " /                             |";
            gotoPos(startX, startY + 8); cout << " |                              \\";
            gotoPos(startX, startY + 9); cout << " |                              |";
            gotoPos(startX, startY + 10); cout << " |                              |";
            gotoPos(startX, startY + 11); cout << " |                              |";
            gotoPos(startX, startY + 12); cout << "/                                \\";
            gotoPos(startX, startY + 13); cout << "|                                |";
            gotoPos(startX, startY + 14); cout << "|                                |";
            gotoPos(startX, startY + 15); cout << "|                                |";
            gotoPos(startX, startY + 16); cout << "----------------------------------";
        }
        break;
    }
}
void EventSceneManager::drawHGSceneExplanation(int idx) {
    // 설명창 내부 지우기
    drawSquare(20, 25, 30, 6);

    // 문구 출력
    int desX = 42;
    int desY = 26;
    switch (idx) {
    case 0: 
        gotoPos(desX, desY); printf("동굴에 철창으로 된 문이 있다."); 
        gotoPos(desX, desY+1); printf("안은 가스로 가득 찬 듯 하다.");
        break;
    case 1:
        gotoPos(desX, desY); printf("갈림길이다. 어느 쪽으로 갈까?");
        break;
    case 2:
        gotoPos(desX, desY); printf("또 다른 갈림길이다. 어느 쪽으로 갈까?");
        break;
    case 3:
        if (HG_isLeft2 && HG_isRight3) { // 체력방
            gotoPos(desX, desY); printf("누군가의 체력 포션 2개를 얻었다!");
            gotoPos(desX, desY+1); printf("HP 40 회복");
        }
        else if (HG_isRight2 && HG_isRight3) { // 보물방
            gotoPos(desX, desY); printf("보물 상자를 발견했다!");
            gotoPos(desX, desY+1); printf("Gold 40 획득");
        }
        else { // 빈 방
            gotoPos(desX, desY); printf("아무것도 보이지 않는다...");
        }
        break;
    }
}
void EventSceneManager::drawHGSelectButton(int idx) {
    // 버튼 출력
    drawSquare(38, 12, 5, 2); // 버튼 1
    drawSquare(38, 16, 5, 2); // 버튼 2
    if (idx >= 1 && idx <= 3) {
        drawSquare(38, 20, 5, 2); // 버튼 3
    }
    else {
        for (int i = 0; i < 3; i++) {
            gotoPos(76, 20 + i); cout << "            ";
        }
    }

    // (hp-) erase
    gotoPos(90, 13);  cout << "      ";
    gotoPos(90, 17);  cout << "      ";
    
    switch (idx) {
    case 0:
        gotoPos(78, 13);  cout << "들어간다";
        gotoPos(78, 17);  cout << "나가기";
        break;
    case 1:
        gotoPos(78, 13);  cout << "왼쪽";
        gotoPos(78, 17);  cout << "오른쪽";
        gotoPos(78, 21);  cout << "뒤로가기";
        gotoPos(90, 13);  cout << "HP-2";
        gotoPos(90, 17);  cout << "HP-2";
        break;
    case 2:
        gotoPos(78, 13);  cout << "왼쪽";
        gotoPos(78, 17);  cout << "오른쪽";
        gotoPos(78, 21);  cout << "뒤로가기";
        gotoPos(90, 13);  cout << "HP-3";
        gotoPos(90, 17);  cout << "HP-3";
        break;
    case 3:
        for (int i = 0; i < 3; i++) { // 버튼 1, 2 지우기
            gotoPos(76, 12 + i); cout << "            ";
            gotoPos(76, 16 + i); cout << "            ";
        }

        if (HG_isLeft2 && HG_isRight3) { // 체력방
            gotoPos(78, 21);  cout << "나가기";
        }
        else if (HG_isRight2 && HG_isRight3) { // 보물방
            gotoPos(78, 21);  cout << "나가기";
        }
        else { // 빈 방
            gotoPos(78, 21);  cout << "뒤로가기";
        }
        break;
    }
}
void EventSceneManager::drawHGSelectArrow(int idx) {
    // 
    gotoPos(74, 13 + idx * 4); cout << "▶";
}
void EventSceneManager::deleteHGSelectArrow(int idx) {
    // 
    gotoPos(74, 13 + idx * 4); cout << "  ";
}

void EventSceneManager::drawGoldScene() {
    // 보물 발굴 컨셉 -> 발굴 시 랜덤 효과 제공
    // 1. 골드 획득 (30-50)
    // 2. 골드 소실 (30-50)
    // 3. 골드 획득 (1/100 확률로, 150-200)

    drawGScene(HpAndGold_event_key);
    drawGSelectButton(HpAndGold_event_key);
    drawGSceneExplanation(HpAndGold_event_key);

    G_event = rand() % 101 + 1; 
    if (G_event <= 70) G_random_gold = rand() % 21 + 30;
    else if (G_event <= 99) G_random_gold = -(rand() % 21 + 30);
    else G_random_gold = rand() % 51 + 150;

    int arrowIdx = 0;
    drawGSelectArrow(arrowIdx);

    int drawFlag = 1;

    while (1) {
        int key = 0;
        if (_kbhit() != 0) {
            key = _getch();
            // 방향키 입력
            if (key == 224) {
                key = _getch();
                if (Gold_event_key == 0) {
                    if (key == 72) { // 위
                        if (arrowIdx > 0) {
                            deleteGSelectArrow(arrowIdx);
                            arrowIdx--;
                            drawGSelectArrow(arrowIdx);
                        }
                    }
                    if (key == 80) {// 아래
                        if (arrowIdx < 1) {
                            deleteGSelectArrow(arrowIdx);
                            arrowIdx++;
                            drawGSelectArrow(arrowIdx);
                        }
                    }
                }
            }
            // space
            if (key == 32) {
                if (Gold_event_key == 0) { // 보물상자 파기 전
                    if (arrowIdx == 0) { // 발굴한다
                        Gold_event_key++; // 전진

                        deleteGSelectArrow(arrowIdx);
                        arrowIdx = 1; // 선택 화살표 인덱스 1로 초기화
                        drawGSelectArrow(arrowIdx);

                        drawGScene(Gold_event_key);
                        drawGSelectButton(Gold_event_key);
                        drawGSceneExplanation(Gold_event_key);

                        // display 
                        if (drawFlag) {
                            p.Gold += G_random_gold;
                            if (p.Gold < 0) p.Gold = 0;

                            drawShopPlayerInfo();

                            drawFlag = 0;
                        }
                    }
                    else if (arrowIdx == 1) { // 나간다
                        // 맵 화면으로 복귀
                        SceneManager = 4;
                        event_key = 1;
                        return;
                    }
                }
                else if (Gold_event_key == 1) { // 발굴 후
                    if (arrowIdx == 1) { // 나가기
                        
                        // 맵 화면으로 복귀
                        SceneManager = 4;
                        event_key = 1;
                        return;
                    }
                }
            }
        }
    }

}
void EventSceneManager::drawGScene(int idx) {
    // erase - 그림 영역만
    int startX = 26;
    int startY = 5;
    drawSquare(startX / 2 - 2, startY, 20, 18);

    switch (idx)
    {
    case 0:
        gotoPos(startX, startY + 1); cout <<  "          $  ||  $$              ";
        gotoPos(startX, startY + 2); cout <<  "   $$$ $$$   ||                  ";
        gotoPos(startX, startY + 3); cout <<  "  $&  ||__$))||--))___       __))";
        gotoPos(startX, startY + 4); cout <<  " ____)||     ||       )___)))    ";
        gotoPos(startX, startY + 5); cout <<  "      ||    /  \\                ";
        gotoPos(startX, startY + 6); cout <<  "      ||                         ";
        gotoPos(startX, startY + 7); cout <<  "     /  \\                       ";
        gotoPos(startX, startY + 8); cout <<  "                                 ";
        gotoPos(startX, startY + 9); cout <<  "               ____              ";
        gotoPos(startX, startY + 10); cout << "              /\\   \\      _    ";
        gotoPos(startX, startY + 11); cout << "          ___/  \\   \\  __/     ";
        gotoPos(startX, startY + 12); cout << "             -__▲___\\/          ";
        gotoPos(startX, startY + 13); cout << "                                 ";
        gotoPos(startX, startY + 14); cout << "                                 ";
        gotoPos(startX, startY + 15); cout << "                                 ";
        gotoPos(startX, startY + 16); cout << "---------------------------------";
        break;
    case 1:
        if (G_event <= 70) {
            gotoPos(startX, startY + 1); cout <<  "                                 ";
            gotoPos(startX, startY + 2); cout <<  "                                 ";
            gotoPos(startX, startY + 3); cout <<  "                                 ";
            gotoPos(startX, startY + 4); cout <<  "         _____________ _         ";
            gotoPos(startX, startY + 5); cout <<  "        /______〓_____/ \\       ";
            gotoPos(startX, startY + 6); cout <<  "        \\             \\  \\    ";
            gotoPos(startX, startY + 7); cout <<  "         \\_____________\\_/     ";
            gotoPos(startX, startY + 8); cout <<  "         /             /|        ";
            gotoPos(startX, startY + 9); cout <<  "        /_____________/ |        ";
            gotoPos(startX, startY + 10); cout << "        |      ■      | |        ";
            gotoPos(startX, startY + 11); cout << "        |             | /        ";
            gotoPos(startX, startY + 12); cout << "        |_____________|/         ";
            gotoPos(startX, startY + 13); cout << "                                 ";
            gotoPos(startX, startY + 14); cout << "                                 ";
            gotoPos(startX, startY + 15); cout << "                                 ";
            gotoPos(startX, startY + 16); cout << "---------------------------------";
        }
        else if (G_event <= 98) {
            gotoPos(startX, startY + 1); cout <<  "                                 ";
            gotoPos(startX, startY + 2); cout <<  "                                 ";
            gotoPos(startX, startY + 3); cout <<  "                                 ";
            gotoPos(startX, startY + 4); cout <<  "                                 ";
            gotoPos(startX, startY + 5); cout <<  "              x                  ";
            gotoPos(startX, startY + 6); cout <<  "              \\\\               ";
            gotoPos(startX, startY + 7); cout <<  "            x  \\\\              ";
            gotoPos(startX, startY + 8); cout <<  "           //   \\\\             ";
            gotoPos(startX, startY + 9); cout <<  "          //     \\\\            ";
            gotoPos(startX, startY + 10); cout << "       /\\//     __\\\\__        ";
            gotoPos(startX, startY + 11); cout << "       \\ \\      \\     \\      ";
            gotoPos(startX, startY + 12); cout << "        \\/       \\     \\      ";
            gotoPos(startX, startY + 13); cout << "                  -____-         ";
            gotoPos(startX, startY + 14); cout << "                                 ";
            gotoPos(startX, startY + 15); cout << "                                 ";
            gotoPos(startX, startY + 16); cout << "---------------------------------";
        }
        else if (G_event <= 100) {
            gotoPos(startX, startY + 1); cout << "                                 ";
            gotoPos(startX, startY + 2); cout << "                                 ";
            gotoPos(startX, startY + 3); cout << "                                 ";
            gotoPos(startX, startY + 4); cout << "         _____________ _         ";
            gotoPos(startX, startY + 5); cout << "        /______〓_____/ \\       ";
            gotoPos(startX, startY + 6); cout << "        \\             \\  \\    ";
            gotoPos(startX, startY + 7); cout << "         \\_____________\\_/     ";
            gotoPos(startX, startY + 8); cout << "         /\\_\\_\\_\\_\\_\\_\\/|        ";
            gotoPos(startX, startY + 9); cout << "        /_____________/ |        ";
            gotoPos(startX, startY + 10); cout << "        |      ■      | |        ";
            gotoPos(startX, startY + 11); cout << "        |             | /        ";
            gotoPos(startX, startY + 12); cout << "        |_____________|/         ";
            gotoPos(startX, startY + 13); cout << "                                 ";
            gotoPos(startX, startY + 14); cout << "                                 ";
            gotoPos(startX, startY + 15); cout << "                                 ";
            gotoPos(startX, startY + 16); cout << "---------------------------------";
        }
        
        break;
     }
}
void EventSceneManager::drawGSceneExplanation(int idx) {
    // 설명창 내부 지우기
    drawSquare(20, 25, 30, 6);

    // 문구 출력
    int desX = 42;
    int desY = 26;
    switch (idx) {
    case 0:
        gotoPos(desX, desY); printf("땅에 보물상자가 묻혀있다.");
        gotoPos(desX, desY + 1); printf("삽으로 파내어 열어볼 수 있을 듯 하다.");
        break;
    case 1:
        if (G_event <= 70) {
            gotoPos(desX, desY); printf("상자에서 금화 몇 푼을 찾았다.");
            gotoPos(desX, desY+1); printf("골드 %d 획득", G_random_gold);
        }
        else if (G_event <= 98) {
            gotoPos(desX, desY); printf("상자를 꺼내다가 가진 돈 일부를 잃어버렸다.");
            gotoPos(desX, desY + 1); printf("골드 %d 소실", -G_random_gold);
        }
        else {
            gotoPos(desX, desY); printf("금괴가 가득 차 있다.");
            gotoPos(desX, desY + 1); printf("골드 %d 획득", G_random_gold);
        }
        break;
    }
}
void EventSceneManager::drawGSelectButton(int idx) {
    // 버튼 출력
    drawSquare(38, 12, 5, 2); // 버튼 1
    drawSquare(38, 16, 5, 2); // 버튼 2
    if (idx >= 1) {
        for (int i = 0; i < 3; i++) {
            gotoPos(76, 12 + i); cout << "            ";
        }
    }

    // (hp-) erase
    gotoPos(90, 13);  cout << "      ";
    gotoPos(90, 17);  cout << "      ";

    switch (idx) {
    case 0:
        gotoPos(78, 13);  cout << "파낸다";
        gotoPos(78, 17);  cout << "나가기";
        break;
    case 1:
        // gotoPos(78, 13);  cout << "    ";
        gotoPos(78, 17);  cout << "나가기";
        break;
    }
}
void EventSceneManager::drawGSelectArrow(int idx) {
    // 
    gotoPos(74, 13 + idx * 4); cout << "▶";
}
void EventSceneManager::deleteGSelectArrow(int idx) {
    // 
    gotoPos(74, 13 + idx * 4); cout << "  ";
}


void EventSceneManager::drawRandomDebuffScene() {
    // 디버프 이벤트 발생 시 강제로 디버프 추가 (선택지 없음)
    // 디버프 개수만큼 랜덤 인덱스 발급 (총 6개 중 하나)

    // 0: 중독 / 깊은 숲에서 독사에게 물렸다. 독에 물든 기운이 몸을 타고 흐른다.
    // 1: 탈진 / 여행의 끝이 보이지 않는다. 끝없는 피로가 몰려온다. 
    // 2, 3, 4, 5: 문양 디버프 / 저주받은 상자를 열어버렸다. 

    int debuffRandomIdx = rand()%6;

    drawDbScene(debuffRandomIdx);
    drawDbSceneExplanation(debuffRandomIdx);
    
    // 디버프 얻기
    p.DebuffInventory.push_back(S.DebuffBook[debuffRandomIdx]);
    p.DebuffManager[debuffRandomIdx] += 1;
        
    drawSquare(38, 12, 5, 2); // 버튼 1

    gotoPos(74, 13); cout << "▶"; 
    gotoPos(78, 13); cout << "나가기";

    while (1) {
        int key = 0;
        if (_kbhit() != 0) {
            key = _getch();
            if (key == 32) {
                // 맵 화면으로 복귀
                SceneManager = 4;
                event_key = 1;
                return;
            }
        }
    }
}
void EventSceneManager::drawDbScene(int idx) {
    // erase - 그림 영역만
    int startX = 26;
    int startY = 5;
    drawSquare(startX / 2 - 2, startY, 20, 18);
    startX -= 1;
    switch (idx) {
    case 0: // 중독: 이동할때마다 hp -3
        gotoPos(startX, startY + 1); cout << " |   |  |/   |   | /| |  | |  |   |";
        gotoPos(startX, startY + 2); cout << " |  /|  |  / |   |  | |  | |  |/  |";
        gotoPos(startX, startY + 3); cout << " |/  |  |    |   |/ | |  | |  |  /|";
        gotoPos(startX, startY + 4); cout << " | / |  |/   |   | /| |  | |  |   |";
        gotoPos(startX, startY + 5); cout << " |   |  |    |   |  | |  | |  |   |";
        gotoPos(startX, startY + 6); cout << "/     \\ |  / |   /  /    / /  | / |";
        gotoPos(startX, startY + 7); cout << "   ________        _______    |   |";
        gotoPos(startX, startY + 8); cout << "  /        \\      /       \\   |   |";
        gotoPos(startX, startY + 9); cout << " /  /~~~~\\  \\    /  /~~~\\  \\ / / \\ \\";
        gotoPos(startX, startY + 10); cout << " |  |    |  |    |  |   |  | / / \\  \\";
        gotoPos(startX, startY + 11); cout << " |  |    |  |    |  |   |  | / /";
        gotoPos(startX, startY + 12); cout << " |  |    |  |    |  |   |  |       /";
        gotoPos(startX, startY + 13); cout << " |  |    |  |    |  |   |  |     //";
        gotoPos(startX, startY + 14); cout << "(o  o)   \\  \\____/  /   \\  \\___/ /";
        gotoPos(startX, startY + 15); cout << " \\__/     \\        /     \\      /";
        gotoPos(startX, startY + 16); cout << "  |        ~~~~~~~~       ~~~~~~";
        gotoPos(startX, startY + 17); cout << "  ^";
        break;

    case 1: // 탈진: 최종 합 -3
        gotoPos(startX, startY + 1); cout << " |   |  |/   |   | /| |  | |  |   |";
        gotoPos(startX, startY + 2); cout << " |  /|  |  / |   |  | |  | |  |/  |";
        gotoPos(startX, startY + 3); cout << " |/  |  |    |   |/ | |  | |  |  /|";
        gotoPos(startX, startY + 4); cout << " | / |  |/   |   | /| |  | |  |   |";
        gotoPos(startX, startY + 5); cout << " |   |  |    |   |  | |  | |  |   |";
        gotoPos(startX, startY + 6); cout << "/     \\ |  / |   /  /    / /  | / |";
        gotoPos(startX, startY + 7); cout << "                            \\ |   |";
        gotoPos(startX, startY + 8); cout << "          __                  |   |";
        gotoPos(startX, startY + 9); cout << "         | ,|   __ O         / / \\ \\";
        gotoPos(startX, startY + 10); cout << "         \\__/     / \\         / / \\ \\";
        gotoPos(startX, startY + 11); cout << "               __/           / /";
        gotoPos(startX, startY + 12); cout << "                 \\              ";
        gotoPos(startX, startY + 13); cout << "";
        gotoPos(startX, startY + 14); cout << "";
        gotoPos(startX, startY + 15); cout << "";
        gotoPos(startX, startY + 16); cout << "";
        gotoPos(startX, startY + 17); cout << "";
        break;

    }
    if (idx == 2 || idx == 3 ||
        idx == 4 || idx == 5) {
        gotoPos(startX, startY + 1); cout << "                                 ";
        gotoPos(startX, startY + 2); cout << "       /                     /   ";
        gotoPos(startX, startY + 3); cout << "     \\                    /      ";
        gotoPos(startX, startY + 4); cout << "         _____________ _   /     ";
        gotoPos(startX, startY + 5); cout << "        /______〓_____/ \\       ";
        gotoPos(startX, startY + 6); cout << "        \\             \\  \\    ";
        gotoPos(startX, startY + 7); cout << "   /     \\_____________\\_/     ";
        gotoPos(startX, startY + 8); cout << "    -    /             /|        ";
        gotoPos(startX, startY + 9); cout << "        /_____________/ |   -    ";
        gotoPos(startX, startY + 10); cout << "     -  |      ■      | |        ";
        gotoPos(startX, startY + 11); cout << "        |             | /        ";
        gotoPos(startX, startY + 12); cout << "   -    |_____________|/   -     ";
        gotoPos(startX, startY + 13); cout << "       /    ,          \\         ";
        gotoPos(startX, startY + 14); cout << "    /           \\          \\     ";
        gotoPos(startX, startY + 15); cout << "      /         |        \\       ";
        gotoPos(startX, startY + 16); cout << "---------------------------------";
    }
}
void EventSceneManager::drawDbSceneExplanation(int idx) {
    // 설명창 내부 지우기
    drawSquare(20, 25, 30, 6);

    // 문구 출력
    int desX = 42;
    int desY = 26;
    switch (idx) {
    case 0:
        gotoPos(desX, desY); printf("깊은 숲에서 독사에게 물렸다.");
        gotoPos(desX, desY + 1); printf("독에 물든 기운이 몸을 타고 흐른다.");
        gotoPos(desX, desY + 3); printf("[중독] 디버프 획득");
        break;
    case 1:
        gotoPos(desX, desY); printf("여행의 끝이 보이지 않는다.");
        gotoPos(desX, desY + 1); printf("끝없는 피로가 몰려온다.");
        gotoPos(desX, desY + 3); printf("[탈진] 디버프 획득");
        break;
    case 2:
        gotoPos(desX, desY); printf("저주받은 보물상자를 열었다.");
        gotoPos(desX, desY + 1); printf("불길한 기운이 느껴진다.");
        gotoPos(desX, desY + 3); printf("[스페이드의 저주] 디버프 획득");
        break;
    case 3:
        gotoPos(desX, desY); printf("저주받은 보물상자를 열었다.");
        gotoPos(desX, desY + 1); printf("불길한 기운이 느껴진다.");
        gotoPos(desX, desY + 3); printf("[다이아몬드의 저주] 디버프 획득");
        break;
    case 4:
        gotoPos(desX, desY); printf("저주받은 보물상자를 열었다.");
        gotoPos(desX, desY + 1); printf("불길한 기운이 느껴진다.");
        gotoPos(desX, desY + 3); printf("[하트의 저주] 디버프 획득");
        break;
    case 5:
        gotoPos(desX, desY); printf("저주받은 보물상자를 열었다.");
        gotoPos(desX, desY + 1); printf("불길한 기운이 느껴진다.");
        gotoPos(desX, desY + 3); printf("[클로버의 저주] 디버프 획득");
        break;
    }
}


void EventSceneManager::drawGameOverScene() {
    // 화면 다 지우기
    deleteScene();

    // 패배화면 그리기
    // 게임오버 문구
    int startX = 11;
    int startY = 5;
    drawSquare(4, startY - 2, 43, 10);

    gotoPos(startX, startY);
    cout << "   ####     ###    ##   ##  #######             ###     ##  ##  #######  ## ###  ";
    gotoPos(startX, startY + 1);
    cout << "  ##  ##   ## ##   ### ###   ##   #            ## ##   ##   ##   ##   #  ###  ## ";
    gotoPos(startX, startY + 2);
    cout << " ##       ##   ##  #######   ##               ##   ##  ##   ##   ##      ##   ## ";
    gotoPos(startX, startY + 3);
    cout << " ##  ###  #######  ## # ##   ####             ##   ##  ##   ##   ####    ######  ";
    gotoPos(startX, startY + 4);
    cout << " ##   ##  ##   ##  ##   ##   ##               ##   ##  ##  ##    ##      ## ##   ";
    gotoPos(startX, startY + 5);
    cout << "  ## ###  ##   ##  ##   ##   ##   #            ## ##    ####     ##   #  ##  ### ";
    gotoPos(startX, startY + 6);
    cout << "   ### #  ##   ##  ##   ##  #######             ###      ##     #######  ##   ## ";


    // 가진 패시브 등등 표시 -> ?

    // 점수 표시 및 저장
    drawSquare(17, 15, 17, 5);
    gotoPos(49, 16); cout << "[SCORE]";
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
}
void EventSceneManager::drawGoSceneArrow(int idx) {
    gotoPos(42, 23 + idx * 4); cout << "▶"; 
}
void EventSceneManager::deleteGoSceneArrow(int idx) {
    gotoPos(42, 23 + idx * 4); cout << "  ";
}