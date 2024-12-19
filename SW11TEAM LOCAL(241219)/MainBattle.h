#ifndef _MAIN_BATTLE_
#define _MAIN_BATTLE_

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct trump
{
	char shape;	// S : Spade, D : Diamond, H : Heart, C : Clover
	int number;	// 1 : Ace, 11 : Jack, 12 : Queen, 13 : King
} trump;

class MainBattle
{
public:
	// Console Variable
	HANDLE hConsoleOut;
	CONSOLE_CURSOR_INFO curCursorInfo;

	int handSize[2];	// 0 : Enemy, 1 : Player
	int cardSum[2];		// 0 : Enemy, 1 : Player
	int damage;

	vector<trump> deck;
	vector<trump> garbage;
	vector<trump> hand[2];		// 0 : Enemy, 1 : Player
	vector<trump> buffer[2];	// 0 : Enemy, 1 : Player

	int curSelect;
	int submitIdx;
	int maxSelect;
	int turn;
	int cooltime;
	int enemyHandInfo;

	int aceBonus;
	int numberBonus;
	int shapeBonus;

	int playerPosX;
	int playerPosY;
	int playerHP_posX;
	int playerHP_posY;
	int enemyPosX;
	int enemyPosY;
	int enemyHP_posX;
	int enemyHP_posY;

	int playerSumX;
	int playerSumY;
	int enemySumX;
	int enemySumY;

	int coinPosX;
	int coinPosY;

	int submitPosX;
	int submitPosY;

	int JQK_flag[3];	// 1 : Jack, 2 : Queen, 3 : King

	int coin;	// 1 : Front, 2 : Back;
	int paidGold;

	/*Initial Function*/
	void start();
	void initSetting();
	void setPosition(int y, int x);
	void keySleep(int n);

	void resetDeck();
	void setGarbage();
	void drawHand(int player);
	void resetBuffer(int player);
	void returnBuffer(int player);

	/*Turn Function*/
	void enemyTurn();
	int playerTurn();
	int itemTurn();
	int skillTurn();
	int endTurn();

	void playerAttack();
	void enemyAttack();

	void enemySmartChoice();
	void enemyRandomChoice();

	void calculateEnemySum();
	void calculatePlayerSum();

	/*��ų, ������, ����� ����*/
	// ������ ����
	void applyPassive00();
	// ������ �ϰ�
	void applyPassive01();
	// ������ ���
	/*void applyPassive02();*/
	// ���� ����
	void applyPassive03();
	// ������
	void applyPassive04();
	// �����̵� ���ʽ�
	void applyPassive05();
	// ���̾Ƹ�� ���ʽ�
	void applyPassive06();
	// ��Ʈ ���ʽ�
	void applyPassive07();
	// Ŭ�ι� ���ʽ�
	void applyPassive08();
	// ��������
	void applyPassive09();

	void applyBossPassive();

	// �ߵ�
	/*void applyDebuff00();*/
	// Ż��
	void applyDebuff01();
	// �����̵��� ����
	void applyDebuff02();
	// ���̾Ƹ���� ����
	void applyDebuff03();
	// ��Ʈ�� ����
	void applyDebuff04();
	// Ŭ�ι��� ����
	void applyDebuff05();

	// ���ΰ�ħ
	void applyActive00();
	// ��ȯ�� ��
	void applyActive01();
	// ȸ�� ����
	void applyActive02();
	// ������ ���
	void applyActive03();

	// �����ΰ� �нú�
	void applySkill00();
	// �����ΰ� ��Ƽ��
	void applySkill01();
	// ���ڻ� �нú�
	void applySkill02();
	// ���ڻ� ��Ƽ��
	void applySkill03();
	// ���� �нú�
	void applySkill04();
	// ���� ��Ƽ��
	void applySkill05();
	// ��ȸ������ �нú�
	void applySkill06();
	// ��ȸ������ ��Ƽ��
	void applySkill07();

	void selectCard();
	
	// �ڵ� ī�� ǥ��
	void showHandSlot();
	// ���� ī�� ǥ��
	void showBufferSlot();
	// ������â ǥ��
	void showActiveSlot();
	// ��ųâ ǥ��
	void showSkillSlot();
	// ���� �����
	void eraseSlot();

	// ������, ��ų ���� �ڽ� �׸���
	void showItemSkillBox();
	// ������, ��ų ���� �ڽ� �����
	void eraseItemSkillBox();
	// ������ ���� ǥ��
	void showItemInfo();
	// ��ų ���� ǥ��
	void showSkillInfo();
	// ������, ��ų ���� �����
	void eraseItemSkillInfo();

	// ��� �ڽ� �׸���
	void showResultBox();
	// ��� �ڽ� �����
	void eraseResultBox();
	// �¸�
	void showResultWin();
	// �й�
	void showResultLose();
	// ��� �����
	void eraseResult();


	void increaseSelection();
	void decreaseSelection();
	void showSelection(int y, int x);
	void deleteSelection(int y, int x);

	void increaseItemSelection(int n);
	void decreaseItemSelection(int n);

	void increaseSkillSelection();
	void decreaseSkillSelection();

	void drawPlayer(int y, int x, int idx);
	void drawPlayerHP(int x, int y);
	void drawEnemy(int x, int y, int idx);
	void drawEnemyHP(int x, int y);

	void showCardSum(int player, int y, int x);
	void showResult(int y, int x);

	void showDeck(int y, int x);
	void showDeckCard(int y, int x, int n);
	void showDeckShape(int y, int x, int n);
	void showDeckNumber(int y, int x, int n);

	void showHand(int player, int y, int x);
	void showHandCard(int player, int y, int x, int idx);
	void showHandShape(int player, int y, int x, int idx);
	void showHandNumber(int player, int y, int x, int idx);

	void showBufferCard(int player, int y, int x, int idx);
	void showBufferShape(int player, int y, int x, int idx);
	void showBufferNumber(int player, int y, int x, int idx);
	void showEnemyBuffer();
};

#endif