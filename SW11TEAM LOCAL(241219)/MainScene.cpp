
// 메인 화면

#include "Data.h"
#include "MainScene.h"
#include "MapScene.h"

#include "Character.h"

MapSceneManager e;

// 생성자
MainSceneManager::MainSceneManager() {
    main_key = 1;
}
// 소멸자
MainSceneManager::~MainSceneManager() {

}

void MainSceneManager::inputKey() {
    // while() 안에 존재하기 때문에 SceneManager값이 변경된 최초 1회만 draw() 호출
    if (main_key) {
        // 최초 진입 시 
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
        // 방향키 입력
        if (key == 224) {
            key = _getch();
            if (key == 72) { // 명령 중 위
                if (selectedMenuIdx > 0)  selectedMenuIdx--;
            }
            else if (key == 80) { // 명령 중 아래
                if (selectedMenuIdx < 3) selectedMenuIdx++;
            }
            drawSelectArrow();
        }
        // 스페이스 바 입력
        if (key == 32) {
            if (selectedMenuIdx == 0) { // 게임 시작
                // 화면 다 지우기 (나중에 애니메이션도 추가)
                for (int i = 2; i < MAP_OUTLINE_X/2-1; i++) {
                    for (int j = 2; j < MAP_OUTLINE_Y-1; j++) {
                        gotoPos(i*2, j); printf("  ");
                    }
                }

                // 이름 및 직업 입력받기
                p.Get_Player_Name();
                p.Get_Player_Job();

                // 게임 내 초기화 항목들은 여기서 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
                e.initMapSetting(); // 맵 세팅 초기화
                p.Init_Player_Info(); // 캐릭터 정보 초기화
                MapCount = 1;

                // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
                

                // SceneManager 값 변경 
                SceneManager = 4;
            }
            else if (selectedMenuIdx == 1) { // 게임 방법
                deleteScene();

                // SceneManager 값 변경 
                SceneManager = 1;
            }
            else if (selectedMenuIdx == 2) { // 점수 확인
                // 화면 다 지우기 (나중에 애니메이션도 추가)
                deleteScene();

                // SceneManager 값 변경 
                SceneManager = 2;
            }
            else if (selectedMenuIdx == 3) { // 게임 종료
                exit(-1);
            }
            main_key = 1;
        }

    }
}

void MainSceneManager::drawStartScene() {
    // 1. 테두리 그리기
    drawOutLine();

    // 2. 게임 이름 디자인 및 출력
    drawGameName();

    // 3. 그 외 세부 항목 출력
    drawGameMenu();

    // 시작화면 키값 1, 나머지 0 (키 입력 조건에 사용하기 위한)
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
        gotoPos(s_x, s_y + k * 4); printf("┌");
        gotoPos(s_x + 20, s_y + k * 4);  printf("┐");
        gotoPos(s_x, s_y + 2 + k * 4);  printf("└");
        gotoPos(s_x + 20, s_y + 2 + k * 4);  printf("┘");
        for (int i = 1; i < 20; i++) {
            gotoPos(s_x + i, s_y + k * 4); printf("─");
            gotoPos(s_x + i, s_y + 2 + k * 4); printf("─");
        }
        for (int i = 1; i < 2; i++) {
            gotoPos(s_x, s_y + i + k * 4); printf("│");
            gotoPos(s_x + 20, s_y + i + k * 4); printf("│");
        }
    }

    // Menu name
    gotoPos(s_x + 5, s_y + 1); printf("Game Start");
    gotoPos(s_x + 5, s_y + 1 + 4); printf("How To Play");
    gotoPos(s_x + 5, s_y + 1 + 8); printf("Score");
    gotoPos(s_x + 5, s_y + 1 + 12); printf("Exit");

}
void MainSceneManager::drawSelectArrow() {
     // 화살표 모두 지우기
     for (int i = 0; i < 4; i++) {
         gotoPos(menuArrow_X, menuArrow_Y + i * 4); printf("  ");
     }
     // 현재 인덱스에 '▶' 출력
     gotoPos(menuArrow_X, menuArrow_Y + selectedMenuIdx * 4); printf("▶");
}
