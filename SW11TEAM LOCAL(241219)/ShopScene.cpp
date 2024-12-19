
// 상점 화면

#include "Data.h"
#include "ShopScene.h"

#include "MapScene.h"

#include "Character.h"
#include "item.h"

#include "Explanation.h"

Item_Book S;

HANDLE shopHandle = GetStdHandle(STD_OUTPUT_HANDLE);

// 생성자
ShopSceneManager::ShopSceneManager() {
    shop_key = 1;
}
// 소멸자
ShopSceneManager::~ShopSceneManager() {

}

void ShopSceneManager::inputKey() {
    // while() 안에 존재하기 때문에 SceneManager값이 변경된 최초 1회만 draw() 호출
    if (shop_key) {
        deleteScene(); 

        shop_key = 0;

        // 상점 최초 들어오면 
        // 항목 인덱스는 0으로 초기화 (체력 칸)
        shopItemIdx = 0;
        // 패시브 액티브 랜덤 으로 1개씩 생성
        randomPassiveItemIdx = rand() % 10; // 패시브는 총 10개
        randomActiveItemIdx = rand() % 4; // 액티브는 총 4개

        isHpSold = 0;
        isDebuffSellingSold = 0;
        isActiveSold = 0;
        isPassiveSold = 0;

        
        drawShopScene();
    }
    // 상점 설명창
    if (!isShopExplanation) {
        // 설명창 그리기
        drawShopExplanation();
        // 맵 에셋 그리기 <- 설명창뜨면 에셋이 지워지기 때문에 다시 그리기
        drawShopScene();

        isShopExplanation = 1;
    }

    int key = 0;
    if (_kbhit() != 0) {
        key = _getch();
        // 방향키 입력
        if (key == 224) {
            key = _getch();

            if (key == 77) { // 오른쪽 
                if (shopItemIdx < 4) {
                    deleteItemArrow();
                    shopItemIdx++;
                    drawItemArrow();
                }
            }
            else if (key == 75) { // 왼쪽 
                if (shopItemIdx > 0) {
                    deleteItemArrow();
                    shopItemIdx--;
                    drawItemArrow();
                }
            }
            drawItemExplanation();
        }
        if (key == 113) { // Q: 액티브 확인
            drawItemCheck();
        }

        if (key == 32) {// space 바
            // 선택 항목 구매 및 갱신 <- 나중에 함수로 빼기
            switch (shopItemIdx) {
            case 0: // 체력 회복 - 40원
                if (p.HP < 100 && p.Gold >= cost_h && !isHpSold) {
                    p.HP += 20;
                    p.Gold -= cost_h;
                    if (p.HP > 100) p.HP = 100;
                    isHpSold = 1;
                    shopItemIdx = 0;
                    drawShopScene();
                }
                break;
            case 1: // 패시브 제거 - 50원
                // 패시브 스킬이 있으면
                if (p.Gold >= cost_d && !isDebuffSellingSold) {
                    // 패시브 제거 창 행동 수행
                    SellingPassiveItem();
                    
                    // 탈출 시 오른쪽 위 창 지우기
                    for (int i = 24; i <= 50; i++) {
                        for (int j = 4; j <= 10; j++) {
                            gotoPos(i*2, j); printf("  ");
                        }
                    }
                    shopItemIdx = 0;
                    drawShopScene();
                }
                break;
            case 2: // 액티브 아이템 구매
                if (p.ActiveInventory.size() < 14 && p.Gold >= cost_a && !isActiveSold) {
                    p.ActiveInventory.push_back(S.ActiveBook[randomActiveItemIdx]);
                    p.ActiveManager[randomActiveItemIdx] += 1;
                    p.Gold -= cost_a;
                    isActiveSold = 1;
                    shopItemIdx = 0;
                    drawShopScene();
                }

                break;
            case 3: // 패시브 아이템 구매
                if (p.PassiveInventory.size() < 14 && p.Gold >= cost_p && !isPassiveSold) {
                    p.PassiveInventory.push_back(S.PassiveBook[randomPassiveItemIdx]);
                    p.PassiveManager[randomPassiveItemIdx] += 1;
                    p.Gold -= cost_p;
                    isPassiveSold = 1;
                    shopItemIdx = 0;
                    drawShopScene();
                }

                break;
            case 4: // 상점 나가기
                SceneManager = 4;
                shop_key = 1;
            }
            // action -> player hp, gold display
            drawShopPlayerInfo();
            // keyboard move -> explanantion refersh
            if (key == 75 || key == 77) {
                drawItemExplanation();
            }
        }
    }
}

void ShopSceneManager::drawShopScene() {
    // 에셋 먼저 그리기
    drawShopAsset();

    // 패시브 미리 계산
    cost_h = 40;
    cost_d = 50;
    cost_p = S.PassiveBook[randomPassiveItemIdx].Cost;
    cost_a = S.ActiveBook[randomActiveItemIdx].Cost;
    if (p.PassiveManager[2] >= 1) {
        cost_h -= cost_h * p.PassiveManager[2] * 10 / 100;
        cost_d -= cost_d * p.PassiveManager[2] * 10 / 100;
        cost_p -= cost_p * p.PassiveManager[2] * 10 / 100;
        cost_a -= cost_a * p.PassiveManager[2] * 10 / 100;
    }

    drawItemsOutLine();
    drawShopPlayerInfo();
    drawItemArrow();
    
    drawItemExplanation();
}
void ShopSceneManager::drawItemsOutLine() {
    // 테두리 그리는 함수

    // 선택 및 설명 칸
    drawSquare(20, 25, 31, 6);

    // 체력 회복 칸
    drawSquare(10, 19, 4, 4);
    gotoPos(22, 20); printf("<3");
    // 패시브 제거 칸
    drawSquare(19, 16, 4, 4);
    gotoPos(40, 17); printf("SELL");
    // 액티브 스킬 칸
    drawSquare(28, 19, 4, 4);
    gotoPos(58, 20); cout << S.ActiveBook[randomActiveItemIdx].avi;
    // 패시브 스킬 칸
    drawSquare(37, 16, 4, 4);
    gotoPos(76, 17); cout << S.PassiveBook[randomPassiveItemIdx].avi;
    // 상점 나가기 칸
    drawSquare(47, 22, 4, 2);
    gotoPos(96, 23); printf("나가기");

    // 상점 항목들이 팔린 경우 표시
    if (isHpSold) {
        SetConsoleTextAttribute(shopHandle, 4);
        drawSquare(9, 20, 6, 2);
        for (int i = 0; i < 9; i++) {
            gotoPos(20+i, 21);  cout << "■";
        }
        SetConsoleTextAttribute(shopHandle, 15);
    }
    if (isDebuffSellingSold) {
        SetConsoleTextAttribute(shopHandle, 4);
        drawSquare(18, 17, 6, 2);
        for (int i = 0; i < 9; i++) {
            gotoPos(38+i, 18);  cout << "■";
        }
        SetConsoleTextAttribute(shopHandle, 15);
    }
    if (isActiveSold) {
        SetConsoleTextAttribute(shopHandle, 4);
        drawSquare(27, 20, 6, 2);
        for (int i = 0; i < 9; i++) {
            gotoPos(56+i, 21);  cout << "■";
        }
        
        SetConsoleTextAttribute(shopHandle, 15);
    }
    if (isPassiveSold) {
        SetConsoleTextAttribute(shopHandle, 4);
        drawSquare(36, 17, 6, 2);
        for (int i = 0; i < 9; i++) {
            gotoPos(74+i, 18);  cout << "■";
        }
        SetConsoleTextAttribute(shopHandle, 15);
    }


    // 액티브 확인 문구
    drawSquare(7, 7, 2, 2);
    gotoPos(16, 8); printf("Q");
    gotoPos(20, 8);  cout << "             ";
    gotoPos(20, 8); printf("아이템 확인");
    // 패시브 확인 문구
    /*drawSquare(7, 10, 2, 2);
    gotoPos(16, 11); printf("W");
    gotoPos(20, 11); printf("패시브 확인");*/

    
}
void ShopSceneManager::drawShopPlayerInfo() {
    // 내용 지우기
    drawSquare(1, 1, 8, 4);
    // 내용 출력하기
    gotoPos(4, 2);  cout << p.Name;
    gotoPos(4, 3);  cout << "Hp: " << p.HP;
    gotoPos(4, 4);  cout << "Gold: " << p.Gold;
}
void ShopSceneManager::drawItemArrow() {
    // 상점 항목 선택 화살표 그리기
    if (shopItemIdx == 4) { 
        gotoPos(2 * (5 + shopItemIdx * 11), 21); printf("▼");
    }
    else {
        gotoPos(2 * (10 + shopItemIdx * 9) + 4, 21 + ((shopItemIdx + 1) % 2) * 3); printf("▲");
    }
}
void ShopSceneManager::deleteItemArrow() {
    // 상점 항목 선택 화살표 그리기
    if (shopItemIdx == 4) { // 나가기 일 때,
        gotoPos(2 * (5 + shopItemIdx * 11), 21); printf("  ");
    }
    else {
        gotoPos(2 * (10 + shopItemIdx * 9) + 4, 21 + ((shopItemIdx + 1) % 2) * 3); printf("  ");
    }
}

void ShopSceneManager::drawItemExplanation() {
    // 설명 창 지우기
    for (int i = 21; i < 51; i++) {
        for (int j = 26; j < 31; j++) {
            gotoPos(i * 2, j); printf("  ");
        }
    }

    int desX = 42;
    int desY = 26;

    switch (shopItemIdx) {
    case 0: // 체력 회복
        gotoPos(desX, desY); printf("[체력 회복] %dGold", cost_h);
        gotoPos(desX, desY + 2); printf("일정량의 체력을 회복한다.");
        break;
    case 1: // 패시브 제거
        gotoPos(desX, desY); printf("[패시브 제거] %dGold", cost_d);
        gotoPos(desX, desY + 2); printf("패시브 스킬을 선택하여 제거한다.");
        break;
    case 2: // 액티브 아이템 구매
        gotoPos(desX, desY); printf("[액티브 아이템 구매] %dGold", cost_a);
        gotoPos(desX, desY + 2); cout << S.ActiveBook[randomActiveItemIdx].Name;
        gotoPos(desX, desY + 4); cout << S.ActiveBook[randomActiveItemIdx].Description;
        break;
    case 3: // 패시브 아이템 구매
        gotoPos(desX, desY); printf("[패시브 아이템 구매] %dGold", cost_p);
        gotoPos(desX, desY + 2); cout << S.PassiveBook[randomPassiveItemIdx].Name;
        gotoPos(desX, desY + 4); cout << S.PassiveBook[randomPassiveItemIdx].Description;
        break;
    }
    
}

void ShopSceneManager::SellingPassiveItem() {
    // 패시브 제거 항목 선택 시 진입
    
    // 진입 시 기존 화살표 지우기
    deleteItemArrow();
    // 기존 상점 창 나가는 버튼 지우기
    for (int i = 0; i < 3; i++) {
        gotoPos(94, 22 + i); cout << "         ";
    }

    // 제거할 패시브 스킬 선택
    int deletePassiveIdx = -1;

    // 패시브 OutLine 그리기 (우측 상단)
    drawSquare(19, 7, 26, 7);
    // 판매 창 나가는 버튼 그리기
    drawSquare(20, 8, 4, 2);
    gotoPos(42, 9); cout << " 종료";

    // 패시브 보유량이 0개일 시
    if (p.DebuffInventory.size() == 0) {
        gotoPos(52, 6); cout << "보유 패시브 없음";
        deletePassiveIdx = -1;
    }
    else { // 1개 이상 보유하고 있을 시
        // 보유 패시브 아이콘 및 이름 출력
        for (int i = 0; i < p.DebuffInventory.size(); i++) {
            drawSquare(25 + i * 4, 8, 3, 3);
            gotoPos(2*(25 + i * 4) + 2, 9); cout << p.DebuffInventory[i].avi;
        }
    }

    // 선택 화살표 그리기
    drawSellingArrow(deletePassiveIdx);
    drawDeleteItemExplanation(deletePassiveIdx);

    while (1) {
        int key = 0;
        if (_kbhit() != 0) {
            key = _getch();
            // 방향키 입력
            if (key == 224) {
                key = _getch();

                int size = p.DebuffInventory.size();

                if (key == 77) { // 오른쪽 
                    if (deletePassiveIdx < size - 1) {
                        deleteSellingArrow(deletePassiveIdx);
                        deletePassiveIdx++;
                        drawSellingArrow(deletePassiveIdx);
                    }
                }
                if (key == 75) { // 왼쪽 
                    if (deletePassiveIdx > -1) {
                        deleteSellingArrow(deletePassiveIdx);
                        deletePassiveIdx--;
                        drawSellingArrow(deletePassiveIdx);
                    }
                }

                drawDeleteItemExplanation(deletePassiveIdx);
            }
        }

        if (key == 32 && p.DebuffInventory.size() && deletePassiveIdx != -1) { // space 바
            if (deletePassiveIdx >= 0) {
                p.DebuffInventory.erase(p.DebuffInventory.begin() + deletePassiveIdx);
                p.DebuffManager[deletePassiveIdx] -= 1;

                p.Gold -= cost_d;

                isDebuffSellingSold = 1;
                shopItemIdx = 0;
                drawItemArrow();
            }
            deleteSellingArrow(deletePassiveIdx);
            // 나가기 버튼 및 패시브 제거 창 지우기
            for (int i = 0; i < 3; i++) {
                gotoPos(36, 4 + i); cout << "          ";
            }

            break;
        }
        else if (key == 32 && deletePassiveIdx == -1) { // 나가기 버튼
            // 나가기 버튼 및 패시브 제거 창 지우기
            for (int i = 0; i < 3; i++) {
                gotoPos(36, 4 + i); cout << "          ";
            }
            // 패시브 제거 창 화살표 지우기
            deleteSellingArrow(deletePassiveIdx);

            break;
        }
    }
}
void ShopSceneManager::drawSellingArrow(int idx) {
    if (idx == -1) {
        gotoPos(2 * (26 + idx * 4), 11); printf("▲");
    }
    else {
        gotoPos(2 * (26 + idx * 4) + 1, 12); printf("▲");
    }
}
void ShopSceneManager::deleteSellingArrow(int idx) {
    if (idx == -1) {
        gotoPos(2 * (26 + idx * 4), 11); printf("  ");
    }
    else {
        gotoPos(2 * (26 + idx * 4) + 1, 12); printf("  ");
    }
}
void ShopSceneManager::drawDeleteItemExplanation(int idx) {
    // 설명 창 지우기
    for (int i = 21; i < 51; i++) {
        for (int j = 26; j < 31; j++) {
            gotoPos(i * 2, j); printf("  ");
        }
    }

    int desX = 42;
    int desY = 26;
    if (idx >= 0) {
        if (p.DebuffInventory.size() > 0) {
            gotoPos(desX, desY); cout << "[패시브 제거] - " << p.DebuffInventory[idx].Name;

            gotoPos(desX, desY + 2); cout << p.DebuffInventory[idx].Description;
        }
    }
    else {
        gotoPos(desX, desY); cout << "[패시브 제거] 종료";
    }
}

void ShopSceneManager::drawShopAsset() { 
    //// 책상
    //for (int i = 5; i < MAP_OUTLINE_X-18; i++) {
    //    gotoPos(i, 19); cout << '-';
    //    gotoPos(i, 21); cout << '-';
    //}
    //gotoPos(5, 19); cout << "┌";
    //gotoPos(5, 20); cout << "│";
    //gotoPos(5, 21); cout << "└";
    //gotoPos(MAP_OUTLINE_X - 18, 19); cout << "┐";
    //gotoPos(MAP_OUTLINE_X - 18, 20); cout << "│";
    //gotoPos(MAP_OUTLINE_X - 18, 21); cout << "┘";
    //for (int i = 0; i < 4; i++) {
    //    gotoPos(6 + i, 18 - i); cout << "/";
    //}
    //for (int i = 0; i < 6; i++) {
    //    gotoPos(MAP_OUTLINE_X - 17 + i, 18 - i); cout << "/";
    //}
    //for (int i = 11; i < MAP_OUTLINE_X - 12; i++) {
    //    gotoPos(i, 13); cout << '-';
    //}
    //gotoPos(MAP_OUTLINE_X - 12, 14); cout << "│";
    //for (int i = 0; i < 6; i++) {
    //    gotoPos(MAP_OUTLINE_X - 16 + i, 20 - i); cout << "/";
    //}
    //
    //for (int i = 0; i < 12; i++) {
    //    gotoPos(5, 20 + i); cout << "│";
    //}
    //for (int i = 0; i < 10; i++) {
    //    gotoPos(8, 22 + i); cout << "│";
    //    gotoPos(11, 22 + i); cout << "│";
    //}
    //for (int i = 0; i < 3; i++) {
    //    gotoPos(MAP_OUTLINE_X - 18, 22 + i); cout << "│";
    //    gotoPos(MAP_OUTLINE_X - 21, 22 + i); cout << "│";
    //}
    //for (int i = 0; i < 5; i++) {
    //    gotoPos(MAP_OUTLINE_X - 15, 20 + i); cout << "│";
    //}
    //for (int i = 0; i < 12; i++) {
    //    gotoPos(MAP_OUTLINE_X - 13, 1 + i); cout << "│";
    //    gotoPos(13, 1 + i); cout << "│";
    //}
    //int startX = 35;
    //int startY = 2;
    //gotoPos(startX, startY); cout <<   " ####   ### ####    #####    #####  ";
    //gotoPos(startX, startY+1); cout << "##  #    ##  ##    ##   ##    ## ## ";
    //gotoPos(startX, startY+2); cout << "###      ##  ##    ##   ##    ## ## ";
    //gotoPos(startX, startY+3); cout << " ###     ######    ##   ##    ####  ";
    //gotoPos(startX, startY+4); cout << "  ###    ##  ##    ##   ##    ##    ";
    //gotoPos(startX, startY+5); cout << "#  ##    ##  ##    ##   ##    ##    ";
    //gotoPos(startX, startY+6); cout << "####    #### ###    #####    ####   ";

    // 새로 구상하기
    drawSquare(6, 6, 40, 22); // 큰 사각형
    drawSquare(24, 1, 20, 8); // SHOP 팻말 사각형
    // 상점 팻말
    gotoPos(50, 2); cout << "   ####   ###  ###    ####    #####  ";
    gotoPos(50, 3); cout << "  ##  #    ##  ##    ##  ##    ## ## ";
    gotoPos(50, 4); cout << "  ###      ##  ##    ##  ##    ## ## ";
    gotoPos(50, 5); cout << "   ###     ######    ##  ##    ####  ";
    gotoPos(50, 6); cout << "    ###    ##  ##    ##  ##    ##    ";
    gotoPos(50, 7); cout << "  #  ##    ##  ##    ##  ##    ##    ";
    gotoPos(50, 8); cout << "  ####    ###  ###    ####    ####   ";
    
    // 체력 칸 팻말
    drawSquare(8, 13, 8, 5);
    gotoPos(18, 14); cout << "  _ _    ___ ";
    gotoPos(18, 15); cout << " | U |  | o \\";
    gotoPos(18, 16); cout << " |   |  |  _/";
    gotoPos(18, 17); cout << " |_n_|  |_|  ";
    // 패시브 제거 칸 팻말
    drawSquare(17, 10, 8, 5);
    gotoPos(36, 11); cout << " __      _  _ ";
    gotoPos(36, 12); cout << "/ _> __ | || |";
    gotoPos(36, 13); cout << "\\_ \\/._>| || |";
    gotoPos(36, 14); cout << "<__/\\__.|_||_|";
    // 액티브 칸 팻말
    drawSquare(26, 13, 8, 5);
    gotoPos(54, 14); cout << " ___  __  ___ ";
    gotoPos(54, 15); cout << "| . ||  >|_ _|";
    gotoPos(54, 16); cout << "|   || <_ | | ";
    gotoPos(54, 17); cout << "|_|_|`__/ |_| ";
    // 패시브 칸 팻말
    drawSquare(35, 10, 8, 5);
    gotoPos(72, 11); cout << " ___  ___  __ ";
    gotoPos(72, 12); cout << "| . \\| . |/ _>";
    gotoPos(72, 13); cout << "|  _/|   |\\_ \\";
    gotoPos(72, 14); cout << "|_|  |_|_|<__/";
}

void ShopSceneManager::drawItemCheck() {
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
            gotoPos((7 + ew * i)*2, 10 + j);
            printf("│"); 
        }
    }
    gotoPos(16, 11); cout << "보유 액티브";
    gotoPos(16 + ew*2, 11); cout << "보유 패시브";
    gotoPos(16 + ew*4, 11); cout << "보유 디버프";
    
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
                drawShopScene();
                break;
            }
        }
    }
}
void ShopSceneManager::drawCheckExplanation(int colIdx, int rowIdx) {
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
        gotoPos(desX, desY+2); cout << S.ActiveBook[rowIdx].Name;
        gotoPos(desX, desY+4); cout << S.ActiveBook[rowIdx].Description;
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

void ShopSceneManager::drawCheckArrow(int colIdx, int rowIdx) {
    gotoPos(16 + 20 * colIdx, 13 + rowIdx); cout << "▶";
}
void ShopSceneManager::deleteCheckArrow(int colIdx, int rowIdx) {
    gotoPos(16 + 20 * colIdx, 13 + rowIdx); cout << "  ";
}