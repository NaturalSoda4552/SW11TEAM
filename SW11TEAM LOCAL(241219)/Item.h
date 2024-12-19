#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "MainBattle.h"


class Enemy;

class Item {
public:
	string Name;
	string Description;
	int Cost;
	int Cooltime;
	int isPassive;
	int Index;

	// ����
	string avi;
};

class Item_Book {
public:
	vector<Item> PassiveBook;
	vector<Item> ActiveBook;
	vector<Item> JobSkillBook;
	vector<Item> DebuffBook;

	// ����
	Item_Book();

	void Add_Item_in_Book();
};

extern Item_Book S;
