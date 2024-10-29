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

void resetDeck();
void drawRandomCard();

int flagSPADE[13];
int flagCLOVER[13];
int flagHEART[13];
int flagDIAMOND[13];

int countSPADE;
int countCLOVER;
int countHEART;
int countDIAMOND;

typedef struct trump
{

} trump;
int main()
{
	setInitSetting();
	drawOutline();

	resetDeck();

	while (1)
	{

	}

	setPosition(11, 0);

	return 0;
}

void setInitSetting()
{
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	srand(time(0));
}
void setPosition(int y, int x)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(hConsoleOut, pos);
}
void drawOutline()
{
	setPosition(0, 0);
	printf("┌");
	setPosition(0, 20);
	printf("┐");
	setPosition(10, 0);
	printf("└");
	setPosition(10, 20);
	printf("┘");
	for (int i = 1; i < 10; i++)
	{
		setPosition(i, 0);
		printf("│");
		setPosition(i, 20);
		printf("│");
	}
	for (int i = 1; i < 20; i++)
	{
		setPosition(0, i);
		printf("─");
		setPosition(10, i);
		printf("─");
	}
	
}

void resetDeck()
{
	for (int i = 0; i < 52; i++)
	{
		flagSPADE[i] = 1;
		flagCLOVER[i] = 1;
		flagHEART[i] = 1;
		flagDIAMOND[i] = 1;
	}
	countSPADE = 13;
	countCLOVER = 13;
	countHEART = 13;
	countDIAMOND = 13;
}
void drawRandomCard()
{
	int r = (float)rand() / RAND_MAX * countSPADE;
	for (int i = 0; i < r; i++)
	{
		if (flagSPADE[i] = 0)
		{
			i--;
			continue;
		}
	}
}