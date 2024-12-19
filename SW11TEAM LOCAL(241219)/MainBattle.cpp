#include "MainBattle.h"
#include "Data.h"
#include "Character.h"
#include "Entity.h"
#include "math.h"

void MainBattle::start()
{
	initSetting();

	setGarbage();
	resetDeck();

	drawHand(0);
	drawHand(1);

	drawPlayer(playerPosY, playerPosX, 0);
	drawPlayerHP(playerHP_posY, playerHP_posX);

	drawEnemy(enemyPosY, enemyPosX, 0);
	drawEnemyHP(enemyHP_posY, enemyHP_posX);

	calculatePlayerSum();
	showCardSum(1, 28, 80);

	setPosition(24, 2);
	printf("TURN:%02d", turn);
}
void MainBattle::initSetting()
{
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);

	srand(time(0));

	hand[0].clear();
	hand[1].clear();
	buffer[0].clear();
	buffer[1].clear();
	deck.clear();
	garbage.clear();

	handSize[0] = enemy.HandSize;
	applyPassive04();
	cardSum[0] = 0;
	cardSum[1] = 0;

	aceBonus = 50;
	numberBonus = 15;
	shapeBonus = 5;

	curSelect = 0;
	turn = 1;
	cooltime = 0;
	enemyHandInfo = 1;
	
	playerPosX = 26;
	playerPosY = 17;
	playerHP_posX = 10;
	playerHP_posY = 19;
	
	enemyPosX = 70;
	enemyPosY = 3;
	enemyHP_posX = 82;
	enemyHP_posY = 5;

	playerSumX = 40;
	playerSumY = 16;
	enemySumX = 60;
	enemySumY = 10;

	coinPosX = 50;
	coinPosY = 13;

	submitPosX = 90;
	submitPosY = 22;

	JQK_flag[0] = 0;
	JQK_flag[1] = 0;
	JQK_flag[2] = 0;

	damage = 0;
	coin = 0;
	paidGold = 0;

	// Debug
//	enemy.HP = 1;
//	p.HP = 1;
}
void MainBattle::setPosition(int y, int x)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(hConsoleOut, pos);
}
void MainBattle::keySleep(int n)
{
	for (int i = 0; i < n / 10; i++)
	{
		int key = 0;
		if (_kbhit() != 0)
		{
			key = _getch();
			if (key == 224)
				key = _getch();
		}
		Sleep(10);
	}
}

void MainBattle::resetDeck()
{
	int size = garbage.size();
	for (int i = 0; i < size; i++)
	{
		deck.push_back(garbage.back());
		garbage.pop_back();
	}
	for (int i = 0; i < deck.size(); i++)
	{
		int r = rand() * deck.size() / (RAND_MAX + 1);
		trump tmp = deck[i];
		deck[i] = deck[r];
		deck[r] = tmp;
	}
}
void MainBattle::setGarbage()
{
	garbage.clear();
	trump card;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			int n = 13 * i + j;
			switch (i)
			{
			case 0: card.shape = 'S'; break;
			case 1: card.shape = 'D'; break;
			case 2: card.shape = 'H'; break;
			case 3: card.shape = 'C'; break;
			default: break;
			}
			card.number = j + 1;
			garbage.push_back(card);
		}
	}
}
void MainBattle::drawHand(int player)
{
	/*while (!(Hand[player].empty()))
	{
		garbage.push_back(Hand[player].back());
		Hand[player].pop_back();
	}*/
	while (hand[player].size() < handSize[player])
	{
		if (deck.empty())
			resetDeck();
		hand[player].push_back(deck.back());
		deck.pop_back();
	}

	/*while (!(Hand[player].empty()))
	{
		garbage.push_back(Hand[player].back());
		Hand[player].pop_back();
	}
	if (HAND_SIZE[player] > deck.size())
		resetDeck();
	for (int i = 0; i < HAND_SIZE[player]; i++)
	{
		Hand[player].push_back(deck.back());
		deck.pop_back();
	}*/
}
void MainBattle::resetBuffer(int player)
{
	while (!(buffer[player].empty()))
	{
		garbage.push_back(buffer[player].back());
		buffer[player].pop_back();
	}
}
void MainBattle::returnBuffer(int player)
{
	while (!buffer[player].empty())
	{
		hand[player].push_back(buffer[player].back());
		buffer[player].pop_back();
	}
}

void MainBattle::enemyTurn()
{
	resetBuffer(0);

	int R = (float)rand() / (RAND_MAX + 1) * 5;

	buffer[0].clear();
	buffer[0].push_back(hand[0][0]);
	hand[0].erase(hand[0].begin());

	if (R < MapCount)
		enemySmartChoice();
	else
		enemyRandomChoice();
}
int MainBattle::playerTurn()
{
	curSelect = 0;
	submitIdx = hand[1].size();
	maxSelect = hand[1].size();
	showSelection(24, 30 + curSelect * 4);

	calculatePlayerSum();
	showCardSum(1, 28, 80);

	setPosition(submitPosY, submitPosX + 2);
	printf("[SUBMIT]");

	while (1)
	{
		int key = 0;
		if (_kbhit() != 0)
		{
			key = _getch();
			if (key == 224)
				key = _getch();
		}

		switch (key)
		{
		// ESC
		case 27:
			deleteSelection(24, 30 + curSelect * 4);
			deleteSelection(24, 92 + (curSelect - hand[1].size()) * 4);
			deleteSelection(submitPosY, submitPosX);
			setPosition(submitPosY, submitPosX + 2);
			printf("        ");
			returnBuffer(1);
			showHandSlot();
			return 1;
			break;

		// Space
		case 32:
			// 2장 선택 후 제출
			if (buffer[1].size() == 2 && curSelect == submitIdx)
			{
				deleteSelection(submitPosY, submitPosX);
				setPosition(submitPosY, submitPosX + 2);
				printf("        ");
				return 0;
			}

			// 2장 초과 선택
			else if (buffer[1].size() != 2 && curSelect == submitIdx)
				continue;
			
			// 정상적 카드 선택
			else
			{
				selectCard();
				showHandSlot();
				showBufferSlot();
			}

			calculatePlayerSum();
			showCardSum(1, 28, 80);
			break;

		// Up
		case 72:
			break;

		// Left
		case 75:
			decreaseSelection();
			break;

		// Right
		case 77:
			increaseSelection();
			break;

		// Down
		case 80:
			break;

		default:
			break;
		}
	}

	return 0;
}
int MainBattle::itemTurn()
{
	curSelect = 0;
	submitIdx = p.ActiveInventory.size();
	maxSelect = p.ActiveInventory.size();
	showActiveSlot();

	if (curSelect == maxSelect)
		showSelection(30, 88);
	else
	{
		showSelection(24, 30);
		showItemSkillBox();
		showItemInfo();
	}

	while (1)
	{
		int key = 0;
		if (_kbhit() != 0)
		{
			key = _getch();
			if (key == 224)
				key = _getch();
		}

		switch (key)
		{
		// ESC
		/*case 27:
			deleteSelection(24, 30 + curSelect * 14);
			showHandSlot();
			return 1;
			break;*/

		// Space
		case 32:
			deleteSelection(24, 30 + (curSelect % 5) * 14);
			eraseItemSkillBox();
			if (curSelect >= maxSelect)
			{
				deleteSelection(30, 88);
				showHandSlot();
				return 1;
			}
			else if (p.ActiveInventory[curSelect].Index == 0)	// 새로고침 : 한장 교체
			{
				p.Delete_Item_in_ActiveInventory(curSelect);
				showActiveSlot();
				applyActive00();
			}
			else if (p.ActiveInventory[curSelect].Index == 1)	// 교환의 장 : 핸드 전체 교체
			{
				p.Delete_Item_in_ActiveInventory(curSelect);
				showActiveSlot();
				applyActive01();
			}
			else if (p.ActiveInventory[curSelect].Index == 2)	// 회복 물약 : HP 20 회복
			{
				p.Delete_Item_in_ActiveInventory(curSelect);
				showActiveSlot();
				applyActive02();
			}

			else if (p.ActiveInventory[curSelect].Index == 3)	// 엇갈린 운명 : 동전 앞면 = +10, 뒷면 = -10;
			{
				p.Delete_Item_in_ActiveInventory(curSelect);
				showActiveSlot();
				applyActive03();
			}
			showHandSlot();
			return 0;
			break;

		// Up
		case 72:
			decreaseItemSelection(5);
			break;

		// Left
		case 75:
			decreaseItemSelection(1);
			break;

		// Right
		case 77:
			increaseItemSelection(1);
			break;

		// Down
		case 80:
			increaseItemSelection(5);
			break;

		default:
			break;
		}
	}
	return 0;
}
int MainBattle::skillTurn()
{
	curSelect = 0;
	submitIdx = 0;
	maxSelect = 1;

	showSkillSlot();
	showItemSkillBox();
	showSkillInfo();
	showSelection(29, 54);
	
	while (1)
	{
		int key = 0;
		if (_kbhit() != 0)
		{
			key = _getch();
			if (key == 224)
				key = _getch();
		}

		switch (key)
		{
		// ESC
		/*case 27:
			return 1;
			break;*/

		// Space
		case 32:
			eraseItemSkillBox();
			if (curSelect == 1)
				return 1;
			if (curSelect == 0)
			{
				if (cooltime > 0)
				{
					eraseSlot();
					setPosition(28, 50);
					printf("%d턴 후에 사용 가능합니다.", cooltime);
					keySleep(1000);

					return 1;
				}
				switch (p.JobIndex)
				{
				case 0: applySkill01(); break;
				case 1: applySkill03(); break;
				case 2: applySkill05(); break;
				case 3: applySkill07(); break;
				default: break;
				}
			}
			return 0;

		// Left
		case 75:
			decreaseSkillSelection();
			break;

		// Right
		case 77:
			increaseSkillSelection();
			break;

		default:
			break;
		}
	}
	return 0;
}
int MainBattle::endTurn()
{
	damage = 0;

	calculatePlayerSum();
	calculateEnemySum();

	setPosition(playerSumY, playerSumX);
	printf("%d", cardSum[1]);
	keySleep(700);

	setPosition(enemySumY, enemySumX);
	printf("%d", cardSum[0]);
	keySleep(1000);

	setPosition(playerSumY, playerSumX);
	printf("  ");
	setPosition(enemySumY, enemySumX);
	printf("  ");

	// 상대 승
	if (cardSum[0] > cardSum[1])
		enemyAttack();

	// 플레이어 승
	else if (cardSum[1] > cardSum[0])
		playerAttack();

	// 엇갈린 운명 효과 초기화
	coin = 0;
	paidGold = 0;
	enemyHandInfo = 1;

	// Reset Buffer
	resetBuffer(0);
	resetBuffer(1);

	// Draw Hand
	if (hand[0].size() < 2)
		drawHand(0);
	if (hand[1].size() < 2)
		drawHand(1);

	// 최후의 저항
	applyPassive00();

	// 은행 이자
	applyPassive03();

	// Win
	if (enemy.HP <= 0)
	{
		p.Defeat += 1;

		showResultBox();
		showResultWin();

		// 도박사 패시브
		applySkill02();

		keySleep(2000);
		return 1;
	}

	// Lose
	if (p.HP <= 0)
	{
		showResultBox();
		showResultLose();

		keySleep(2000);
		return -1;
	}

	turn += 1;
	if (cooltime > 0)
		cooltime -= 1;

	setPosition(24, 2);
	printf("TURN:%02d", turn);

	return 0;
}

void MainBattle::playerAttack()
{
	damage = cardSum[1] - cardSum[0];

	if (JQK_flag[0] == 1)
	{
		p.Gold += 10 + damage;
	}
	if (JQK_flag[1] == 1)
	{
		p.HP += damage;
		if (p.HP > p.maxHP)
			p.HP = p.maxHP;
	}
	if (JQK_flag[2] == 1)
	{
		damage *= 2;
	}

	if (damage < 10)
		damage += 10;

	// 유리대포
	applyPassive09();

	// 최후의 일격
	applyPassive01();

	// 기회주의자 패시브
	applySkill06();

	// 엇갈린 운명
	if (coin == 1)
		damage += 10;
	else if (coin == 2)
		damage -= 10;

	enemy.HP -= damage;

	setPosition(enemyPosY + 3, enemyPosX + 22);
	SetConsoleTextAttribute(hConsoleOut, 4);
	printf("%d", -damage);
	SetConsoleTextAttribute(hConsoleOut, 7);

	drawPlayer(playerPosY, playerPosX, 1);
	drawPlayerHP(playerPosY + 2, playerPosX - 16);

	SetConsoleTextAttribute(hConsoleOut, 4);
	drawEnemy(enemyPosY, enemyPosX, 0);
	drawEnemyHP(enemyPosY + 2, enemyPosX + 12);
	keySleep(300);
	SetConsoleTextAttribute(hConsoleOut, 7);
	drawEnemy(enemyPosY, enemyPosX, 0);
	drawEnemyHP(enemyPosY + 2, enemyPosX + 12);
	keySleep(300);

	drawPlayer(playerPosY, playerPosX, 0);

	SetConsoleTextAttribute(hConsoleOut, 4);
	drawEnemy(enemyPosY, enemyPosX, 0);
	drawEnemyHP(enemyPosY + 2, enemyPosX + 12);
	keySleep(300);
	SetConsoleTextAttribute(hConsoleOut, 7);
	drawEnemy(enemyPosY, enemyPosX, 0);
	drawEnemyHP(enemyPosY + 2, enemyPosX + 12);
	keySleep(300);

	setPosition(enemyPosY + 3, enemyPosX + 22);
	printf("   ");
	setPosition(enemyPosY + 4, enemyPosX + 20);
	printf("           ");
}
void MainBattle::enemyAttack()
{
	damage = cardSum[0] - cardSum[1];

	if (damage < 10)
		damage += 10;

	// 유리대포
	applyPassive09();

	// 도적 패시브
	applySkill04();

	p.HP -= damage;

	setPosition(playerHP_posY + 1, playerHP_posX + 10);
	SetConsoleTextAttribute(hConsoleOut, 4);
	printf("%d", -damage);
	SetConsoleTextAttribute(hConsoleOut, 7);

	drawEnemy(enemyPosY, enemyPosX, 1);

	SetConsoleTextAttribute(hConsoleOut, 4);
	drawPlayer(playerPosY, playerPosX, 0);
	drawPlayerHP(playerHP_posY, playerHP_posX);
	keySleep(300);
	SetConsoleTextAttribute(hConsoleOut, 7);
	drawPlayer(playerPosY, playerPosX, 0);
	drawPlayerHP(playerHP_posY, playerHP_posX);
	keySleep(300);

	drawEnemy(enemyPosY, enemyPosX, 0);

	SetConsoleTextAttribute(hConsoleOut, 4);
	drawPlayer(playerPosY, playerPosX, 0);
	drawPlayerHP(playerHP_posY, playerHP_posX);
	keySleep(300);
	SetConsoleTextAttribute(hConsoleOut, 7);
	drawPlayer(playerPosY, playerPosX, 0);
	drawPlayerHP(playerHP_posY, playerHP_posX);
	keySleep(300);

	setPosition(playerHP_posY + 1, playerHP_posX + 10);
	printf("   ");
}

void MainBattle::enemySmartChoice()
{
	auto it = hand[0].begin();

	// 같은 숫자 선택
	if (buffer[0].size() < 2)
	{
		while (it != hand[0].end())
		{
			if (buffer[0][0].number == it->number)
			{
				buffer[0].push_back(*it);
				hand[0].erase(it);
				break;
			}
			it++;
		}
	}

	// 같은 모양 선택
	if (buffer[0].size() < 2)
	{
		it = hand[0].begin();
		while (it != hand[0].end())
		{
			if (buffer[0][0].shape == it->shape)
			{
				buffer[0].push_back(*it);
				hand[0].erase(it);
				break;
			}
			it++;
		}
	}

	// 무작위 선택
	if (buffer[0].size() < 2)
	{
		buffer[0].push_back(hand[0][0]);
		hand[0].erase(hand[0].begin());
	}
}
void MainBattle::enemyRandomChoice()
{
	// 무작위 선택
	if (buffer[0].size() < 2)
	{
		buffer[0].push_back(hand[0][0]);
		hand[0].erase(hand[0].begin());
	}
}

void MainBattle::calculateEnemySum()
{
	cardSum[0] = 0;

	for (auto e : buffer[0])
		cardSum[0] += e.number;

	if (buffer[0].size() == 2)
	{
		// Ace
		if (buffer[0][0].number == 1 && buffer[0][1].number == 1)
			cardSum[0] += aceBonus;

		// 같은 숫자
		else if (buffer[0][0].number == buffer[0][1].number)
			cardSum[0] += numberBonus;

		// 같은 문자
		else if (buffer[0][0].shape == buffer[0][1].shape)
			cardSum[0] += shapeBonus;
	}

	// 보스 패시브 적용
	if (enemy.isBoss != 0)
		applyBossPassive();
}
void MainBattle::calculatePlayerSum()
{
	cardSum[1] = paidGold;
	
	for (int i = 0; i < 3; i++)
		JQK_flag[i] = 0;

	for (auto e : buffer[1])
		cardSum[1] += e.number;

	// 스페이드, 다이아몬드, 하트. 클로버 패시브
	applyPassive05();
	applyPassive06();
	applyPassive07();
	applyPassive08();
	
	// 늑대인간 패시브
	applySkill00();

	// 조합 보너스
	if (buffer[1].size() == 2)
	{
		// Ace
		if (buffer[1][0].number == 1 && buffer[1][1].number == 1)
			cardSum[1] += aceBonus;

		// J
		else if (buffer[1][0].number == 11 && buffer[1][1].number == 11)
		{
			JQK_flag[0] = 1;
			cardSum[1] += numberBonus;
		}
		// Q
		else if (buffer[1][0].number == 12 && buffer[1][1].number == 12)
		{
			JQK_flag[1] = 1;
			cardSum[1] += numberBonus;
		}
		// K
		else if (buffer[1][0].number == 13 && buffer[1][1].number == 13)
		{
			JQK_flag[2] = 1;
			cardSum[1] += numberBonus;
		}

		// 같은 숫자
		else if (buffer[1][0].number == buffer[1][1].number)
			cardSum[1] += numberBonus;

		// 같은 모양
		else if (buffer[1][0].shape == buffer[1][1].shape)
			cardSum[1] += shapeBonus;
	}

	// 디버프 적용
	applyDebuff01();
	applyDebuff02();
	applyDebuff03();
	applyDebuff04();
	applyDebuff05();
}

void MainBattle::applyPassive00()
{
	// 체력이 0 이하일 때 1로 생존
	if (p.HP <= 0)
	{
		if (p.PassiveManager[0] >= 1)
		{
			p.HP = 1;
			p.Delete_Item_in_PassiveInventory(S.PassiveBook[0]);

			drawPlayerHP(playerHP_posY, playerHP_posX);
			
			setPosition(playerHP_posY + 2, playerHP_posX);
			SetConsoleTextAttribute(hConsoleOut, 14);
			printf("최후의 저항");
			keySleep(2000);

			setPosition(playerHP_posY + 2, playerHP_posX);
			SetConsoleTextAttribute(hConsoleOut, 7);
			printf("            ");
		}
	}
}
void MainBattle::applyPassive01()
{
	// 상대 체력 20% 이하일 때 데미지 20% 증가
	if (enemy.HP / (float)enemy.maxHP <= 0.2)
	{
		if (p.PassiveManager[1] >= 1)
		{
			damage += damage * p.PassiveManager[1] * 0.2;
			setPosition(enemyHP_posY + 2, enemyHP_posX + 8);
			printf("최후의 일격");
		}
	}
}

void MainBattle::applyPassive03()
{
	// 승리 시 골드 + 10%
	if (enemy.HP <= 0)
		if (p.PassiveManager[3] >= 1)
			p.Gold += p.PassiveManager[3] * p.Gold / 10;
}
void MainBattle::applyPassive04()
{
	// 핸드 사이즈 +2
	handSize[1] = p.HandSize;
	if (p.PassiveManager[4] >= 1)
		handSize[1] += 2 * p.PassiveManager[4];
}
void MainBattle::applyPassive05()
{
	// 스페이드 포함 시 +4
	if (p.PassiveManager[5] >= 1)
		for (auto e : buffer[1])
			if (e.shape == 'S')
			{
				cardSum[1] += p.PassiveManager[5] * 4;
				return;
			}
}
void MainBattle::applyPassive06()
{
	// 다이아몬드 포함 시 +3
	if (p.PassiveManager[6] >= 1)
		for (auto e : buffer[1])
			if (e.shape == 'D')
			{
				cardSum[1] += p.PassiveManager[6] * 3;
				return;
			}
}
void MainBattle::applyPassive07()
{
	// 하트 포함 시 +2
	if (p.PassiveManager[7] >= 1)
		for (auto e : buffer[1])
			if (e.shape == 'H')
			{
				cardSum[1] += p.PassiveManager[7] * 2;
				return;
			}
}
void MainBattle::applyPassive08()
{
	// 클로버 포함 시 +1
	if (p.PassiveManager[8] >= 1)
		for (auto e : buffer[1])
			if (e.shape == 'C')
			{
				cardSum[1] += p.PassiveManager[8] * 1;
				return;
			}
}
void MainBattle::applyPassive09()
{
	// 받는 데미지, 주는 데미지 +10%
	if (p.PassiveManager[9] >= 1)
		damage += p.PassiveManager[9] * damage / 10;
}

void MainBattle::applyBossPassive()
{
	if (MapCount == 1)
		for (int i = 0; i < buffer[0].size(); i++)
			if (buffer[0][i].shape == 'C')
			{
				cardSum[0] += 3;
				return;
			}
	if (MapCount == 2)
		for (int i = 0; i < buffer[0].size(); i++)
			if (buffer[0][i].shape == 'H')
			{
				cardSum[0] += 5;
				return;
			}
	if (MapCount == 3)
		for (int i = 0; i < buffer[0].size(); i++)
			if (buffer[0][i].shape == 'D')
			{
				cardSum[0] += 7;
				return;
			}
	if (MapCount == 4)
		for (int i = 0; i < buffer[0].size(); i++)
			if (buffer[0][i].shape == 'S')
			{
				cardSum[0] += 10;
				return;
			}
}

void MainBattle::applyDebuff01()
{
	// 카드 합 -3
	if (p.DebuffManager[1] >= 1)
		cardSum[1] -= p.DebuffManager[1] * 3;
}
void MainBattle::applyDebuff02()
{
	// 스페이드 포함 시 카드 합 -5
	if (p.DebuffManager[2] >= 1)
		for (int i = 0; i < buffer[1].size(); i++)
			if (buffer[1][i].shape == 'S')
			{
				cardSum[1] -= p.DebuffManager[2] * 5;
				return;
			}
}
void MainBattle::applyDebuff03()
{
	// 다이아몬드 포함 시 카드 합 -5
	if (p.DebuffManager[3] >= 1)
		for (int i = 0; i < buffer[1].size(); i++)
			if (buffer[1][i].shape == 'D')
			{
				cardSum[1] -= p.DebuffManager[3] * 5;
				return;
			}
}
void MainBattle::applyDebuff04()
{
	// 하트 포함 시 카드 합 -5
	if (p.DebuffManager[4] >= 1)
		for (int i = 0; i < buffer[1].size(); i++)
			if (buffer[1][i].shape == 'H')
			{
				cardSum[1] -= p.DebuffManager[4] * 5;
				return;
			}
}
void MainBattle::applyDebuff05()
{
	// 클로버 포함 시 카드 합 -5
	if (p.DebuffManager[5] >= 1)
		for (int i = 0; i < buffer[1].size(); i++)
			if (buffer[1][i].shape == 'C')
			{
				cardSum[1] -= p.DebuffManager[5] * 5;
				return;
			}
}

void MainBattle::applyActive00()
{
	// 카드 한장 선택 후 교체
	curSelect = 0;
	maxSelect = hand[1].size() - 1;
	submitIdx = hand[1].size();

	showHandSlot();
	showSelection(24, 30 + curSelect * 4);

	while (1)
	{
		int key = 0;
		if (_kbhit() != 0)
		{
			key = _getch();
			if (key == 224)
				key = _getch();
		}

		switch (key)
		{
		// Space
		case 32:
			garbage.push_back(hand[1][curSelect]);
			hand[1].erase(hand[1].begin() + curSelect);
			deleteSelection(24, 30 + curSelect * 4);
			showHandSlot();
			keySleep(500);

			if (deck.empty())
				resetDeck();

			hand[1].push_back(deck.back());
			deck.pop_back();
			showHandSlot();
			keySleep(500);
			return;
		// Left
		case 75: decreaseSelection(); break;
		// Right
		case 77: increaseSelection(); break;
		default: break;
		}
	}

}
void MainBattle::applyActive01()
{
	// 카드 전체 교체
	showHandSlot();
	keySleep(300);
	while (!hand[1].empty())
	{
		garbage.push_back(hand[1].back());
		hand[1].pop_back();
		showHandSlot();
		keySleep(200);
	}
	keySleep(300);
	drawHand(1);
	showHandSlot();
	keySleep(500);
}
void MainBattle::applyActive02()
{
	// 체력 20 회복
	p.HP += 20;
	if (p.HP > p.maxHP)
		p.HP = p.maxHP;

	SetConsoleTextAttribute(hConsoleOut, 10);
	drawPlayer(playerPosY, playerPosX, 0);
	drawPlayerHP(playerHP_posY, playerHP_posX);
	setPosition(playerHP_posY + 1, playerHP_posX + 10);
	printf("+20");
	keySleep(300);

	SetConsoleTextAttribute(hConsoleOut, 7);
	drawPlayer(playerPosY, playerPosX, 0);
	drawPlayerHP(playerHP_posY, playerHP_posX);
	keySleep(300);

	SetConsoleTextAttribute(hConsoleOut, 10);
	drawPlayer(playerPosY, playerPosX, 0);
	drawPlayerHP(playerHP_posY, playerHP_posX);
	keySleep(300);

	SetConsoleTextAttribute(hConsoleOut, 7);
	drawPlayer(playerPosY, playerPosX, 0);
	drawPlayerHP(playerHP_posY, playerHP_posX);
	keySleep(300);

	setPosition(playerHP_posY + 1, playerHP_posX + 10);
	printf("   ");
}
void MainBattle::applyActive03()
{
	// 데미지 +10 or -10;
	coin = (float)rand() / (RAND_MAX + 1) * 2 + 1;

	for (int i = 0; i < 6; i++)
	{
		setPosition(coinPosY, coinPosX);
		printf("앞");
		keySleep(100);
		setPosition(coinPosY, coinPosX);
		printf("뒤");
		keySleep(100);
	}
	for (int i = 0; i < 4; i++)
	{
		setPosition(coinPosY, coinPosX);
		printf("앞");
		keySleep(150);
		setPosition(coinPosY, coinPosX);
		printf("뒤");
		keySleep(150);
	}
	for (int i = 0; i < 2; i++)
	{
		setPosition(coinPosY, coinPosX);
		printf("앞");
		keySleep(300);
		setPosition(coinPosY, coinPosX);
		printf("뒤");
		keySleep(300);
	}
	keySleep(500);
	
	if (coin == 1)
	{
		setPosition(coinPosY, coinPosX);
		printf("앞");
		setPosition(coinPosY + 1, coinPosX - 6);
		printf("주는 피해 +10");
	}
	else
	{
		setPosition(coinPosY, coinPosX);
		printf("뒤");
		setPosition(coinPosY + 1, coinPosX - 6);
		printf("주는 피해 -10");
	}
	keySleep(2000);

	setPosition(coinPosY, coinPosX);
	printf("  ");
	setPosition(coinPosY + 1, coinPosX - 6);
	printf("              ");
}

void MainBattle::applySkill00()
{
	// 승리 수 만큼 합 증가
	if (p.JobIndex == 0)
	{
		cardSum[1] += p.Defeat * 1;
	}
}
void MainBattle::applySkill01()
{
	// 상대 카드 한장 무효화
	cooltime = S.JobSkillBook[2 * p.JobIndex + 1].Cooltime + 1;

	garbage.push_back(buffer[0].back());
	buffer[0].pop_back();

	showEnemyBuffer();
	keySleep(1000);
}
void MainBattle::applySkill02()
{
	// 승리 시 10~60 골드 획득
	if (p.JobIndex == 1)
	{
		int R = (float)rand() / (RAND_MAX + 1) * 6 + 1;

		SetConsoleTextAttribute(hConsoleOut, 14);
		setPosition(15, 34);
		printf("사기주사위");
		SetConsoleTextAttribute(hConsoleOut, 7);

		keySleep(300);

		for (int i = 0; i < 20; i++)
		{
			setPosition(15, 46);
			printf("%d", rand() % 6 + 1);
			keySleep(100);
		}
		setPosition(15, 46);
		printf("%d", R);

		keySleep(500);
		setPosition(15, 50);
		printf("%d 골드 추가 획득", 10 * R);

		keySleep(500);

		p.Gold += 10 * R;
	}
}
void MainBattle::applySkill03()
{
	// 보유 골드 10% 사용하여 카드 합 증가
	cooltime = S.JobSkillBook[2 * p.JobIndex + 1].Cooltime + 1;

	paidGold = p.Gold * 0.1;
	p.Gold -= paidGold;

	setPosition(13, 40);
	printf("보유 골드 : %d (-%d)", p.Gold, paidGold);
	setPosition(14, 40);
	printf("카드 합 %d증가", paidGold);
	keySleep(2000);

	setPosition(13, 40);
	printf("                       ");
	setPosition(14, 40);
	printf("               ");
}
void MainBattle::applySkill04()
{
	// 피해 감소 20%
	if (p.JobIndex == 2)
	{
		damage *= 0.8;
	}
}
void MainBattle::applySkill05()
{
	// 상대 핸드 정보 확인
	cooltime = S.JobSkillBook[2 * p.JobIndex + 1].Cooltime + 1;

	enemyHandInfo = 2;
	showEnemyBuffer();
	keySleep(1000);
}
void MainBattle::applySkill06()
{
	// 플레이어 체력 비율이 상대 체력 비율보다 높을 때 피해 20% 증가
	if (p.JobIndex == 3)
	{
		float playerHP_ratio = (float)p.HP / p.maxHP;
		float enemyHP_ratio = (float)enemy.HP / enemy.maxHP;

		if (playerHP_ratio > enemyHP_ratio)
			damage *= 1.2;
	}
}
void MainBattle::applySkill07()
{
	// 핸드에서 한장 선택하여 교체
	cooltime = S.JobSkillBook[2 * p.JobIndex + 1].Cooltime + 1;

	curSelect = 0;
	maxSelect = hand[1].size() - 1;
	submitIdx = hand[1].size();

	showHandSlot();
	showSelection(24, 30 + curSelect * 4);

	while (1)
	{
		int key = 0;
		if (_kbhit() != 0)
		{
			key = _getch();
			if (key == 224)
				key = _getch();
		}

		switch (key)
		{
		// Space
		case 32:
			garbage.push_back(hand[1][curSelect]);
			hand[1].erase(hand[1].begin() + curSelect);
			deleteSelection(24, 30 + curSelect * 4);
			showHandSlot();
			keySleep(1000);

			if (deck.empty())
				resetDeck();
			hand[1].push_back(deck.back());
			deck.pop_back();
			showHandSlot();
			keySleep(1000);
			return;

		// Left
		case 75: decreaseSelection(); break;
		// Right
		case 77: increaseSelection(); break;
		default: break;
		}
	}

	
}

void MainBattle::selectCard()
{
	if (curSelect >= hand[1].size())
	{
		int bufferIdx = curSelect - hand[1].size();
		if (bufferIdx == 0)
		{
			hand[1].push_back(buffer[1][0]);
			buffer[1].erase(buffer[1].begin());
		}
		else
		{
			hand[1].push_back(buffer[1][1]);
			buffer[1].erase(buffer[1].begin() + 1);
		}
		deleteSelection(24, 92 + (curSelect - hand[1].size() + 1) * 4);
		if (curSelect < hand[1].size())
			showSelection(24, 30 + curSelect * 4);
		else
			showSelection(24, 92 + (curSelect - hand[1].size()) * 4);
	}

	else if (buffer[1].size() >= 2)
		return;
	
	else
	{
		buffer[1].push_back(hand[1][curSelect]);
		hand[1].erase(hand[1].begin() + curSelect);
		if (curSelect >= hand[1].size())
		{
			deleteSelection(24, 30 + curSelect * 4);
			showSelection(24, 92 + (curSelect - hand[1].size()) * 4);
		}
	}
}

void MainBattle::showHandSlot()
{
	int hand_start_X = MAP_OUTLINE_X / 2 / 2 + 1;
	int hand_end_X = MAP_OUTLINE_X - 1;

	int hand_start_Y = MAP_OUTLINE_Y - 7;
	int hand_end_Y = MAP_OUTLINE_Y - 1;

	// 모두 지우기
	for (int i = hand_start_X + 1; i < hand_end_X - 1; i++) {
		for (int j = hand_start_Y + 1; j < hand_end_Y; j++) {
			setPosition(j, i);
			printf(" ");
		}
	}

	for (int i = 0; i < hand[1].size(); i++)
	{
		// each
		setPosition(hand_start_Y + 1, hand_start_X + 2 + i * 4);
		printf("┌");
		setPosition(hand_start_Y + 1, hand_start_X + 3 + i * 4);
		printf("─");
		setPosition(hand_start_Y + 1, hand_start_X + 4 + i * 4);
		printf("─");
		setPosition(hand_start_Y + 1, hand_start_X + 5 + i * 4);
		printf("─");

		for (int j = hand_start_Y + 2; j < hand_end_Y - 1; j++) 
		{
			setPosition(j, hand_start_X + 2 + i * 4);
			printf("│");
		}
		setPosition(hand_end_Y - 1, hand_start_X + 2 + i * 4);
		printf("└");
		setPosition(hand_end_Y - 1, hand_start_X + 3 + i * 4);
		printf("─");
		setPosition(hand_end_Y - 1, hand_start_X + 4 + i * 4);
		printf("─");
		setPosition(hand_end_Y - 1, hand_start_X + 5 + i * 4);
		printf("─");

		// num, shape
		showHandNumber(1, hand_start_Y + 1 + 1, hand_start_X + i * 4 + 4, i);
		showHandShape(1, hand_start_Y + 1 + 2, hand_start_X + i * 4 + 4, i);

		if (i == hand[1].size() - 1)
		{
			setPosition(hand_end_Y - 1, hand_start_X + i * 4 + 8);
			printf("┘");
			setPosition(hand_start_Y + 1, hand_start_X + i * 4 + 8);
			printf("┐");
			setPosition(hand_end_Y - 1, hand_start_X + 7 + i * 4);
			printf("─");
			setPosition(hand_end_Y - 1, hand_start_X + 7 + i * 4 - 1);
			printf("─");
			setPosition(hand_start_Y + 1, hand_start_X + 7 + i * 4);
			printf("─");
			setPosition(hand_start_Y + 1, hand_start_X + 7 + i * 4 - 1);
			printf("─");

			for (int j = hand_start_Y + 2; j < hand_end_Y - 1; j++)
			{
				setPosition(j, hand_start_X + i * 4 + 8);
				printf("│");
			}
		}
	}
}
void MainBattle::showBufferSlot()
{
	int startX = 90;
	int startY = 26;

	for (int i = 0; i <= 4; i++)
		for (int j = 0; j <= 10; j++)
		{
			setPosition(startY + i, startX + j);
			printf(" ");
		}
	for (int i = 0; i < buffer[1].size(); i++)
	{
		setPosition(startY, 4 * i + startX);
		printf("┌");
		setPosition(startY + 4, 4 * i + startX);
		printf("└");
		setPosition(startY, 4 * i + startX + 6);
		printf("┐");
		setPosition(startY + 4, 4 * i + startX + 6);
		printf("┘");
		for (int j = 1; j <= 5; j++)
		{
			setPosition(startY, 4 * i + startX + j);
			printf("─");
			setPosition(startY + 4, 4 * i + startX + j);
			printf("─");
		}
		for (int j = 1; j <= 3; j++)
		{
			setPosition(startY + j, 4 * i + startX);
			printf("│");
			if (i == buffer[1].size() - 1)
			{
				setPosition(startY + j, 4 * i + startX + 6);
				printf("│");
			}
		}

		showBufferNumber(1, startY + 1, 4 * i + startX + 2, i);
		showBufferShape(1, startY + 2, 4 * i + startX + 2, i);
	}
}
void MainBattle::showActiveSlot()
{
	int item_start_X = MAP_OUTLINE_X / 2 / 2 + 1;
	int item_end_X = MAP_OUTLINE_X - 1;

	int item_start_Y = MAP_OUTLINE_Y - 7;
	int item_end_Y = MAP_OUTLINE_Y - 1;

	// 모두 지우기
	for (int i = item_start_X + 1; i < item_end_X - 1; i++) {
		for (int j = item_start_Y + 1; j < item_end_Y; j++) {
			setPosition(j, i);
			printf(" ");
		}
	}

	for (int i = 0; i < p.ActiveInventory.size(); i++)
	{
		setPosition(item_start_Y + 1 + 2 * (i / 5), item_start_X + 2 + (i % 5) * 14);
		cout << p.ActiveInventory[i].Name;
	}

	setPosition(30, 90);
	printf("뒤로 가기");
}
void MainBattle::showSkillSlot()
{
	int skill_start_X = MAP_OUTLINE_X / 2 / 2 + 1;
	int skill_end_X = MAP_OUTLINE_X - 1;

	int skill_start_Y = MAP_OUTLINE_Y - 7;
	int skill_end_Y = MAP_OUTLINE_Y - 1;

	// 모두 지우기
	for (int i = skill_start_X + 1; i < skill_end_X - 1; i++) {
		for (int j = skill_start_Y + 1; j < skill_end_Y; j++) {
			setPosition(j, i);
			printf(" ");
		}
	}
	setPosition(27, 50);
	printf("스킬을 사용하시겠습니까?");
	setPosition(29, 56);
	printf("예");
	setPosition(29, 66);
	printf("아니요");
}
void MainBattle::eraseSlot()
{
	int slot_start_X = MAP_OUTLINE_X / 2 / 2 + 1;
	int slot_end_X = MAP_OUTLINE_X - 1;

	int slot_start_Y = MAP_OUTLINE_Y - 7;
	int slot_end_Y = MAP_OUTLINE_Y - 1;

	// 모두 지우기
	for (int i = slot_start_X + 1; i < slot_end_X - 1; i++) {
		for (int j = slot_start_Y + 1; j < slot_end_Y; j++) {
			setPosition(j, i);
			printf(" ");
		}
	}
}

void MainBattle::showItemSkillBox()
{
	setPosition(18, 40);
	printf("┌");
	setPosition(18, 102);
	printf("┐");
	setPosition(23, 40);
	printf("└");
	setPosition(23, 102);
	printf("┘");
	for (int i = 19; i < 23; i++)
	{
		setPosition(i, 40);
		printf("│");
		setPosition(i, 102);
		printf("│");
	}
	for (int i = 41; i < 102; i++)
	{
		setPosition(18, i);
		printf("─");
		setPosition(23, i);
		printf("─");
	}
}
void MainBattle::eraseItemSkillBox()
{
	for (int i = 18; i <= 23; i++)
		for (int j = 40; j <= 102; j++)
		{
			setPosition(i, j);
			printf(" ");
		}
}
void MainBattle::showItemInfo()
{
	if (curSelect == maxSelect)
		return;
	setPosition(19, 42);
	cout << p.ActiveInventory[curSelect].Name;
	setPosition(20, 42);
	cout << p.ActiveInventory[curSelect].Description;
}
void MainBattle::showSkillInfo()
{
	setPosition(19, 42);
	cout << S.JobSkillBook[2 * p.JobIndex + 1].Name;
	setPosition(20, 42);
	cout << S.JobSkillBook[2 * p.JobIndex + 1].Description.substr(0, S.JobSkillBook[2 * p.JobIndex + 1].Description.size() - 13);
	setPosition(21, 42);
	cout << "쿨타임 : " << S.JobSkillBook[2 * p.JobIndex + 1].Cooltime;
	setPosition(22, 42);
	if (p.JobIndex == 1)
		cout << "보유 골드 : " << p.Gold;
	else
		cout << "남은 쿨타임 : " << cooltime;
}
void MainBattle::eraseItemSkillInfo()
{
	for (int i = 19; i < 23; i++)
		for (int j = 41; j < 102; j++)
		{
			setPosition(i, j);
			printf(" ");
		}
}

void MainBattle::showResultBox()
{
	setPosition(11, 30);
	printf("┌");
	setPosition(11, 70);
	printf("┐");
	setPosition(16, 30);
	printf("└");
	setPosition(16, 70);
	printf("┘");
	for (int i = 12; i < 16; i++)
	{
		setPosition(i, 30);
		printf("│");
		setPosition(i, 70);
		printf("│");
	}
	for (int i = 31; i < 70; i++)
	{
		setPosition(11, i);
		printf("─");
		setPosition(16, i);
		printf("─");
	}
}
void MainBattle::eraseResultBox()
{
	for (int i = 11; i <= 16; i++)
		for (int j = 30; j <= 70; j++)
		{
			setPosition(i, j);
			printf(" ");
		}
}
void MainBattle::showResultWin()
{
	int earnGold = (enemy.isBoss + 1) * MapCount * (rand() % 5 + 5);
	p.Gold += earnGold;
	setPosition(12, 48);
	printf("승리");
	setPosition(14, 40);
	printf("소유 골드 : %d (+%d)", p.Gold, earnGold);
}
void MainBattle::showResultLose()
{
	setPosition(12, 48);
	printf("패배");
	setPosition(14, 40);
	printf("다시 도전해보세요.");
}
void MainBattle::eraseResult()
{
	for (int i = 12; i < 16; i++)
		for (int j = 31; j < 70; j++)
		{
			setPosition(i, j);
			printf(" ");
		}
}

void MainBattle::increaseSelection()
{
	if (curSelect + 1 > maxSelect)
		return;

	if (curSelect >= hand[1].size())
		deleteSelection(24, 92 + (curSelect - hand[1].size()) * 4);
	else
		deleteSelection(24, 30 + curSelect * 4);
	
	curSelect += 1;
	
	if (curSelect == submitIdx)
		showSelection(submitPosY, submitPosX);
	else if (curSelect >= hand[1].size())
		showSelection(24, 92 + (curSelect - hand[1].size()) * 4);
	else
		showSelection(24, 30 + curSelect * 4);
}
void MainBattle::decreaseSelection()
{
	if (curSelect - 1 < 0)
		return;
	
	if (curSelect == submitIdx)
		deleteSelection(submitPosY, submitPosX);
	if (curSelect >= hand[1].size())
		deleteSelection(24, 92 + (curSelect - hand[1].size()) * 4);
	else
		deleteSelection(24, 30 + curSelect * 4);
	
	curSelect -= 1;
	
	if (curSelect >= hand[1].size())
		showSelection(24, 92 + (curSelect - hand[1].size()) * 4);
	else
		showSelection(24, 30 + curSelect * 4);
}
void MainBattle::showSelection(int y, int x)
{
	setPosition(y, x);
	if (curSelect >= submitIdx)
		printf("▶");
	else
		printf("▼");
}
void MainBattle::deleteSelection(int y, int x)
{
	setPosition(y, x);
	printf("  ");
}

void MainBattle::increaseItemSelection(int n)
{
	if (curSelect + 1 > maxSelect)
		return;

	if (curSelect / 5 == 0)
		deleteSelection(24, 30 + (curSelect % 5) * 14);
	else if (curSelect / 5 == 1)
		deleteSelection(27, 30 + (curSelect % 5) * 14);
	else if (curSelect / 5 == 2)
		deleteSelection(29, 30 + (curSelect % 5) * 14);

	curSelect += n;
	if (curSelect > maxSelect)
		curSelect = maxSelect;

	eraseItemSkillInfo();

	if (curSelect == maxSelect)
	{
		showSelection(30, 88);
		eraseItemSkillBox();
	}
	else if (curSelect / 5 == 0)
	{
		showSelection(24, 30 + (curSelect % 5) * 14);
		showItemSkillBox();
		showItemInfo();
	}
	else if (curSelect / 5 == 1)
	{
		showSelection(27, 30 + (curSelect % 5) * 14);
		showItemSkillBox();
		showItemInfo();
	}
	else if (curSelect / 5 == 2)
	{
		showSelection(29, 30 + (curSelect % 5) * 14);
		showItemSkillBox();
		showItemInfo();
	}
}
void MainBattle::decreaseItemSelection(int n)
{
	if (curSelect - n < 0)
		return;
	if (curSelect == maxSelect)
		n = 1;

	if (curSelect == maxSelect)
		deleteSelection(30, 88);
	else if (curSelect / 5 == 0)
		deleteSelection(24, 30 + (curSelect % 5) * 14);
	else if (curSelect / 5 == 1)
		deleteSelection(27, 30 + (curSelect % 5) * 14);
	else if (curSelect / 5 == 2)
		deleteSelection(29, 30 + (curSelect % 5) * 14);

	curSelect -= n;
	if (curSelect < 0)
		curSelect = 0;

	eraseItemSkillInfo();

	if (curSelect / 5 == 0)
		showSelection(24, 30 + (curSelect % 5) * 14);
	else if (curSelect / 5 == 1)
		showSelection(27, 30 + (curSelect % 5) * 14);
	else if (curSelect / 5 == 2)
		showSelection(29, 30 + (curSelect % 5) * 14);

	showItemSkillBox();
	showItemInfo();
}

void MainBattle::increaseSkillSelection()
{
	if (curSelect + 1 > maxSelect)
		return;

	deleteSelection(29, 54);
	curSelect += 1;
	showSelection(29, 64);
}
void MainBattle::decreaseSkillSelection()
{
	if (curSelect - 1 < 0)
		return;

	deleteSelection(29, 64);
	curSelect -= 1;
	showSelection(29, 54);
}

void MainBattle::drawPlayer(int y, int x, int idx)
{
//	SetConsoleTextAttribute(hConsoleOut, 10);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			setPosition(y + i, x + j);
			printf("%c", mobModel[idx][i][j]);
		}
	}
//	SetConsoleTextAttribute(hConsoleOut, 15);
}
void MainBattle::drawPlayerHP(int y, int x)
{
	setPosition(y, x);
	printf("HP");
	int hpRatio = p.HP / (float)p.maxHP * 10;
	for (int i = 0; i < 10; i++)
	{
		setPosition(y, x + 2 + i);
		if (hpRatio >= (i + 1))
			printf("■");
		else if (i == 0 && p.HP > 0)
			printf("■");
		else
			printf("□");
	}
	setPosition(y + 1, x + 2);
	printf("%03d/%03d", p.HP, p.maxHP);
}
void MainBattle::drawEnemy(int y, int x, int idx)
{
	int model = 1;
	if (enemy.isBoss == 1)
		model = MapCount;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			setPosition(y + i, x + j);
			printf("%c", mobModel[2 * model + idx][i][j]);
		}
	}
}
void MainBattle::drawEnemyHP(int y, int x)
{
	setPosition(y, x);
	printf("HP");
	int hpRatio = enemy.HP / (float)enemy.maxHP * 10;
	for (int i = 0; i < 10; i++)
	{
		setPosition(y, x + 2 + i);
		if (hpRatio >= (i + 1))
			printf("■");
		else if (i == 0 && enemy.HP > 0)
			printf("■");
		else
			printf("□");
	}
	setPosition(y + 1, x + 2);
	printf("%03d/%03d", enemy.HP, enemy.maxHP);
}

void MainBattle::showCardSum(int player, int y, int x)
{
	setPosition(y, x);
	printf("SUM:%02d", cardSum[player]);
}
void MainBattle::showResult(int y, int x)
{
	setPosition(y, x);
	printf("          ");
	setPosition(y, x);
	if (cardSum[0] > cardSum[1])
		printf("P1 WIN");
	else if (cardSum[1] > cardSum[0])
		printf("P2 WIN");
	else
		printf("Draw");

	setPosition(y, x + 8);
	printf("%02d", abs(cardSum[0] - cardSum[1]));
}

void MainBattle::showDeck(int y, int x)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			setPosition(y + i, x + 6 * j);
			printf("      ");
		}
	}
	for (int i = 0; i < deck.size(); i++)
	{
		int line = 0;
		showDeckCard(y + i / 13, x + 6 * (i % 13), i);
	}
	/*for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			setPosition(y + i, x + 6 * j);
			printf("      ");
			int n = 13 * i + j;
			showDeckCard(y + i, x + 6 * j, n);
		}
	}*/
}
void MainBattle::showDeckCard(int y, int x, int n)
{
	showDeckShape(y, x, n);
	showDeckNumber(y, x + 2, n);
}
void MainBattle::showDeckShape(int y, int x, int n)
{
	setPosition(y, x);
	switch (deck[n].shape)
	{
	case 'S': printf("♤"); break;
	case 'D': printf("◇"); break;
	case 'H': printf("♡"); break;
	case 'C': printf("♧"); break;
	default: break;
	}
}
void MainBattle::showDeckNumber(int y, int x, int n)
{
	setPosition(y, x);
	switch (deck[n].number)
	{
	case 1: printf("A"); break;
	case 11: printf("J"); break;
	case 12: printf("Q"); break;
	case 13: printf("K"); break;
	default: printf("%d", deck[n].number); break;
	}
}

void MainBattle::showHand(int player, int y, int x)
{
	for (int i = 0; i < handSize[player]; i++)
	{
		setPosition(y + i, x);
		printf("        ");
	}
	for (int i = 0; i < hand[player].size(); i++)
		showHandCard(player, y + i, x, i);
	for (int i = 0; i < buffer[player].size(); i++)
		showBufferCard(player, y + hand[player].size() + i, x, i);

//	setPosition(y + HAND_SIZE[player], x);
//	printf("Submit");
}
void MainBattle::showHandCard(int player, int y, int x, int idx)
{
	for (int i = 0; i < 4; i++)
	{
		setPosition(y, x + i);
		printf(" ");
	}
	showHandShape(player, y, x, idx);
	showHandNumber(player, y, x + 2, idx);

	/*if (hand[player][idx].flagSelected == 1)
	{
		setPosition(5 + idx, 4 + 10 * player);
		printf("＊");
	}*/
}
void MainBattle::showHandShape(int player, int y, int x, int idx)
{
	int C = hand[player][idx].shape;
	setPosition(y, x);
	if (C == 'D' || C == 'H')
		SetConsoleTextAttribute(hConsoleOut, 4);
	else
		SetConsoleTextAttribute(hConsoleOut, 8);
	switch (C)
	{
	case 'S':	printf("♤");	break;
	case 'D':	printf("◇");	break;
	case 'H':	printf("♡");	break;
	case 'C':	printf("♧");	break;
	default:	break;
	}
	SetConsoleTextAttribute(hConsoleOut, 7);
}
void MainBattle::showHandNumber(int player, int y, int x, int idx)
{
	int N = hand[player][idx].number;
	setPosition(y, x);
	switch (N)
	{
	case 1:		printf("A");		break;
	case 11:	printf("J");		break;
	case 12:	printf("Q");		break;
	case 13:	printf("K");		break;
	default:	printf("%d", N);	break;
	}
}

void MainBattle::showBufferCard(int player, int y, int x, int idx)
{
	for (int i = 0; i < 4; i++)
	{
		setPosition(y, x + i);
		printf(" ");
	}
	showBufferShape(player, y, x, idx);
	showBufferNumber(player, y, x + 2, idx);

	setPosition(y, x + 4);
	printf("*");
}
void MainBattle::showBufferShape(int player, int y, int x, int idx)
{
	int C = buffer[player][idx].shape;
	setPosition(y, x);
	if (C == 'D' || C == 'H')
		SetConsoleTextAttribute(hConsoleOut, 4);
	else
		SetConsoleTextAttribute(hConsoleOut, 8);
	switch (C)
	{
	case 'S':	printf("♤");	break;
	case 'D':	printf("◇");	break;
	case 'H':	printf("♡");	break;
	case 'C':	printf("♧");	break;
	default:	break;
	}
	SetConsoleTextAttribute(hConsoleOut, 7);
}
void MainBattle::showBufferNumber(int player, int y, int x, int idx)
{
	int N = buffer[player][idx].number;
	setPosition(y, x);
	switch (N)
	{
	case 1:		printf("A");		break;
	case 11:	printf("J");		break;
	case 12:	printf("Q");		break;
	case 13:	printf("K");		break;
	default:	printf("%d", N);	break;
	}
}
void MainBattle::showEnemyBuffer()
{
	int hand_start_X = 14;

	int hand_start_Y = 5;
	
	// 상대 선택 카드 테두리
	drawSquare(hand_start_X - 1, hand_start_Y - 1, 9, 6);

	for (int i = 0; i < buffer[0].size(); i++) {
		// each
		drawSquare(hand_start_X + i * 4, hand_start_Y, 3, 4);
		// 상대방 카드이므로 일단 안보이게 설정
		// num, shape
	}
	for (int i = 0; i < enemyHandInfo; i++)
	{
		showBufferNumber(0, hand_start_Y + 1, (hand_start_X + i * 4 + 1) * 2, i);
		showBufferShape(0, hand_start_Y + 1 + 1, (hand_start_X + i * 4 + 1) * 2, i);
	}
}