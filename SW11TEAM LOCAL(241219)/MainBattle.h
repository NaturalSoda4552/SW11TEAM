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

	/*스킬, 아이템, 디버프 적용*/
	// 최후의 저항
	void applyPassive00();
	// 최후의 일격
	void applyPassive01();
	// 절약의 기술
	/*void applyPassive02();*/
	// 은행 이자
	void applyPassive03();
	// 유연함
	void applyPassive04();
	// 스페이드 보너스
	void applyPassive05();
	// 다이아몬드 보너스
	void applyPassive06();
	// 하트 보너스
	void applyPassive07();
	// 클로버 보너스
	void applyPassive08();
	// 유리대포
	void applyPassive09();

	void applyBossPassive();

	// 중독
	/*void applyDebuff00();*/
	// 탈진
	void applyDebuff01();
	// 스페이드의 저주
	void applyDebuff02();
	// 다이아몬드의 저주
	void applyDebuff03();
	// 하트의 저주
	void applyDebuff04();
	// 클로버의 저주
	void applyDebuff05();

	// 새로고침
	void applyActive00();
	// 교환의 장
	void applyActive01();
	// 회복 물약
	void applyActive02();
	// 엇갈린 운명
	void applyActive03();

	// 늑대인간 패시브
	void applySkill00();
	// 늑대인간 액티브
	void applySkill01();
	// 도박사 패시브
	void applySkill02();
	// 도박사 액티브
	void applySkill03();
	// 도적 패시브
	void applySkill04();
	// 도적 액티브
	void applySkill05();
	// 기회주의자 패시브
	void applySkill06();
	// 기회주의자 액티브
	void applySkill07();

	void selectCard();
	
	// 핸드 카드 표시
	void showHandSlot();
	// 선택 카드 표시
	void showBufferSlot();
	// 아이템창 표시
	void showActiveSlot();
	// 스킬창 표시
	void showSkillSlot();
	// 슬롯 지우기
	void eraseSlot();

	// 아이템, 스킬 정보 박스 그리기
	void showItemSkillBox();
	// 아이템, 스킬 정보 박스 지우기
	void eraseItemSkillBox();
	// 아이템 정보 표시
	void showItemInfo();
	// 스킬 정보 표시
	void showSkillInfo();
	// 아이템, 스킬 정보 지우기
	void eraseItemSkillInfo();

	// 결과 박스 그리기
	void showResultBox();
	// 결과 박스 지우기
	void eraseResultBox();
	// 승리
	void showResultWin();
	// 패배
	void showResultLose();
	// 결과 지우기
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