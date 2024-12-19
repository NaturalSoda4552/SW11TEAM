
// 맵 화면

#include "Data.h"
#include "SceneASCIIAsset.h"
#include "MapScene.h"

#include "Character.h"

#include "Explanation.h"

int isBoss;

// 생성자
MapSceneManager::MapSceneManager() {
    initMapSetting();
}
// 소멸자
MapSceneManager::~MapSceneManager() {

}
void MapSceneManager::inputKey() {
    if (MapCount >= 6) {
        // 맵 카운트가 6 이상 -> 게임 종료
        drawGameClearScene();
    }

    if (map_key) {
        deleteScene();
        drawMapScene();
        map_key = 0;
    }
    // 맵 설명
    if (!isMapExplanation) {

        // 설명창 그리기
        drawMapExplanation();
        // 맵 에셋 그리기 <- 설명창뜨면 에셋이 지워지기 때문에 다시 그리기
        drawMapScene();

        isMapExplanation = 1;
    }

    int key = 0;
    if (_kbhit() != 0) {

        key = _getch();
        if (!p.ShowInfo) { // 정보창을 보고 있지 않을 때만 작동
            // 방향키 입력
            if (key == 224) {
                key = _getch();

                if (!isMovable && key == 77) { // 오른쪽 - 이동명령 켜짐
                    // 보스방까지 이동했을 시 그 다음은 isMovable 비활성화
                    if (playerPosIdx.X + 1 <= MAP_MAX_X - 1) isMovable = 1;
                }
                else if (isMovable && key == 75) isMovable = 0; // 왼쪽 - 이동명령 꺼짐

                if (isMovable && key == 72) { // 명령 중 위
                    deleteNextPlayerPos();
                    for (int i = nextStageIdx - 1; i >= 0; i--) {
                        if (Map[i][playerPosIdx.X + 1] != RoomType::EMPTY) {
                            nextStageIdx = i;
                            break;
                        }
                    }
                    drawNextPlayerPos();
                }
                else if (isMovable && key == 80) { // 명령 중 아래
                    deleteNextPlayerPos();
                    for (int i = nextStageIdx + 1; i < MAP_MAX_Y; i++) {
                        if (Map[i][playerPosIdx.X + 1] != RoomType::EMPTY) {
                            nextStageIdx = i;
                            break;
                        }
                    }
                    drawNextPlayerPos();
                }
                
            }
            // 스페이스 바 입력
            if (isMovable && key == 32) {
                // 이동 명령일 때 스페이스 바 입력 시
                deletePlayerPos();
                deleteNextPlayerPos();

                // 디버프 체크
                if (p.DebuffManager[0] != 0) {
                    p.HP -= p.DebuffManager[0] * 3; // 가진 중독 * 3 만큼 데미지
                    if (p.HP < 1) p.HP = 1;
                }

                playerPosIdx.X++;
                p.Move++;
                playerPosIdx.Y = nextStageIdx;

                // 이동 완료 시 미리 다음 이동할 스테이지 인덱스 찾기
                for (int i = 0; i < MAP_MAX_Y; i++) {
                    if (Map[i][playerPosIdx.X + 1] != RoomType::EMPTY) {
                        nextStageIdx = i;
                        break;
                    }
                }

                // 스테이지는 한 번 들어가면 나올 수 없음 -> key
                isStopByMonster = 1;
                isStopByShop = 1;
                isStopByEvent = 1;

                isMovable = 0;
                drawPlayerPos();
                drawNextPlayerPos();

                // 이동한 스테이지가 상점일 시
                if (Map[playerPosIdx.Y][playerPosIdx.X] == RoomType::SHOP) {
                    // 바로 상점씬 진입
                    isStopByShop = 0;
                    // SceneManager
                    SceneManager = 5;
                    map_key = 1;
                }
                // 이동한 스테이지가 몬스터일 시
                if (Map[playerPosIdx.Y][playerPosIdx.X] == RoomType::MONSTER) {
                    isBoss = 0;

                    // 바로 몬스터씬 진입
                    isStopByMonster = 0;
                    // SceneManager
                    SceneManager = 7;
                    map_key = 1;
                }
                // 이동한 스테이지가 이벤트일 시
                if (Map[playerPosIdx.Y][playerPosIdx.X] == RoomType::EVENT) {
                    // 바로 이벤트씬 진입
                    isStopByEvent = 0;
                    // SceneManager
                    SceneManager = 6;
                    map_key = 1;
                }
                // 보스방 시
                if (Map[playerPosIdx.Y][playerPosIdx.X] == RoomType::BOSS) {
                    isBoss = 1;

                    // 바로 보스 화면 진입
                    isStopByMonster = 0;
                    // SceneManager
                    SceneManager = 7;
                    p.Move++;
                    map_key = 1;

                    MapCount++;

                    // 초기화하는 함수 따로 빼기
                    // 맵 초기화
                    initMap();
                    // 맵 랜덤 구성
                    setRoomType();

                    // 플레이어 위치 초기화
                    initPlayerPos();

                    // 보스 클리어 점수 추가
                    p.Accum_Score(1);
                }
            }
            else if (key == 32) { // space 눌러서 이동하는 건 현재 x
                // 상점일 시
                if (!isMovable && Map[playerPosIdx.Y][playerPosIdx.X] == RoomType::SHOP 
                    && isStopByShop) {

                    isStopByShop = 0;
                    // SceneManager
                    SceneManager = 5;
                    map_key = 1;
                }
                // 전투일 시
                if (!isMovable && (Map[playerPosIdx.Y][playerPosIdx.X] == RoomType::MONSTER)
                    && isStopByMonster) {
                    // 몬스터인지 보스인지 판별
                    if (Map[playerPosIdx.Y][playerPosIdx.X] == RoomType::MONSTER) isBoss = 0;
                    else isBoss = 1;

                    isStopByMonster = 0;
                    // SceneManager
                    SceneManager = 7;
                    map_key = 1;
                }
            }

            if (key == 72 || key == 80 || key == 77) {
                drawNextPlayerPos();
                drawPlayerPos();
            }
            else if (key == 75) {
                if (playerPosIdx.X < MAP_MAX_X - 1) deleteNextPlayerPos();
                drawPlayerPos();
            }
        }
        // tab키
        if (key == 9) {
            if (!p.ShowInfo) {
                p.Show_Player_Info();
            }
            drawMapScene();
        }
    }
}

void MapSceneManager::drawMapLevel() {
    drawSquare(1, 1, 2, 2);
    gotoPos(4, 2); cout << MapCount;
}

void MapSceneManager::drawMapScene() {
    // 맵 단계 출력
    drawMapLevel();

    // 맵 에셋 그리기
    drawMapAsset();
    // 맵 그리기
    drawMap();
    // 플레이어 위치 그리기
    drawPlayerPos();
}

void MapSceneManager::initMapSetting() {
    map_key = 1;

    // 이동 명령
    isMovable = 0;
    nextStageIdx = 0;
    // 플레이어 위치 인덱스
    playerPosIdx = { 0, 0 };

    // 맵 초기화
    initMap();
    // 스테이지 랜덤 배치
    setRoomType();
    // 플레이어 위치 인덱스 초기화
    initPlayerPos();
}

string MapSceneManager::getRoomTypeName(RoomType type) {
	switch (type) {
	case RoomType::EMPTY:   return "X";
	case RoomType::DEFAULT:   return "기본";
	case RoomType::MONSTER: return "몬스터";
	case RoomType::SHOP:    return "상점";
	case RoomType::EVENT:   return "이벤트";
	case RoomType::BOSS:    return "보스";
	default:                return "알수없음";
	}
}
RoomType MapSceneManager::setRandomRoomType() {
	int key = rand() % 2;
	switch (key) {
	case 0: return RoomType::MONSTER;
    case 1:    return RoomType::EVENT;
	case 2:    return RoomType::SHOP;
	
		// default: return;
	}
}
void MapSceneManager::initMap() {
	// 맵 배열 생성, RoomType::EMPTY로 초기화
	Map = new RoomType * [MAP_MAX_Y];
	for (int i = 0; i < MAP_MAX_Y; i++) {
		Map[i] = new RoomType[MAP_MAX_X];
		// 각 요소를 RoomType::EMPTY로 초기화
		for (int j = 0; j < MAP_MAX_X; j++) {
			Map[i][j] = RoomType::EMPTY;
		}
	}
    for (int i=0;i<MAP_MAX_X;i++)
        stageCnt[i]=0;
	// return map;
}
void MapSceneManager::setRoomType() {
    srand(time(NULL)); // 시드 랜덤
    int stageNum;

    // 1. 0번째와 9번째는 고정
    Map[1][0] = RoomType::DEFAULT;
    Map[1][MAP_MAX_X - 1] = RoomType::BOSS;

    // 2. 한 열이 전부 상점, 맵당 두 번
    int randomAllShopIdx1 = rand() % (MAP_MAX_X / 2 - 1) + MAP_MAX_X / 2; // 절반 기준 오른쪽에 배치
    int randomAllShopIdx2 = rand() % (MAP_MAX_X / 2 - 2) + 1; // 절반 기준 왼쪽에 배치

    stageNum = rand() % 3 + 1;
    for (int i = 0; i < stageNum; i++) {
        Map[i][randomAllShopIdx1] = RoomType::SHOP;
    }
    stageNum = rand() % 3 + 1;
    for (int i = 0; i < stageNum; i++) {
        Map[i][randomAllShopIdx2] = RoomType::SHOP;
    }

    // 3. 한 열이 전부 몬스터, 맵당 두 번
    vector<int> availableMonster1;
    vector<int> availableMonster2;
    // vector<int> availableMonster3;
    for (int j = 1; j < MAP_MAX_X - 1; j++) {
        // 배치 가능 인덱스 저장, 절반 나눠서 하나씩
        if (j >= MAP_MAX_X / 2 && Map[0][j] == RoomType::EMPTY) availableMonster1.push_back(j);
        if (j < MAP_MAX_X / 2 && Map[0][j] == RoomType::EMPTY) availableMonster2.push_back(j);
        // if (j < MAP_MAX_X / 3 && Map[0][j] == RoomType::EMPTY) availableMonster3.push_back(j);
    }
    // 배치 가능 인덱스 중 2개를 무작위로 뽑아 그 인덱스에 해당하는 한 열을 모두 몬스터로 채우기
    int availableMonsterIdx1 = rand() % availableMonster1.size();
    int availableMonsterIdx2 = rand() % availableMonster2.size();
    // int availableMonsterIdx3 = rand() % availableMonster3.size();
    // if (availableMonsterIdx2 >= availableMonsterIdx1) availableMonsterIdx2++;

    int randomAllMonsterIdx1 = availableMonster1[availableMonsterIdx1];
    int randomAllMonsterIdx2 = availableMonster2[availableMonsterIdx2];
    // int randomAllMonsterIdx3 = availableMonster3[availableMonsterIdx3];

    stageNum = rand() % 3 + 1;
    for (int i = 0; i < stageNum; i++) {
        Map[i][randomAllMonsterIdx1] = RoomType::MONSTER;
    }
    stageNum = rand() % 3 + 1;
    for (int i = 0; i < stageNum; i++) {
        Map[i][randomAllMonsterIdx2] = RoomType::MONSTER;
    }
    stageNum = rand() % 3 + 1;
    for (int i = 0; i < stageNum; i++) {
        // Map[i][randomAllMonsterIdx3] = RoomType::MONSTER;
    }

    // -> 남은 인덱스: MAP_MAX_X - 4
    // 몬스터:이벤트:상점 = 2:3:1 정도

    // 4. 상점+이벤트 열 

    // 5. 이벤트+몬스터 열

    // 그 외. EMPTY 자리에 랜덤 스테이지 배정
    /* */
    for (int j = 1; j < MAP_MAX_X - 1; j++) {
        // j번째 행에 스테이지가 이미 존재하는지 검사
        int isChecked = 1;
        for (int i = 0; i < MAP_MAX_Y; i++) {
            // 방 타입이 빈 방(X)일 때만 랜덤 삽입
            if (Map[i][j] != RoomType::EMPTY) {
                isChecked = 0;
            }
        }

        if (isChecked) {
            /*
            // 한 열의 스테이지 배치 가능 인덱스 저장
            vector<int> availableIdx;
            for (int i = 0; i < MAP_MAX_Y; i++) {
                // 방 타입이 빈 방(X)일 때만 랜덤 삽입
                if (Map[i][j] == RoomType::EMPTY) {
                    availableIdx.push_back(i);
                }
            }
            // 한 열에 배치할 방의 개수 i: 1~3개
            stageNum = rand() % 3 + 1;
            for (int i = 0; i < stageNum && !availableIdx.empty(); i++) {
                int randomIdx = rand() % availableIdx.size();
                int idx = availableIdx[randomIdx];

                // 선택된 위치에 랜덤한 방 타입 배치
                RoomType room = setRandomRoomType();
                Map[idx][j] = room;

                // 사용한 인덱스 제거
                availableIdx.erase(availableIdx.begin() + randomIdx);
            }
            */

            // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
            // 한 행에 넣을 스테이지 개수 랜덤 (1~3)
            stageNum = rand() % 3 + 1;
            for (int i = 0; i < stageNum; i++) {
                RoomType room = setRandomRoomType();
                Map[i][j] = room;
            }


        }
    }

    // 각 행에 스테이지 개수 판별 -> stageCnt[]에 저장
    for (int i = 0; i < MAP_MAX_Y; i++) {
        for (int j = 0; j < MAP_MAX_X; j++) {
            if (Map[i][j] != RoomType::EMPTY) stageCnt[j] += 1;
        }
    }
}

void MapSceneManager::drawMap() {
    // 전체 맵의 가로는 112
    // 전체 맵의 세로는 32

    // 1 - 1. 스테이지가 1, 3개인 경우
    for (int j = 0; j < MAP_MAX_X; j++) {
        for (int i = 0; i < MAP_MAX_Y; i++) {
            if (Map[i][j] != RoomType::EMPTY && stageCnt[j] == 1) {
                drawStage(j * 13 + 2, 18, 4, Map[i][j]);
            }
            else if (Map[i][j] != RoomType::EMPTY && stageCnt[j] == 2) {
                drawStage(j * 13 + 2, 15 + i*6 , 4, Map[i][j]);
            }
            else if (Map[i][j] != RoomType::EMPTY && stageCnt[j] == 3) {
                drawStage(j * 13 + 2, 13 + i * 5, 4, Map[i][j]);
            }
        }
    }
}
void MapSceneManager::drawStage(int curX, int curY, int size, RoomType room) {
    gotoPos(curX, curY);  printf("┌");
    gotoPos(curX + size * 2, curY);  printf("┐");
    gotoPos(curX, curY + size);  printf("└");
    gotoPos(curX + size * 2, curY + size);  printf("┘");
    for (int i = 1; i < 2 * size; i++) {
        gotoPos(curX + i, curY); printf("─");
        gotoPos(curX + i, curY + size); printf("─");
    }
    for (int i = 1; i < size; i++) {
        gotoPos(curX, curY + i); printf("│");
        gotoPos(curX + size * 2, curY + i); printf("│");
    }
    gotoPos(curX + size, curY + size);
    cout << getRoomTypeName(room);
}
void MapSceneManager::drawMapAsset() {
    // 에셋 그리기

    // 구름 1
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            gotoPos(10 + j, 5 + i);
            cout << mapCloudModel1[i][j];
        }
    }
    // 구름 2
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 11; j++) {
            gotoPos(26 + j, 6 + i);
            cout << mapCloudModel2[i][j];
        }
    }
    // 구름 3
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 11; j++) {
            gotoPos(42 + j, 3 + i);
            cout << mapCloudModel3[i][j];
        }
    }
    // 구름 2
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 11; j++) {
            gotoPos(52 + j, 7 + i);
            cout << mapCloudModel2[i][j];
        }
    }
    // 구름 3
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 11; j++) {
            gotoPos(65 + j, 2 + i);
            cout << mapCloudModel3[i][j];
        }
    }
    // 구름 3
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 11; j++) {
            gotoPos(85 + j, 8 + i);
            cout << mapCloudModel3[i][j];
        }
    }
    // 구름 1
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            gotoPos(82 + j, 3 + i);
            cout << mapCloudModel1[i][j];
        }
    }

    // 바닥 1, 2
    for (int k = 0; k < 10; k++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 12; j++) {
                gotoPos(2 + 12*k + j, 27 + i);
                if (2 + 12 * k + j >= MAP_OUTLINE_X) break;
                cout << mapGroundModel[k%2][i][j];
            }
        }
    }
    

}

void MapSceneManager::initPlayerPos() {
    for (int i = 0; i < MAP_MAX_Y; i++) {
        if (Map[i][0] == RoomType::DEFAULT) {
            playerPosIdx = { 0, (short)i };
            break;
        }
    }

    for (int i = 0; i < MAP_MAX_Y; i++) {
        if (Map[i][playerPosIdx.X + 1] != RoomType::EMPTY) {
            nextStageIdx = i;
            break;
        }
    }
}
void MapSceneManager::drawPlayerPos() {
    
    // 플레이어 위치 그리기
    for (int j = 0; j < MAP_MAX_X; j++) {
        for (int i = 0; i < MAP_MAX_Y; i++) {
        
            if (i == playerPosIdx.Y && j == playerPosIdx.X) {
                if (stageCnt[j] == 1) gotoPos(j * 13 + 2 + 4, 18 + 2);
                else if (stageCnt[j] == 2) gotoPos(j * 13 + 2 + 4, 15 + i*6 + 2);
                else if  (stageCnt[j] == 3) gotoPos(j * 13 + 2 + 4, 13 + i*5 + 2);

                // gotoPos(j * 13 + 2 + 4, i * 8 + 2 + 2);
                if (!isMovable) cout << " P ";
                else cout << "[P]";
            }
        }
    }
}
void MapSceneManager::deletePlayerPos() {
    // 플레이어 위치 지우기
    for (int j = 0; j < MAP_MAX_X; j++) {
        for (int i = 0; i < MAP_MAX_Y; i++) {
            if (i == playerPosIdx.Y && j == playerPosIdx.X) {
                if (stageCnt[j] == 1) gotoPos(j * 13 + 2 + 4, 18 + 2);
                else if (stageCnt[j] == 2) gotoPos(j * 13 + 2 + 4, 15 + i * 6 + 2);
                else if (stageCnt[j] == 3) gotoPos(j * 13 + 2 + 4, 13 + i * 5 + 2);

                cout << "   ";
            }
        }
    }
}
void MapSceneManager::drawNextPlayerPos() {
    // 이동 명령일 시 다음 이동할 스테이지 표시
    int nextX = playerPosIdx.X + 1;
    for (int j = 0; j < MAP_MAX_Y; j++) {
        if (isMovable && j == nextStageIdx) {
            if (stageCnt[nextX] == 1) gotoPos(nextX * 13 + 2 + 4, 18 + 2);
            else if (stageCnt[nextX] == 2) gotoPos(nextX * 13 + 2 + 4, 15 + j * 6 + 2);
            else if (stageCnt[nextX] == 3) gotoPos(nextX * 13 + 2 + 4, 13 + j * 5 + 2);
            // gotoPos((playerPosIdx.X + 1) * 13 + 2 + 4, j * 8 + 2 + 2);
            cout << "★";
        }
    }
}
void MapSceneManager::deleteNextPlayerPos() {
    int nextX = playerPosIdx.X + 1;
    for (int j = 0; j < MAP_MAX_Y; j++) {
        if (isMovable && j == nextStageIdx) {
            if (stageCnt[nextX] == 1) gotoPos(nextX * 13 + 2 + 4, 18 + 2);
            else if (stageCnt[nextX] == 2) gotoPos(nextX * 13 + 2 + 4, 15 + j * 6 + 2);
            else if (stageCnt[nextX] == 3) gotoPos(nextX * 13 + 2 + 4, 13 + j * 5 + 2);
            // gotoPos((playerPosIdx.X + 1) * 13 + 2 + 4, j * 8 + 2 + 2);
            cout << "  ";
        }
        else if (!isMovable && playerPosIdx.X <= MAP_MAX_X - 1) {
            if (stageCnt[nextX] == 1) gotoPos(nextX * 13 + 2 + 4, 18 + 2);
            else if (stageCnt[nextX] == 2) gotoPos(nextX * 13 + 2 + 4, 15 + j * 6 + 2);
            else if (stageCnt[nextX] == 3) gotoPos(nextX * 13 + 2 + 4, 13 + j * 5 + 2);
            // gotoPos((playerPosIdx.X + 1) * 13 + 2 + 4, j * 8 + 2 + 2);
            cout << "  ";
        }

    }

}

void MapSceneManager::drawGameClearScene() {
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

    // 점수 합산하기
    for (int i = 0; i < p.Defeat; i++) p.Accum_Score(1); // 적 처치
    for (int i = 0; i < p.Move; i++) p.Accum_Score(3); // 이동
    p.Accum_Score(5); // 게임 승리 시 

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
                    SceneManager = 2;
                    break;
                }
                else { // back to main
                    SceneManager = 0;
                    break;
                }
            }

        }
    }
}
void MapSceneManager::drawGoSceneArrow(int idx) {
    gotoPos(42, 23 + idx * 4); cout << "▶";
}
void MapSceneManager::deleteGoSceneArrow(int idx) {
    gotoPos(42, 23 + idx * 4); cout << "  ";
}