
#include "Data.h"

void disableCursor() {
    HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO curCursorInfo;
    GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
    curCursorInfo.bVisible = 0;
    SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
}
void gotoPos(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void drawOutLine() {
    gotoPos(0, 0);  printf("┌");
    gotoPos(MAP_OUTLINE_X, 0);  printf("┐");
    gotoPos(0, MAP_OUTLINE_Y);  printf("└");
    gotoPos(MAP_OUTLINE_X, MAP_OUTLINE_Y);  printf("┘");
    for (int i = 1; i < MAP_OUTLINE_X; i++) {
        gotoPos(i, 0); printf("─");
        gotoPos(i, MAP_OUTLINE_Y); printf("─");
    }
    for (int i = 1; i < MAP_OUTLINE_Y; i++) {
        gotoPos(0, i); printf("│");
        gotoPos(MAP_OUTLINE_X, i); printf("│");
    }
}
void drawSquare(int startX, int startY, int dx, int dy) {
    // 콘솔에서 x좌표를 2배로 계산
    int adjustedX = startX * 2;

    // 그릴 사각형 내부 다 지우기
    for (int i = adjustedX + 1; i < adjustedX + dx * 2; i++) {
        for (int j = startY + 1; j < startY + dy; j++) {
            gotoPos(i, j); printf(" ");
        }
    }


    // 테두리 그리기
    gotoPos(adjustedX, startY); printf("┌");
    gotoPos(adjustedX + dx * 2, startY); printf("┐");

    gotoPos(adjustedX, startY + dy); printf("└");
    gotoPos(adjustedX + dx * 2, startY + dy); printf("┘");

    // 상단과 하단 선
    for (int i = adjustedX + 1; i < adjustedX + dx * 2; i++) {
        gotoPos(i, startY); printf("─");
        gotoPos(i, startY + dy); printf("─");
    }

    // 왼쪽과 오른쪽 선
    for (int i = startY + 1; i < startY + dy; i++) {
        gotoPos(adjustedX, i); printf("│");
        gotoPos(adjustedX + dx * 2, i); printf("│");
    }

}
void deleteScene() {
    // 화면 다 지우기 (나중에 애니메이션도 추가)
    for (int i = 1; i < MAP_OUTLINE_X; i++) {
        for (int j = 1; j < MAP_OUTLINE_Y; j++) {
            gotoPos(i, j); printf(" ");
        }
    }
}