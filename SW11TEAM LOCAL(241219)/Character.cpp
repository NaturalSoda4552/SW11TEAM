#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "Character.h"
#include "Item.h"
#include "Data.h"

Player p;
Enemy enemy;
Enemy boss1, boss2, boss3, boss4, boss5;

const int size_factor = 3;
const int Width = 16 * size_factor, Height = 9 * size_factor;
const char JobName[4][50] = { {"늑대인간"}, {"도박사"}, {"도적"}, {"기회주의자"} };

void Player::Player_Set_Cursor_Position(int x, int y) {
    COORD pos = { x,y };
    HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOut, pos);
}

void Player::Player_Hide_Cursor() {
    HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(hConsoleOut, &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(hConsoleOut, &curInfo);
}

void Player::Player_Show_Cursor() {
    HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(hConsoleOut, &curInfo);
    curInfo.bVisible = 1;
    SetConsoleCursorInfo(hConsoleOut, &curInfo);
}

void Player::Player_Draw_Stage() {
    int x = 0, y = 0;

    for (y = 0; y <= Height; y++) {
        Player_Set_Cursor_Position(2 * x, y);
        printf("│");
    }
    x = Width;
    for (y = 0; y <= Height; y++) {
        Player_Set_Cursor_Position(2 * x, y);
        printf("│");
    }
    y = 0;
    for (x = 0; x <= 2 * Width; x++) {
        Player_Set_Cursor_Position(x, y);
        printf("─");
    }
    y = Height;
    for (x = 0; x <= 2 * Width; x++) {
        Player_Set_Cursor_Position(x, y);
        printf("─");
    }
    Player_Set_Cursor_Position(0, 0); printf("┌");
    Player_Set_Cursor_Position(2 * Width, 0); printf("┐");
    Player_Set_Cursor_Position(0, Height); printf("└");
    Player_Set_Cursor_Position(2 * Width, Height); printf("┘");
}

void Player::Player_Draw_Info_Stage() {

    for (int a = 8; a <= 94; a++) {
        for (int b = 4; b <= 22; b++) {
            Player_Set_Cursor_Position(a, b);
            printf(" ");
        }
    }
    int x = 4, y = 4;
    
    for (y = 4; y <= 22; y++) {
        Player_Set_Cursor_Position(2 * x, y);
        printf("│");
    }
    x = 47;
    for (y = 4; y <= 22; y++) {
        Player_Set_Cursor_Position(2 * x, y);
        printf("│");
    }
    y = 4;
    for (x = 8; x <= 94; x++) {
        Player_Set_Cursor_Position(x, y);
        printf("─");
    }
    y = 22;
    for (x = 8; x <= 94; x++) {
        Player_Set_Cursor_Position(x, y);
        printf("─");
    }
    Player_Set_Cursor_Position(4 * 2, 4); printf("┌");
    Player_Set_Cursor_Position(47 * 2, 4); printf("┐");
    Player_Set_Cursor_Position(4 * 2, 22); printf("└");
    Player_Set_Cursor_Position(47 * 2, 22); printf("┘");

    x = 4; y = 6;
    for (x = 8; x <= 94; x++) {
        Player_Set_Cursor_Position(x, y);
        printf("─");
    }
    x = 14;
    for (y = 4; y <= 22; y++) {
        Player_Set_Cursor_Position(2 * x, y);
        printf("│");
    }
    x = 24;
    for (y = 4; y <= 22; y++) {
        Player_Set_Cursor_Position(2 * x, y);
        printf("│");
    }
    x = 34;
    for (y = 4; y <= 22; y++) {
        Player_Set_Cursor_Position(2 * x, y);
        printf("│");
    }

    Player_Set_Cursor_Position(14 * 2, 4); printf("┬");
    Player_Set_Cursor_Position(24 * 2, 4); printf("┬");
    Player_Set_Cursor_Position(34 * 2, 4); printf("┬");

    Player_Set_Cursor_Position(14 * 2, 6); printf("┼");
    Player_Set_Cursor_Position(24 * 2, 6); printf("┼");
    Player_Set_Cursor_Position(34 * 2, 6); printf("┼");

    Player_Set_Cursor_Position(14 * 2, 22); printf("┴");
    Player_Set_Cursor_Position(24 * 2, 22); printf("┴");
    Player_Set_Cursor_Position(34 * 2, 22); printf("┴");

    Player_Set_Cursor_Position(4 * 2, 6); printf("├");
    Player_Set_Cursor_Position(47 * 2, 6); printf("┤");
}

void Player::Init_Player_Info() {
    HP = 100;
    maxHP = 100;
    Gold = 0;
    HandSize = 5;
    Move = 0;
    Defeat = 0;
    Score = 0;

    // 매니저 0으로 초기화
    for (int i = 0; i < S.PassiveBook.size(); i++) {
        PassiveManager[i] = 0;
    }
    for (int i = 0; i < S.ActiveBook.size(); i++) {
        ActiveManager[i] = 0;
    }
    for (int i = 0; i < S.DebuffBook.size(); i++) {
        DebuffManager[i] = 0;
    }
    p.PassiveInventory.clear();
    p.ActiveInventory.clear();
    p.DebuffInventory.clear();


// 디버그용
    /*
    * HP = 1;
    Gold = 200;
    ShowInfo = false;
    Name = "TEMP";
    PassiveInventory.push_back(S.PassiveBook[0]);
    PassiveManager[0] += 1;
    PassiveInventory.push_back(S.PassiveBook[1]);
    PassiveManager[1] += 1;

    ActiveInventory.push_back(S.ActiveBook[0]);
    ActiveManager[0] += 1;
    ActiveInventory.push_back(S.ActiveBook[0]);
    ActiveManager[0] += 1;
    ActiveInventory.push_back(S.ActiveBook[1]);
    ActiveManager[1] += 1;
    ActiveInventory.push_back(S.ActiveBook[1]);
    ActiveManager[1] += 1;
    ActiveInventory.push_back(S.ActiveBook[2]);
    ActiveManager[2] += 1;
    ActiveInventory.push_back(S.ActiveBook[2]);
    ActiveManager[2] += 1;
    ActiveInventory.push_back(S.ActiveBook[3]);
    ActiveManager[3] += 1;
    ActiveInventory.push_back(S.ActiveBook[3]);
    ActiveManager[3] += 1;

    DebuffInventory.push_back(S.DebuffBook[0]);
    DebuffManager[0]++;
    DebuffInventory.push_back(S.DebuffBook[1]);
    DebuffManager[1]++;
    */
    
}


void Player::Get_Player_Name() {

    // 스테이지 중앙 좌표 계산
    int centerX = Width;
    int centerY = Height / 2;

    Player_Set_Cursor_Position(centerX - 25, centerY);
    cout << "Enter your name (max 10 characters):";
    Player_Show_Cursor();

    char c;
    Name.clear();

    // 10자 이하 입력 받기
    while (1) {
        c = _getch();  // 실시간으로 입력 받음

        if (c == '\b') {
            if (!Name.empty()) {
                Name.pop_back();  // 문자열에서 마지막 문자 제거
                // 커서 이동 및 출력 제거
                cout << "\b \b";
            }
        }
        // 엔터 입력 시 종료
        else if (c == '\r') {
            break;
        }
        // 최대 길이를 초과하지 않은 경우 문자 추가
        else if (Name.length() < 10) {
            Name += c;
            cout << c;  // 입력된 문자 출력
        }
    }

    Player_Hide_Cursor();

    Player_Set_Cursor_Position(centerX - 25, centerY);
    cout << string(Name.length() + 36, ' ');
}
void Player::Get_Player_Job() {
    _Draw_();
    // 직업 목록 표시
    Player_Set_Cursor_Position(45, 10);
    cout << "Choice your Job!";

    Player_Set_Cursor_Position(10, 13);
    cout << JobName[0];
    Player_Set_Cursor_Position(10, 14);
    cout << JobName[1];
    Player_Set_Cursor_Position(10, 15);
    cout << JobName[2];
    Player_Set_Cursor_Position(10, 16);
    cout << JobName[3];

    int key;
    int currentIndex = 0;
    bool isSelection = false;
    Player_Set_Cursor_Position(7, 13);
    cout << "▶";
    Player_Set_Cursor_Position(23, 13);
    cout << "패시브 :" << S.JobSkillBook[currentIndex * 2].Description;
    Player_Set_Cursor_Position(23, 16);
    cout << "액티브 :" << S.JobSkillBook[currentIndex * 2 + 1].Description;

    while (!isSelection) {
        key = _getch();
        switch (key) {
        case 72: // 위 방향키
            if (currentIndex > 0) {
                Player_Set_Cursor_Position(7, 13 + currentIndex);
                cout << "  ";
                for (int x = 23; x <= 99; x++) {
                    for (int y = 13; y <= 16; y++) {
                        Player_Set_Cursor_Position(x, y);
                        printf(" ");
                    }
                }
                currentIndex--;
                Player_Set_Cursor_Position(7, 13 + currentIndex);
                cout << "▶";
                Player_Set_Cursor_Position(23, 13);
                cout << "패시브 :" << S.JobSkillBook[currentIndex * 2].Description;
                Player_Set_Cursor_Position(23, 16);
                cout << "액티브 :" << S.JobSkillBook[currentIndex * 2 + 1].Description;
            }
            break;
        case 80: // 아래 방향키
            if (currentIndex < 3) {
                Player_Set_Cursor_Position(7, 13 + currentIndex);
                cout << "  ";
                for (int x = 23; x <= 99; x++) {
                    for (int y = 13; y <= 16; y++) {
                        Player_Set_Cursor_Position(x, y);
                        printf(" ");
                    }
                }
                currentIndex++;
                Player_Set_Cursor_Position(7, 13 + currentIndex);
                cout << "▶";
                Player_Set_Cursor_Position(23, 13);
                cout << "패시브 :" << S.JobSkillBook[currentIndex * 2].Description;
                Player_Set_Cursor_Position(23, 16);
                cout << "액티브 :" << S.JobSkillBook[currentIndex * 2 + 1].Description;
            }
            break;
        case 32: // 스페이스바
            isSelection = true;
            break;
        }
    }
    JobIndex = currentIndex;

    JobPassive = S.JobSkillBook[JobIndex * 2];
    JobActive = S.JobSkillBook[JobIndex * 2 + 1];
}


void Player::_Draw_() {
    int x = 21, y = 12;

    for (y = 12; y <= 18; y++) {
        Player_Set_Cursor_Position(x, y);
        printf("│");
    }
    x = 100;
    for (y = 12; y <= 18; y++) {
        Player_Set_Cursor_Position(x, y);
        printf("│");
    }
    y = 12;
    for (x = 21; x <= 100; x++) {
        Player_Set_Cursor_Position(x, y);
        printf("─");
    }
    y = 18;
    for (x = 21; x <= 100; x++) {
        Player_Set_Cursor_Position(x, y);
        printf("─");
    }
    Player_Set_Cursor_Position(21, 12); printf("┌");
    Player_Set_Cursor_Position(100, 12); printf("┐");
    Player_Set_Cursor_Position(21, 18); printf("└");
    Player_Set_Cursor_Position(100, 18); printf("┘");
}

void Player::Show_Player_Info() {
    // 강준 - 수정 
    ShowInfo = true;
    Player_Draw_Info_Stage();

    int startX = 5;  // 왼쪽 테두리에서 2칸 여백
    int startY = 5;  // 상단 테두리에서 5칸 여백


    // 플레이어 정보 표시
    Player_Set_Cursor_Position(startX * 2, startY);
    cout << "Player Status";

    Player_Set_Cursor_Position(startX * 2, startY + 2);
    cout << "Name:" << Name;

    Player_Set_Cursor_Position(startX * 2, startY + 3);
    cout << "Job:" << JobName[JobIndex];

    Player_Set_Cursor_Position(startX * 2, startY + 4);
    cout << "-P:" << JobPassive.Name;

    Player_Set_Cursor_Position(startX * 2, startY + 5);
    cout << "-A:" << JobActive.Name;

    Player_Set_Cursor_Position(startX * 2, startY + 6);
    cout << "HP:" << HP;

    Player_Set_Cursor_Position(startX * 2, startY + 7);
    cout << "Gold:" << Gold;

    Player_Set_Cursor_Position(startX * 2, startY + 8);
    cout << "Hand Size:" << HandSize + p.PassiveManager[4] * 2;

    Player_Set_Cursor_Position(startX * 2, startY + 9);
    cout << "Moves:" << Move;

    Player_Set_Cursor_Position(startX * 2, startY + 10);
    cout << "Defeats:" << Defeat;

    Player_Set_Cursor_Position(startX * 2, startY + 11);
    cout << "Score:" << Score;


    //passive 출력
    startX = 15; startY = 5;
    Player_Set_Cursor_Position(startX * 2, startY);
    cout << "Passive";
    startY += 2;
    for (int i = 0; i < S.PassiveBook.size(); i++) {
        Player_Set_Cursor_Position(startX * 2, startY);
        cout << S.PassiveBook[i].Name << " x " << p.PassiveManager[i];
        startY++;
    }

    //avtive 출력
    startX = 25; startY = 5;
    Player_Set_Cursor_Position(startX * 2, startY);
    cout << "Active";
    startY += 2;
    for (int i = 0; i < S.ActiveBook.size(); i++) {
        Player_Set_Cursor_Position(startX * 2, startY);
        cout << S.ActiveBook[i].Name << " x " << p.ActiveManager[i];
        startY++;
    }
    
    //debuff 출력
    startX = 35; startY = 5;
    Player_Set_Cursor_Position(startX * 2, startY);
    cout << "Debuff";
    startY += 2;
    for (int i = 0; i < S.DebuffBook.size(); i++) {
        Player_Set_Cursor_Position(startX * 2, startY);
        cout << S.DebuffBook[i].Name << " x " << p.DebuffManager[i];
        startY++;
    }

    
    int x = 0, y = 2;
    output_in_tab(x, y, 1);
    int previous_x = 0, previous_y = 1;
    int max_y0, max_y1, max_y2, max_y3;
    max_y0 = 3;
    max_y1 = S.PassiveBook.size() - 1;
    max_y2 = S.ActiveBook.size() - 1;
    max_y3 = S.DebuffBook.size() - 1;
    bool tmp = false;

    while (1) {
        if (_kbhit()) {
            int key = _getch();

            switch (key) {
            case 9:
                p.Hide_Player_Info();
                return;
                break;

            case 32: // 스페이스 바
                p.Hide_Player_Info();
                if (tmp) {
                    tmp = false;
                    return;
                }
                else {
                    tmp = true;
                    p.show_description_in_tap(x, y);
                }
                
                break;

            case 224:
                if (tmp) break;
                key = _getch(); 
                switch (key) {
                case 72: // 윗 방향키
                    if (x == 0 && y == 2) break;
                    if (x != 0 && y == 0) break;
                    previous_x = x;
                    previous_y = y;
                    y--;
                    output_in_tab(previous_x, previous_y, 0);
                    output_in_tab(x, y, 1);
                    break;
                case 80: // 아래 방향키
                    if (x == 0 && y == max_y0) break;
                    if (x == 1 && y == max_y1) break;
                    if (x == 2 && y == max_y2) break;
                    if (x == 3 && y == max_y3) break;
                    previous_x = x;
                    previous_y = y;
                    y++;
                    output_in_tab(previous_x, previous_y, 0);
                    output_in_tab(x, y, 1);
                    break;
                case 75: // 왼쪽 방향키
                    if (x == 0) break;
                    previous_x = x;
                    previous_y = y;
                    x--;
                    y = 0;
                    if (x == 0) y = 2;
                    output_in_tab(previous_x, previous_y, 0);
                    output_in_tab(x, y, 1);
                    break;
                case 77: // 오른쪽 방향키
                    if (x == 3) break;
                    previous_x = x;
                    previous_y = y;
                    x++;
                    y = 0;
                    output_in_tab(previous_x, previous_y, 0);
                    output_in_tab(x, y, 1);
                    break;
                }
                break;
            }
        }
        Sleep(10);
    }
}
void Player::Hide_Player_Info() {
    ShowInfo = false;

    int startY = 4;
    int endY = 22;

    for (int y = startY; y <= endY; y++) {
        Player_Set_Cursor_Position(4 * 2, y);
        cout << string(88, ' ');
    }
}

void Player::output_in_tab(int x, int y, int flag) {
    if (x == 0) {
        if (y ==2)
            x = 13 + JobPassive.Name.length();
        else
            x = 13 + JobActive.Name.length();
    }
    else if (x == 1) {
        x = 30 + S.PassiveBook[y].Name.length() + 4;
    }
    else if (x == 2) {
        x = 50 + S.ActiveBook[y].Name.length() + 4;
    }
    else {
        x = 70 + S.DebuffBook[y].Name.length() + 4;
    }
    Player_Set_Cursor_Position(x + 1, 7 + y);
    if (flag) cout << "◀";
    else cout << "  ";
}

void Player::show_description_in_tap(int x, int y) {
    int x1 = 4, y1 = 4;

    for (y1 = 4; y1 <= 22; y1++) {
        Player_Set_Cursor_Position(2 * x1, y1);
        printf("│");
    }
    x1 = 44;
    for (y1 = 4; y1 <= 22; y1++) {
        Player_Set_Cursor_Position(2 * x1, y1);
        printf("│");
    }
    y1 = 4;
    for (x1 = 8; x1 <= 88; x1++) {
        Player_Set_Cursor_Position(x1, y1);
        printf("─");
    }
    y1 = 22;
    for (x1 = 8; x1 <= 88; x1++) {
        Player_Set_Cursor_Position(x1, y1);
        printf("─");
    }
    Player_Set_Cursor_Position(4 * 2, 4); printf("┌");
    Player_Set_Cursor_Position(44 * 2, 4); printf("┐");
    Player_Set_Cursor_Position(4 * 2, 22); printf("└");
    Player_Set_Cursor_Position(44 * 2, 22); printf("┘");

    int tmp;
    if (x == 0) {
        if (y == 2) {
            tmp = 48 - JobPassive.Name.length() / 2;
            Player_Set_Cursor_Position(tmp, 11);
            cout << "<" << JobPassive.Name << ">";
            tmp = 48 - JobPassive.Description.length() / 2;
            Player_Set_Cursor_Position(tmp, 13);
            cout << JobPassive.Description;
        }
        else {
            tmp = 48 - JobActive.Name.length() / 2;
            Player_Set_Cursor_Position(tmp, 11);
            cout << "<" << JobActive.Name << ">";
            tmp = 48 - JobActive.Description.length() / 2;
            Player_Set_Cursor_Position(tmp, 13);
            cout << JobActive.Description;
        }
        
    }
    else if (x == 1) {
        tmp = 48 - S.PassiveBook[y].Name.length() / 2;
        Player_Set_Cursor_Position(tmp, 11);
        cout << "<" << S.PassiveBook[y].Name << ">";
        tmp = 48 - S.PassiveBook[y].Description.length() / 2;
        Player_Set_Cursor_Position(tmp, 13);
        cout << S.PassiveBook[y].Description;
    }
    else if (x ==2) {
        tmp = 48 - S.ActiveBook[y].Name.length() / 2;
        Player_Set_Cursor_Position(tmp, 11);
        cout << "<" << S.ActiveBook[y].Name << ">";
        tmp = 48 - S.ActiveBook[y].Description.length() / 2;
        Player_Set_Cursor_Position(tmp, 13);
        cout << S.ActiveBook[y].Description;
    }
    else {
        tmp = 48 - S.DebuffBook[y].Name.length() / 2;
        Player_Set_Cursor_Position(tmp, 11);
        cout << "<" << S.DebuffBook[y].Name << ">";
        tmp = 48 - S.DebuffBook[y].Description.length() / 2;
        Player_Set_Cursor_Position(tmp, 13);
        cout << S.DebuffBook[y].Description;
    }
}

void Player::Acquire_Random_Item() { 
    int flag = rand() % 2, idx;

    if (flag) {     //flag가 1이면 패시브를 획득
        idx = rand() % S.PassiveBook.size();
        PassiveInventory.push_back(S.PassiveBook[idx]);
        PassiveManager[idx]++;
    }
    else {      //아니면 액티브룰 획득
        idx = rand() % S.ActiveBook.size();
        ActiveInventory.push_back(S.ActiveBook[idx]);
        ActiveManager[idx]++;
    }
}

void Player::Acquire_Random_Debuff() {
    int idx = rand() % S.DebuffBook.size();
    DebuffInventory.push_back(S.DebuffBook[idx]);
    DebuffManager[idx]++;
}

void Player::Delete_Item_in_PassiveInventory(Item tmp) {
    for (size_t i = 0; i < PassiveInventory.size(); i++) {
        if (PassiveInventory[i].Index == tmp.Index)
            PassiveInventory.erase(PassiveInventory.begin() + i);
    }
    PassiveManager[tmp.Index]--;
}

void Player::Delete_Item_in_ActiveInventory(int idx) {
    int tmp = ActiveInventory[idx].Index;
    ActiveInventory.erase(ActiveInventory.begin() + idx);
    ActiveManager[tmp]--;
}

void Player::Delete_Debuff_in_Inventory(Item tmp) {
    DebuffManager[tmp.Index]--;
    for (int i = 0; i < DebuffInventory.size(); i++) {
        if (DebuffInventory[i].Index == tmp.Index) {
            DebuffInventory.erase(DebuffInventory.begin() + i);
            break;
        }
    }
}

void Player::Accum_Score(int flag) {
    /*
    flag = 1 -> 적 처치
    flag = 2 -> 보스 처치
    flag = 3 -> 이동
    flag = 4 -> 게임 오버 시 점수 추가
    flag = 5 -> 게임 클리어 시 점수 추가
    */

    if (flag == 1) {
        Score += 100 ;
    }
    else if (flag == 2) {
        Score += 500;
    }
    else if (flag == 3) {
        Score += 50;
    }
    else if (flag == 4) {
        int unused_item = PassiveInventory.size() + ActiveInventory.size();
        int remaining_debuff = DebuffInventory.size();
        Score = Score + (unused_item * 100) - (remaining_debuff * 50) + p.Gold;
    }
    else if (flag == 5) {
        int unused_item = PassiveInventory.size() + ActiveInventory.size();
        int remaining_debuff = DebuffInventory.size();
        Score = Score + (unused_item * 200) - (remaining_debuff * 50) + p.Gold;
    }
}

void Player::Acquire_Gold() {
    int a = rand() % 5 + 5;
    p.Gold = p.Gold + a * MapCount;
}

void Enemy::Init_Basic_Enemy() {
    maxHP = 20 * MapCount;
    HP = 20 * MapCount;
    HandSize = 2 * MapCount;
    isBoss = 0;
}

void Enemy::Init_Boss1() {
    maxHP = 150;
    HP = 150;
    HandSize = 8;
    isBoss = 1;
}

void Enemy::Init_Boss2() {
    maxHP = 200;
    HP = 200;
    HandSize = 10;
    isBoss = 1;
}

void Enemy::Init_Boss3() {
    maxHP = 250;
    HP = 250;
    HandSize = 12;
    isBoss = 1;
}

void Enemy::Init_Boss4() {
    maxHP = 300;
    HP = 300;
    HandSize = 15;
    isBoss = 1;
}

void Enemy::Init_Boss5() {
    maxHP = 400;
    HP = 400;
    HandSize = 20;
    isBoss = 1;
}
