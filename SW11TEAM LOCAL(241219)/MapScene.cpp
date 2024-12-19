
// �� ȭ��

#include "Data.h"
#include "SceneASCIIAsset.h"
#include "MapScene.h"

#include "Character.h"

#include "Explanation.h"

int isBoss;

// ������
MapSceneManager::MapSceneManager() {
    initMapSetting();
}
// �Ҹ���
MapSceneManager::~MapSceneManager() {

}
void MapSceneManager::inputKey() {
    if (MapCount >= 6) {
        // �� ī��Ʈ�� 6 �̻� -> ���� ����
        drawGameClearScene();
    }

    if (map_key) {
        deleteScene();
        drawMapScene();
        map_key = 0;
    }
    // �� ����
    if (!isMapExplanation) {

        // ����â �׸���
        drawMapExplanation();
        // �� ���� �׸��� <- ����â�߸� ������ �������� ������ �ٽ� �׸���
        drawMapScene();

        isMapExplanation = 1;
    }

    int key = 0;
    if (_kbhit() != 0) {

        key = _getch();
        if (!p.ShowInfo) { // ����â�� ���� ���� ���� ���� �۵�
            // ����Ű �Է�
            if (key == 224) {
                key = _getch();

                if (!isMovable && key == 77) { // ������ - �̵���� ����
                    // ��������� �̵����� �� �� ������ isMovable ��Ȱ��ȭ
                    if (playerPosIdx.X + 1 <= MAP_MAX_X - 1) isMovable = 1;
                }
                else if (isMovable && key == 75) isMovable = 0; // ���� - �̵���� ����

                if (isMovable && key == 72) { // ��� �� ��
                    deleteNextPlayerPos();
                    for (int i = nextStageIdx - 1; i >= 0; i--) {
                        if (Map[i][playerPosIdx.X + 1] != RoomType::EMPTY) {
                            nextStageIdx = i;
                            break;
                        }
                    }
                    drawNextPlayerPos();
                }
                else if (isMovable && key == 80) { // ��� �� �Ʒ�
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
            // �����̽� �� �Է�
            if (isMovable && key == 32) {
                // �̵� ����� �� �����̽� �� �Է� ��
                deletePlayerPos();
                deleteNextPlayerPos();

                // ����� üũ
                if (p.DebuffManager[0] != 0) {
                    p.HP -= p.DebuffManager[0] * 3; // ���� �ߵ� * 3 ��ŭ ������
                    if (p.HP < 1) p.HP = 1;
                }

                playerPosIdx.X++;
                p.Move++;
                playerPosIdx.Y = nextStageIdx;

                // �̵� �Ϸ� �� �̸� ���� �̵��� �������� �ε��� ã��
                for (int i = 0; i < MAP_MAX_Y; i++) {
                    if (Map[i][playerPosIdx.X + 1] != RoomType::EMPTY) {
                        nextStageIdx = i;
                        break;
                    }
                }

                // ���������� �� �� ���� ���� �� ���� -> key
                isStopByMonster = 1;
                isStopByShop = 1;
                isStopByEvent = 1;

                isMovable = 0;
                drawPlayerPos();
                drawNextPlayerPos();

                // �̵��� ���������� ������ ��
                if (Map[playerPosIdx.Y][playerPosIdx.X] == RoomType::SHOP) {
                    // �ٷ� ������ ����
                    isStopByShop = 0;
                    // SceneManager
                    SceneManager = 5;
                    map_key = 1;
                }
                // �̵��� ���������� ������ ��
                if (Map[playerPosIdx.Y][playerPosIdx.X] == RoomType::MONSTER) {
                    isBoss = 0;

                    // �ٷ� ���;� ����
                    isStopByMonster = 0;
                    // SceneManager
                    SceneManager = 7;
                    map_key = 1;
                }
                // �̵��� ���������� �̺�Ʈ�� ��
                if (Map[playerPosIdx.Y][playerPosIdx.X] == RoomType::EVENT) {
                    // �ٷ� �̺�Ʈ�� ����
                    isStopByEvent = 0;
                    // SceneManager
                    SceneManager = 6;
                    map_key = 1;
                }
                // ������ ��
                if (Map[playerPosIdx.Y][playerPosIdx.X] == RoomType::BOSS) {
                    isBoss = 1;

                    // �ٷ� ���� ȭ�� ����
                    isStopByMonster = 0;
                    // SceneManager
                    SceneManager = 7;
                    p.Move++;
                    map_key = 1;

                    MapCount++;

                    // �ʱ�ȭ�ϴ� �Լ� ���� ����
                    // �� �ʱ�ȭ
                    initMap();
                    // �� ���� ����
                    setRoomType();

                    // �÷��̾� ��ġ �ʱ�ȭ
                    initPlayerPos();

                    // ���� Ŭ���� ���� �߰�
                    p.Accum_Score(1);
                }
            }
            else if (key == 32) { // space ������ �̵��ϴ� �� ���� x
                // ������ ��
                if (!isMovable && Map[playerPosIdx.Y][playerPosIdx.X] == RoomType::SHOP 
                    && isStopByShop) {

                    isStopByShop = 0;
                    // SceneManager
                    SceneManager = 5;
                    map_key = 1;
                }
                // ������ ��
                if (!isMovable && (Map[playerPosIdx.Y][playerPosIdx.X] == RoomType::MONSTER)
                    && isStopByMonster) {
                    // �������� �������� �Ǻ�
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
        // tabŰ
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
    // �� �ܰ� ���
    drawMapLevel();

    // �� ���� �׸���
    drawMapAsset();
    // �� �׸���
    drawMap();
    // �÷��̾� ��ġ �׸���
    drawPlayerPos();
}

void MapSceneManager::initMapSetting() {
    map_key = 1;

    // �̵� ���
    isMovable = 0;
    nextStageIdx = 0;
    // �÷��̾� ��ġ �ε���
    playerPosIdx = { 0, 0 };

    // �� �ʱ�ȭ
    initMap();
    // �������� ���� ��ġ
    setRoomType();
    // �÷��̾� ��ġ �ε��� �ʱ�ȭ
    initPlayerPos();
}

string MapSceneManager::getRoomTypeName(RoomType type) {
	switch (type) {
	case RoomType::EMPTY:   return "X";
	case RoomType::DEFAULT:   return "�⺻";
	case RoomType::MONSTER: return "����";
	case RoomType::SHOP:    return "����";
	case RoomType::EVENT:   return "�̺�Ʈ";
	case RoomType::BOSS:    return "����";
	default:                return "�˼�����";
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
	// �� �迭 ����, RoomType::EMPTY�� �ʱ�ȭ
	Map = new RoomType * [MAP_MAX_Y];
	for (int i = 0; i < MAP_MAX_Y; i++) {
		Map[i] = new RoomType[MAP_MAX_X];
		// �� ��Ҹ� RoomType::EMPTY�� �ʱ�ȭ
		for (int j = 0; j < MAP_MAX_X; j++) {
			Map[i][j] = RoomType::EMPTY;
		}
	}
    for (int i=0;i<MAP_MAX_X;i++)
        stageCnt[i]=0;
	// return map;
}
void MapSceneManager::setRoomType() {
    srand(time(NULL)); // �õ� ����
    int stageNum;

    // 1. 0��°�� 9��°�� ����
    Map[1][0] = RoomType::DEFAULT;
    Map[1][MAP_MAX_X - 1] = RoomType::BOSS;

    // 2. �� ���� ���� ����, �ʴ� �� ��
    int randomAllShopIdx1 = rand() % (MAP_MAX_X / 2 - 1) + MAP_MAX_X / 2; // ���� ���� �����ʿ� ��ġ
    int randomAllShopIdx2 = rand() % (MAP_MAX_X / 2 - 2) + 1; // ���� ���� ���ʿ� ��ġ

    stageNum = rand() % 3 + 1;
    for (int i = 0; i < stageNum; i++) {
        Map[i][randomAllShopIdx1] = RoomType::SHOP;
    }
    stageNum = rand() % 3 + 1;
    for (int i = 0; i < stageNum; i++) {
        Map[i][randomAllShopIdx2] = RoomType::SHOP;
    }

    // 3. �� ���� ���� ����, �ʴ� �� ��
    vector<int> availableMonster1;
    vector<int> availableMonster2;
    // vector<int> availableMonster3;
    for (int j = 1; j < MAP_MAX_X - 1; j++) {
        // ��ġ ���� �ε��� ����, ���� ������ �ϳ���
        if (j >= MAP_MAX_X / 2 && Map[0][j] == RoomType::EMPTY) availableMonster1.push_back(j);
        if (j < MAP_MAX_X / 2 && Map[0][j] == RoomType::EMPTY) availableMonster2.push_back(j);
        // if (j < MAP_MAX_X / 3 && Map[0][j] == RoomType::EMPTY) availableMonster3.push_back(j);
    }
    // ��ġ ���� �ε��� �� 2���� �������� �̾� �� �ε����� �ش��ϴ� �� ���� ��� ���ͷ� ä���
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

    // -> ���� �ε���: MAP_MAX_X - 4
    // ����:�̺�Ʈ:���� = 2:3:1 ����

    // 4. ����+�̺�Ʈ �� 

    // 5. �̺�Ʈ+���� ��

    // �� ��. EMPTY �ڸ��� ���� �������� ����
    /* */
    for (int j = 1; j < MAP_MAX_X - 1; j++) {
        // j��° �࿡ ���������� �̹� �����ϴ��� �˻�
        int isChecked = 1;
        for (int i = 0; i < MAP_MAX_Y; i++) {
            // �� Ÿ���� �� ��(X)�� ���� ���� ����
            if (Map[i][j] != RoomType::EMPTY) {
                isChecked = 0;
            }
        }

        if (isChecked) {
            /*
            // �� ���� �������� ��ġ ���� �ε��� ����
            vector<int> availableIdx;
            for (int i = 0; i < MAP_MAX_Y; i++) {
                // �� Ÿ���� �� ��(X)�� ���� ���� ����
                if (Map[i][j] == RoomType::EMPTY) {
                    availableIdx.push_back(i);
                }
            }
            // �� ���� ��ġ�� ���� ���� i: 1~3��
            stageNum = rand() % 3 + 1;
            for (int i = 0; i < stageNum && !availableIdx.empty(); i++) {
                int randomIdx = rand() % availableIdx.size();
                int idx = availableIdx[randomIdx];

                // ���õ� ��ġ�� ������ �� Ÿ�� ��ġ
                RoomType room = setRandomRoomType();
                Map[idx][j] = room;

                // ����� �ε��� ����
                availableIdx.erase(availableIdx.begin() + randomIdx);
            }
            */

            // �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
            // �� �࿡ ���� �������� ���� ���� (1~3)
            stageNum = rand() % 3 + 1;
            for (int i = 0; i < stageNum; i++) {
                RoomType room = setRandomRoomType();
                Map[i][j] = room;
            }


        }
    }

    // �� �࿡ �������� ���� �Ǻ� -> stageCnt[]�� ����
    for (int i = 0; i < MAP_MAX_Y; i++) {
        for (int j = 0; j < MAP_MAX_X; j++) {
            if (Map[i][j] != RoomType::EMPTY) stageCnt[j] += 1;
        }
    }
}

void MapSceneManager::drawMap() {
    // ��ü ���� ���δ� 112
    // ��ü ���� ���δ� 32

    // 1 - 1. ���������� 1, 3���� ���
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
    gotoPos(curX, curY);  printf("��");
    gotoPos(curX + size * 2, curY);  printf("��");
    gotoPos(curX, curY + size);  printf("��");
    gotoPos(curX + size * 2, curY + size);  printf("��");
    for (int i = 1; i < 2 * size; i++) {
        gotoPos(curX + i, curY); printf("��");
        gotoPos(curX + i, curY + size); printf("��");
    }
    for (int i = 1; i < size; i++) {
        gotoPos(curX, curY + i); printf("��");
        gotoPos(curX + size * 2, curY + i); printf("��");
    }
    gotoPos(curX + size, curY + size);
    cout << getRoomTypeName(room);
}
void MapSceneManager::drawMapAsset() {
    // ���� �׸���

    // ���� 1
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            gotoPos(10 + j, 5 + i);
            cout << mapCloudModel1[i][j];
        }
    }
    // ���� 2
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 11; j++) {
            gotoPos(26 + j, 6 + i);
            cout << mapCloudModel2[i][j];
        }
    }
    // ���� 3
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 11; j++) {
            gotoPos(42 + j, 3 + i);
            cout << mapCloudModel3[i][j];
        }
    }
    // ���� 2
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 11; j++) {
            gotoPos(52 + j, 7 + i);
            cout << mapCloudModel2[i][j];
        }
    }
    // ���� 3
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 11; j++) {
            gotoPos(65 + j, 2 + i);
            cout << mapCloudModel3[i][j];
        }
    }
    // ���� 3
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 11; j++) {
            gotoPos(85 + j, 8 + i);
            cout << mapCloudModel3[i][j];
        }
    }
    // ���� 1
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            gotoPos(82 + j, 3 + i);
            cout << mapCloudModel1[i][j];
        }
    }

    // �ٴ� 1, 2
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
    
    // �÷��̾� ��ġ �׸���
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
    // �÷��̾� ��ġ �����
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
    // �̵� ����� �� ���� �̵��� �������� ǥ��
    int nextX = playerPosIdx.X + 1;
    for (int j = 0; j < MAP_MAX_Y; j++) {
        if (isMovable && j == nextStageIdx) {
            if (stageCnt[nextX] == 1) gotoPos(nextX * 13 + 2 + 4, 18 + 2);
            else if (stageCnt[nextX] == 2) gotoPos(nextX * 13 + 2 + 4, 15 + j * 6 + 2);
            else if (stageCnt[nextX] == 3) gotoPos(nextX * 13 + 2 + 4, 13 + j * 5 + 2);
            // gotoPos((playerPosIdx.X + 1) * 13 + 2 + 4, j * 8 + 2 + 2);
            cout << "��";
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
    // ȭ�� �� �����
    deleteScene();

    // �й�ȭ�� �׸���
    // ���ӿ��� ����
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


    // ���� �нú� ��� ǥ�� -> ?

    // ���� ǥ�� �� ����
    drawSquare(17, 15, 17, 5);
    gotoPos(49, 16); cout << "[SCORE]";

    // ���� �ջ��ϱ�
    for (int i = 0; i < p.Defeat; i++) p.Accum_Score(1); // �� óġ
    for (int i = 0; i < p.Move; i++) p.Accum_Score(3); // �̵�
    p.Accum_Score(5); // ���� �¸� �� 

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
    gotoPos(42, 23 + idx * 4); cout << "��";
}
void MapSceneManager::deleteGoSceneArrow(int idx) {
    gotoPos(42, 23 + idx * 4); cout << "  ";
}