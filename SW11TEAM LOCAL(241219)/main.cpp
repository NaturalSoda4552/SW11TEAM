
#include "Data.h"
#include "MainScene.h"
#include "HowToPlayScene.h"
#include "ScoreScene.h"

#include "MapScene.h"
#include "ShopScene.h"
#include "BattleScene.h"
#include "EventScene.h"

#include "Character.h"
#include "Item.h"

#include "Explanation.h"

// 화면 구분 키값
int SceneManager; 
// 0: 메인 화면 / 1: 게임 방법 / 2: 점수 확인 / 4: 맵 화면
// 5: 상점 화면 / 6: 이벤트 화면 / 7: 전투 화면
// 0 -> 4: 이름 입력 및 직업 선택 화면
// 7 -> 0: 패배 화면

// 맵 카운트
int MapCount;
// 1~5 (맵 반복 횟수)

// 설명창 변수
int isMapExplanation;
int isShopExplanation;
int isBattleExplanation;
// 프로그램 실행 후 각 씬 진입 시 최초 1회만 적용

void initGameSetting() {
    // 콘솔 크기와 제목 설정
    char command[100];
    snprintf(command, sizeof(command), "mode con cols=%d lines=%d | title %s", CONSOLE_SIZE_X, CONSOLE_SIZE_Y, TITLE);
    // 명령어 실행
    system(command);

    SceneManager = 0; // 시작 화면 조절, 디폴트는 0 (메인 화면)
    MapCount = 0; // 맵 카운트, 디폴트는 1 (최대 5) : 맵에 들어가자마자 1

    isMapExplanation = 0; // 맵 설명 변수
    isShopExplanation = 0; // 상점 설명 변수
    isBattleExplanation = 0; // 전투 설명 변수

    disableCursor(); // 커서 비활성화
    drawOutLine(); // 게임판 테두리 그리기
}

int main() {
    // 메인 화면 클래스
    MainSceneManager a;
    HTPSceneManager b;
    ScoreSceneManager c;

    // MapSceneManager e; // extern 전역으로 빼서 주석처리함
    ShopSceneManager f;
    EventSceneManager g;
    BattleSceneManager h; 

    // 게임 세팅
    initGameSetting();
    //p.Init_Player_Info(); // 디버그용, 원래는 게임 시작 시 호출

    while (1) {
        if (SceneManager == 0) a.inputKey(); // 메인 화면
        if (SceneManager == 1) b.inputKey(); // 게임 방법 화면
        if (SceneManager == 2) c.inputKey(); // 점수 화면

        if (SceneManager == 4) e.inputKey(); // 맵 화면
        if (SceneManager == 5) f.inputKey(); // 상점 화면
        if (SceneManager == 6) g.inputKey(); // 이벤트 화면
        if (SceneManager == 7) h.inputKey(); // 전투 화면
    }
}
