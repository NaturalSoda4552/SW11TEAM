
// 게임 방법 화면

#include "Data.h"
#include "HowToPlayScene.h"

// 생성자
HTPSceneManager::HTPSceneManager() {
    htp_key = 1;
    htp_sceneIdx = 0;
}
// 소멸자
HTPSceneManager::~HTPSceneManager() {

}

void HTPSceneManager::inputKey() {
    // while() 안에 존재하기 때문에 SceneManager값이 변경된 최초 1회만 draw() 호출
    if (htp_key) {
        deleteScene();

        drawHtpScene();
        htp_key = 0;
    }

    int key = 0;
    if (_kbhit() != 0) {
        key = _getch();
        // 방향키 입력
        if (key == 224) {
            key = _getch();
            if (key == 75) { // 좌

            }
            else if (key == 77) { // 우

            }
            
        }
        if (key == 27) { // esc
            // 메인화면으로 복귀
            SceneManager = 0;
            htp_key = 1;
        }
    }
}

void HTPSceneManager::drawHtpScene() {
    // 왼쪽, 오른쪽 나눠서 설명
    // 왼쪽은 전투 외, 오른쪽은 전투 설명

    drawSquare(1, 1, 8, 2); 
    gotoPos(4, 2); cout << "게임 규칙";
}