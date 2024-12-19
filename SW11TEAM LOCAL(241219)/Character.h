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

    bool ShowInfo; // ����׿�? �ƹ�ư ���� �߰�
  
    vector<Item> PassiveInventory;
    vector<Item> ActiveInventory;
    vector<Item> DebuffInventory;
    Item JobPassive, JobActive;

    void Player_Set_Cursor_Position(int x, int y);
    void Player_Hide_Cursor();
    void Player_Show_Cursor();
    void Player_Draw_Stage();
    void Player_Draw_Info_Stage();

    void Init_Player_Info();       //�÷��̾� ������ �ʱ�ȭ�ϴ� �Լ�
    void Get_Player_Name();        //�̸��� �Է¹޴� �Լ�
    void Get_Player_Job();         //������ �����ϴ� �Լ�
    void _Draw_();

    void Show_Player_Info();       //�÷��̾� ����â�� ����ϴ� �Լ�
    void Hide_Player_Info();       //�÷��̾� ����â�� ����� �Լ�
    void output_in_tab(int x, int y, int flag);       //����â�� �������� �� �� �Ǵ� ������ ����ϴ� �Լ�
    void show_description_in_tap(int x, int y);

    void Acquire_Random_Item();     //������ �������� ȹ���ϴ� �Լ� (�׽�Ʈ ��)
    void Acquire_Random_Debuff();   //������ ������� ȹ���ϴ� ��� (�̺�Ʈ Ȱ��)
    void Delete_Item_in_PassiveInventory(Item tmp);      //�нú� �������� �κ��丮���� �����ϴ� �Լ�
    void Delete_Item_in_ActiveInventory(int idx);        //��Ƽ�� �������� �κ��丮���� �����ϴ� �Լ�
    void Delete_Debuff_in_Inventory(Item tmp);      //������� �κ��丮���� �����ϴ� �Լ�

    // flag = 1 -> �� óġ
    // flag = 2->���� óġ
    // flag = 3->�̵�
    // flag = 4->���� ���� �� ���� �߰�
    // flag = 5->���� Ŭ���� �� ���� 
    void Accum_Score(int flag);     //���� ���� �Լ�
    void Acquire_Gold();        //��� ȹ�� �Լ�

    /*
    �ʿ��� �Լ� ���
    
    �������� �κ��丮�� �߰��ϴ� �Լ�
    ����â�� ������ �� ������ �������� ȿ���� Ȯ���ϴ� �Լ�
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