#include <iostream>
#include <string>
#include <vector>
#include "Character.h"
#include "Item.h"

#include "MainBattle.h"

void Item_Book::Add_Item_in_Book() {		// 이 함수에서 아이템 밸런싱 내용 바꾸기
	Item tmp;

	//패시브
	tmp.Name = "최후의 저항";
	tmp.Description = "체력이 0이면, 체력 1로 생존 (1회)";
	tmp.Cost = 20;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "LR";
	tmp.Index = 0;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "최후의 일격";
	tmp.Description = "상대 체력 20% 이하일 때, 상대방 받는 피해 20% 증가";
	tmp.Cost = 30;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "LB";
	tmp.Index = 1;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "절약의 기술";
	tmp.Description = "아이템 구매 시 10% 할인";
	tmp.Cost = 15;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "TS";
	tmp.Index = 2;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "은행 이자";
	tmp.Description = "스테이지 클리어 시, 현재 보유 골드의 10%를 획득";
	tmp.Cost = 20;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "BI";
	tmp.Index = 3;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "유연함";
	tmp.Description = "자신의 핸드크기를 2 증가시킵니다.";
	tmp.Cost = 20;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "FX";
	tmp.Index = 4;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "스페이드";
	tmp.Description = "스페이드 카드 포함 시 +4";
	tmp.Cost = 10;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "SP";
	tmp.Index = 5;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "다이아몬드";
	tmp.Description = "다이아몬드 카드 포함 시 +3";
	tmp.Cost = 10;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "DM";
	tmp.Index = 6;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "하트";
	tmp.Description = "하트 카드 포함 시 +2";
	tmp.Cost = 10;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "HE";
	tmp.Index = 7;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "클로버";
	tmp.Description = "클로버 카드 포함 시 +1";
	tmp.Cost = 10;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "CL";
	tmp.Index = 8;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "유리대포";
	tmp.Description = "입히는 피해와 입는 피해가 10% 중가";
	tmp.Cost = 10;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "GC";
	tmp.Index = 9;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	//액티브
	tmp.Name = "새로고침";
	tmp.Description = "한 장의 카드를 버리고, 한 장의 카드를 드로우";
	tmp.Cost = 5;
	tmp.Cooltime = 0;
	tmp.isPassive = 0;
	tmp.avi = "RE";
	tmp.Index = 0;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "교환의 장";
	tmp.Description = "핸드를 모두 버리고, 다시 덱에서 카드를 드로우";
	tmp.Cost = 5;
	tmp.Cooltime = 0;
	tmp.avi = "EX";
	tmp.isPassive = 0;
	tmp.Index = 1;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "회복 물약";
	tmp.Description = "체력 20 회복";
	tmp.Cost = 5;
	tmp.Cooltime = 0;
	tmp.isPassive = 0;
	tmp.avi = "HP";
	tmp.Index = 2;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "엇갈린 운명";
	tmp.Description = "동전 앞면이 나오면 +10, 뒷면이 나오면 -10";
	tmp.Cost = 10;
	tmp.Cooltime = 0;
	tmp.isPassive = 0;
	tmp.avi = "MF";
	tmp.Index = 3;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	//직업 스킬
	//늑대인간 패시브
	tmp.Name = "야성의 부름";
	tmp.Description = "쓰러뜨린 적의 수 만큼 자신의 카드 합의 추가한다.";
	tmp.Cost = 0;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.Index = 0;
	JobSkillBook.push_back(tmp);

	//늑대인간 액티브
	tmp.Name = "찢어발기기";
	tmp.Description = "상대방이 낸 카드 중 하나를 무작위로 찢어 무효화 한다. (쿨타임 3턴)";
	tmp.Cost = 0;
	tmp.Cooltime = 3;
	tmp.isPassive = 0;
	tmp.Index = 1;
	JobSkillBook.push_back(tmp);

	//도박사 패시브
	tmp.Name = "사기주사위";
	tmp.Description = "라운드가 끝날 때 10~60의 추가 골드를 획득한다.";
	tmp.Cost = 0;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.Index = 2;
	JobSkillBook.push_back(tmp);

	//도박사 액티브
	tmp.Name = "환전";
	tmp.Description = "보유 골드의 10% 소모하여 소모한 골드만큼 카드 합 증가 (쿨타임 3턴)";
	tmp.Cost = 0;
	tmp.Cooltime = 3;
	tmp.isPassive = 0;
	tmp.Index = 3;
	JobSkillBook.push_back(tmp);

	//도적 패시브
	tmp.Name = "회피기동";
	tmp.Description = "피해 감소 20%";
	tmp.Cost = 0;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.Index = 4;
	JobSkillBook.push_back(tmp);

	//도적 액티브
	tmp.Name = "잠입";
	tmp.Description = "상대방이 낸 카드 2장 중에 무작위 1장의 정보를 획득한다. (쿨타임 2턴)";
	tmp.Cost = 0;
	tmp.Cooltime = 2;
	tmp.isPassive = 0;
	tmp.Index = 5;
	JobSkillBook.push_back(tmp);

	//기회주의자 패시브
	tmp.Name = "고지선점";
	tmp.Description = "내 체력 비율이 상대 체력 비율보다 높다면 피해 증가 20%";
	tmp.Cost = 0;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.Index = 6;
	JobSkillBook.push_back(tmp);

	//기회주의자 액티브
	tmp.Name = "새로운기회";
	tmp.Description = "자신의 핸드에서 카드 한장을 버린 뒤 새 카드를 획득한다. (쿨타임 1턴)";
	tmp.Cost = 0;
	tmp.Cooltime = 1;
	tmp.isPassive = 0;
	tmp.Index = 7;
	JobSkillBook.push_back(tmp);

	//디버프
	tmp.Name = "중독";
	tmp.Description = "플레이어가 이동 할 때마다, 3의 데미지를 입음";
	tmp.Index = 0;
	DebuffBook.push_back(tmp);

	/*tmp.Name = "소멸";
	tmp.Description = "플레이어가 카드를 제출 할 때마다, 무작위 아이템 하나를 제거";
	tmp.Index = 1;
	DebuffBook.push_back(tmp);*/

	tmp.Name = "탈진";
	tmp.Description = "최종 카드 합 -3";
	tmp.Index = 1;
	DebuffBook.push_back(tmp);

	tmp.Name = "스페이드의 저주";
	tmp.Description = "스페이드 포함 시 카드 합 -5";
	tmp.Index = 2;
	DebuffBook.push_back(tmp);

	tmp.Name = "다이아몬드의 저주";
	tmp.Description = "다이아몬드 포함 시 카드 합 -5";
	tmp.Index = 3;
	DebuffBook.push_back(tmp);

	tmp.Name = "하트의 저주";
	tmp.Description = "하트 포함 시 카드 합 -5";
	tmp.Index = 4;
	DebuffBook.push_back(tmp);

	tmp.Name = "클로버의 저주";
	tmp.Description = "클로버 포함 시 카드 합 -5";
	tmp.Index = 5;
	DebuffBook.push_back(tmp);
}
Item_Book::Item_Book() {
	Add_Item_in_Book();
}