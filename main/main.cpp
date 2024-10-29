#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

HANDLE hConsoleOut;
CONSOLE_CURSOR_INFO curCursorInfo;

void setInitSetting();

void setPosition(int x, int y);

void drawOutline();

int main()
{
	setInitSetting();
	drawOutline();

	while (1)
	{

	}

	setPosition(11, 0);

	printf("test2222222");
	printf("test33");
	printf(" ");

	return 0;
}

void setInitSetting()
{
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
}

void setPosition(int y, int x)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(hConsoleOut, pos);
}

void drawOutline()
{
	setPosition(0, 0);
	printf("¦®");
	setPosition(0, 20);
	printf("¦¯");
	setPosition(10, 0);
	printf("¦±");
	setPosition(10, 20);
	printf("¦°");
	for (int i = 1; i < 10; i++)
	{
		setPosition(i, 0);
		printf("¦­");
		setPosition(i, 20);
		printf("¦­");
	}
	for (int i = 1; i < 20; i++)
	{
		setPosition(0, i);
		printf("¦¬");
		setPosition(10, i);
		printf("¦¬");
	}
	
}
