
// 게임 점수 화면

#include "Data.h"
#include "ScoreScene.h"

// 생성자
ScoreSceneManager::ScoreSceneManager() {
    score_key = 1;
}
// 소멸자
ScoreSceneManager::~ScoreSceneManager() {

}

void ScoreSceneManager::inputKey() {
    // while() 안에 존재하기 때문에 SceneManager값이 변경된 최초 1회만 draw() 호출
    if (score_key) {
        deleteScene();

        drawScoreScene();
        score_key = 0;
    }

    int key = 0;
    if (_kbhit() != 0) {
        key = _getch();
        // 방향키 입력
        if (key == 224) {
            key = _getch();
        }
        if (key == 27) { // esc
            // 메인화면으로 복귀
            SceneManager = 0;
            score_key = 1;
        }
    }
}

void ScoreSceneManager::drawScoreScene() {
    gotoPos(MAP_OUTLINE_X / 2 - 6, MAP_OUTLINE_Y / 2 - 8);
    printf("게임 점수입니다.");
}