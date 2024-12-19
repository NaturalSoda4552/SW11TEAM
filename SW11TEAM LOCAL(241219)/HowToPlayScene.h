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
class HTPSceneManager {
public:
	int htp_key = 0;
	int htp_sceneIdx;

public:
	HTPSceneManager();
	~HTPSceneManager();

	/*void gotoPos(int x, int y);
	void drawOutLine();*/

	void inputKey();

	void drawHtpScene();

};
