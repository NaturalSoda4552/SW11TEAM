#include <iostream>
#include <string>
#include <vector>
#include "Character.h"
#include "Item.h"

#include "MainBattle.h"

void Item_Book::Add_Item_in_Book() {		// �� �Լ����� ������ �뷱�� ���� �ٲٱ�
	Item tmp;

	//�нú�
	tmp.Name = "������ ����";
	tmp.Description = "ü���� 0�̸�, ü�� 1�� ���� (1ȸ)";
	tmp.Cost = 20;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "LR";
	tmp.Index = 0;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "������ �ϰ�";
	tmp.Description = "��� ü�� 20% ������ ��, ���� �޴� ���� 20% ����";
	tmp.Cost = 30;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "LB";
	tmp.Index = 1;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "������ ���";
	tmp.Description = "������ ���� �� 10% ����";
	tmp.Cost = 15;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "TS";
	tmp.Index = 2;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "���� ����";
	tmp.Description = "�������� Ŭ���� ��, ���� ���� ����� 10%�� ȹ��";
	tmp.Cost = 20;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "BI";
	tmp.Index = 3;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "������";
	tmp.Description = "�ڽ��� �ڵ�ũ�⸦ 2 ������ŵ�ϴ�.";
	tmp.Cost = 20;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "FX";
	tmp.Index = 4;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "�����̵�";
	tmp.Description = "�����̵� ī�� ���� �� +4";
	tmp.Cost = 10;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "SP";
	tmp.Index = 5;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "���̾Ƹ��";
	tmp.Description = "���̾Ƹ�� ī�� ���� �� +3";
	tmp.Cost = 10;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "DM";
	tmp.Index = 6;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "��Ʈ";
	tmp.Description = "��Ʈ ī�� ���� �� +2";
	tmp.Cost = 10;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "HE";
	tmp.Index = 7;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "Ŭ�ι�";
	tmp.Description = "Ŭ�ι� ī�� ���� �� +1";
	tmp.Cost = 10;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "CL";
	tmp.Index = 8;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "��������";
	tmp.Description = "������ ���ؿ� �Դ� ���ذ� 10% �߰�";
	tmp.Cost = 10;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.avi = "GC";
	tmp.Index = 9;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	//��Ƽ��
	tmp.Name = "���ΰ�ħ";
	tmp.Description = "�� ���� ī�带 ������, �� ���� ī�带 ��ο�";
	tmp.Cost = 5;
	tmp.Cooltime = 0;
	tmp.isPassive = 0;
	tmp.avi = "RE";
	tmp.Index = 0;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "��ȯ�� ��";
	tmp.Description = "�ڵ带 ��� ������, �ٽ� ������ ī�带 ��ο�";
	tmp.Cost = 5;
	tmp.Cooltime = 0;
	tmp.avi = "EX";
	tmp.isPassive = 0;
	tmp.Index = 1;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "ȸ�� ����";
	tmp.Description = "ü�� 20 ȸ��";
	tmp.Cost = 5;
	tmp.Cooltime = 0;
	tmp.isPassive = 0;
	tmp.avi = "HP";
	tmp.Index = 2;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	tmp.Name = "������ ���";
	tmp.Description = "���� �ո��� ������ +10, �޸��� ������ -10";
	tmp.Cost = 10;
	tmp.Cooltime = 0;
	tmp.isPassive = 0;
	tmp.avi = "MF";
	tmp.Index = 3;
	if (tmp.isPassive) PassiveBook.push_back(tmp);
	else ActiveBook.push_back(tmp);

	//���� ��ų
	//�����ΰ� �нú�
	tmp.Name = "�߼��� �θ�";
	tmp.Description = "�����߸� ���� �� ��ŭ �ڽ��� ī�� ���� �߰��Ѵ�.";
	tmp.Cost = 0;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.Index = 0;
	JobSkillBook.push_back(tmp);

	//�����ΰ� ��Ƽ��
	tmp.Name = "����߱��";
	tmp.Description = "������ �� ī�� �� �ϳ��� �������� ���� ��ȿȭ �Ѵ�. (��Ÿ�� 3��)";
	tmp.Cost = 0;
	tmp.Cooltime = 3;
	tmp.isPassive = 0;
	tmp.Index = 1;
	JobSkillBook.push_back(tmp);

	//���ڻ� �нú�
	tmp.Name = "����ֻ���";
	tmp.Description = "���尡 ���� �� 10~60�� �߰� ��带 ȹ���Ѵ�.";
	tmp.Cost = 0;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.Index = 2;
	JobSkillBook.push_back(tmp);

	//���ڻ� ��Ƽ��
	tmp.Name = "ȯ��";
	tmp.Description = "���� ����� 10% �Ҹ��Ͽ� �Ҹ��� ��常ŭ ī�� �� ���� (��Ÿ�� 3��)";
	tmp.Cost = 0;
	tmp.Cooltime = 3;
	tmp.isPassive = 0;
	tmp.Index = 3;
	JobSkillBook.push_back(tmp);

	//���� �нú�
	tmp.Name = "ȸ�Ǳ⵿";
	tmp.Description = "���� ���� 20%";
	tmp.Cost = 0;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.Index = 4;
	JobSkillBook.push_back(tmp);

	//���� ��Ƽ��
	tmp.Name = "����";
	tmp.Description = "������ �� ī�� 2�� �߿� ������ 1���� ������ ȹ���Ѵ�. (��Ÿ�� 2��)";
	tmp.Cost = 0;
	tmp.Cooltime = 2;
	tmp.isPassive = 0;
	tmp.Index = 5;
	JobSkillBook.push_back(tmp);

	//��ȸ������ �нú�
	tmp.Name = "��������";
	tmp.Description = "�� ü�� ������ ��� ü�� �������� ���ٸ� ���� ���� 20%";
	tmp.Cost = 0;
	tmp.Cooltime = 0;
	tmp.isPassive = 1;
	tmp.Index = 6;
	JobSkillBook.push_back(tmp);

	//��ȸ������ ��Ƽ��
	tmp.Name = "���ο��ȸ";
	tmp.Description = "�ڽ��� �ڵ忡�� ī�� ������ ���� �� �� ī�带 ȹ���Ѵ�. (��Ÿ�� 1��)";
	tmp.Cost = 0;
	tmp.Cooltime = 1;
	tmp.isPassive = 0;
	tmp.Index = 7;
	JobSkillBook.push_back(tmp);

	//�����
	tmp.Name = "�ߵ�";
	tmp.Description = "�÷��̾ �̵� �� ������, 3�� �������� ����";
	tmp.Index = 0;
	DebuffBook.push_back(tmp);

	/*tmp.Name = "�Ҹ�";
	tmp.Description = "�÷��̾ ī�带 ���� �� ������, ������ ������ �ϳ��� ����";
	tmp.Index = 1;
	DebuffBook.push_back(tmp);*/

	tmp.Name = "Ż��";
	tmp.Description = "���� ī�� �� -3";
	tmp.Index = 1;
	DebuffBook.push_back(tmp);

	tmp.Name = "�����̵��� ����";
	tmp.Description = "�����̵� ���� �� ī�� �� -5";
	tmp.Index = 2;
	DebuffBook.push_back(tmp);

	tmp.Name = "���̾Ƹ���� ����";
	tmp.Description = "���̾Ƹ�� ���� �� ī�� �� -5";
	tmp.Index = 3;
	DebuffBook.push_back(tmp);

	tmp.Name = "��Ʈ�� ����";
	tmp.Description = "��Ʈ ���� �� ī�� �� -5";
	tmp.Index = 4;
	DebuffBook.push_back(tmp);

	tmp.Name = "Ŭ�ι��� ����";
	tmp.Description = "Ŭ�ι� ���� �� ī�� �� -5";
	tmp.Index = 5;
	DebuffBook.push_back(tmp);
}
Item_Book::Item_Book() {
	Add_Item_in_Book();
}