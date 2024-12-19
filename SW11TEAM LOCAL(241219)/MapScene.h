#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <conio.h>
#include <windows.h>

// �� ȭ��
class MapSceneManager{
public:
	int map_key;

	int isStopByShop; // ���� 1ȸ�� ���尡��
	int isStopByMonster; // ���� 1ȸ�� ���尡��
	int isStopByEvent; // �̺�Ʈ 1ȸ�� ���尡��

	// �̵� ���
	int isMovable;
	int nextStageIdx;
	// player position
	COORD playerPosIdx;

	int stageCnt[MAP_MAX_X];

	// �� ����
	RoomType** Map;
	
public:
	MapSceneManager();
	~MapSceneManager();

	void inputKey();

	void drawMapLevel();

	void drawMapScene();

	void initMapSetting();

	string getRoomTypeName(RoomType type);
	RoomType setRandomRoomType();
	void initMap();
	void setRoomType();

	void drawMap();
	void drawStage(int curX, int curY, int size, RoomType room);
	void drawMapAsset();

	void initPlayerPos();
	void drawPlayerPos();
	void deletePlayerPos();
	void drawNextPlayerPos();
	void deleteNextPlayerPos();

	void drawGameClearScene();
	void drawGoSceneArrow(int idx);
	void deleteGoSceneArrow(int idx);
};

extern MapSceneManager e;