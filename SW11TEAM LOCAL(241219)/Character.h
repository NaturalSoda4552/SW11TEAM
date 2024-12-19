#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
using namespace std;


class Character {
public:
    string Name;
    int HP;
    int maxHP;
    int HandSize;
};

class Player : public Character {
public:
    int Gold;
    int Move;
    int Defeat;
    int JobIndex;
    int PassiveManager[10];
    int ActiveManager[4];
    int DebuffManager[6];
    int Score;

    bool ShowInfo; // 디버그용? 아무튼 내가 추가
  
    vector<Item> PassiveInventory;
    vector<Item> ActiveInventory;
    vector<Item> DebuffInventory;
    Item JobPassive, JobActive;

    void Player_Set_Cursor_Position(int x, int y);
    void Player_Hide_Cursor();
    void Player_Show_Cursor();
    void Player_Draw_Stage();
    void Player_Draw_Info_Stage();

    void Init_Player_Info();       //플레이어 정보를 초기화하는 함수
    void Get_Player_Name();        //이름을 입력받는 함수
    void Get_Player_Job();         //직업을 선택하는 함수
    void _Draw_();

    void Show_Player_Info();       //플레이어 정보창을 출력하는 함수
    void Hide_Player_Info();       //플레이어 정보창을 지우는 함수
    void output_in_tab(int x, int y, int flag);       //정보창이 열려있을 때 별 또는 공백을 출력하는 함수
    void show_description_in_tap(int x, int y);

    void Acquire_Random_Item();     //임의의 아이템을 획득하는 함수 (테스트 용)
    void Acquire_Random_Debuff();   //임의의 디버프를 획득하는 험수 (이벤트 활용)
    void Delete_Item_in_PassiveInventory(Item tmp);      //패시브 아이템을 인벤토리에서 삭제하는 함수
    void Delete_Item_in_ActiveInventory(int idx);        //액티브 아이템을 인벤토리에서 삭제하는 함수
    void Delete_Debuff_in_Inventory(Item tmp);      //디버프를 인벤토리에서 삭제하는 함수

    // flag = 1 -> 적 처치
    // flag = 2->보스 처치
    // flag = 3->이동
    // flag = 4->게임 오버 시 점수 추가
    // flag = 5->게임 클리어 시 점수 
    void Accum_Score(int flag);     //점수 누적 함수
    void Acquire_Gold();        //골드 획득 함수

    /*
    필요한 함수 목록
    
    아이템을 인벤토리에 추가하는 함수
    정보창을 열었을 때 보유한 아이템의 효과를 확인하는 함수
    */
};

class Enemy : public Character {
public : 
    int isBoss;
    vector<Item> Gimmick;

    void Init_Basic_Enemy();
    void Init_Boss1();
    void Init_Boss2();
    void Init_Boss3();
    void Init_Boss4();
    void Init_Boss5();
};

extern Player p;
extern Enemy enemy;
extern Enemy boss1, boss2, boss3, boss4, boss5;