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


// 메인 화면
class MainSceneManager {
public:
	int main_key;

	int selectedMenuIdx;
	int menuArrow_X;
	int menuArrow_Y;

public:
	MainSceneManager();
	~MainSceneManager();

	/*void gotoPos(int x, int y);
	void drawOutLine();*/

	void inputKey();

	void drawStartScene();
	void drawGameName();
	void drawGameMenu();
	void drawSelectArrow();

	void drawMapLevel();
};
