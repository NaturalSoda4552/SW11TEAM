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


// 게임 방법 화면
class ScoreSceneManager {
public:
	int score_key = 0;

public:
	ScoreSceneManager();
	~ScoreSceneManager();

	/*void gotoPos(int x, int y);
	void drawOutLine();*/

	void inputKey();

	void drawScoreScene();

};
