#include "DarkSorcerer.h"
#include <algorithm>

DarkSorcerer::DarkSorcerer(std::string name)
	: Controller(name, 55, 12, 10)
{
}

void DarkSorcerer::skills(std::vector<Character*>& team, std::vector<Character*> enemy)
{
	// �Ʊ��� ��Ŀ�� ���� ��
	bool tanker = std::any_of(team.begin(), team.end(), [](Character* character)
		{
			return character->isLive() && character->getType() == "��Ŀ";
		});
	if (!tanker)
	{
		auto target = selectTarget(enemy, { "����", "������", "��Ŀ" });
		if (target)
		{
			std::cout << name << " : ����� �ձ��� ���� ������ŵ�ϴ�.\n" << std::endl;
			target->takeStatus(StatusEffect::Stunned, 0, 0);
			return;
		}
	}
	// ü���� 20%������ ���� ���� ��
	for (auto& enemys : enemy)
	{
		if (enemys->isLive() && enemys->getHp() <= enemys->getMaxHp() * 0.2)
		{
			std::cout << name << " : ����� �ձ��� ���� ������ŵ�ϴ�.\n" << std::endl;
			enemys->takeStatus(StatusEffect::Stunned, 0, 0);
			return;
		}
	}
	//����� ����
	int lowHpEnemy = std::count_if(enemy.begin(), enemy.end(), [](Character* character)
		{
			return character->isLive() && character->getHp() <= character->getMaxHp() * 0.5;
		});
	if (lowHpEnemy >= 2)
	{
		std::cout << name << " : ����� ������ ���� ���� ������ ��ȭ��ŵ�ϴ�.\n" << std::endl;
		for (auto& enemys : enemy)
		{
			if (enemys->isLive())
			{
				enemys->Atk = std::max(0, enemys->Atk - 10);
				enemys->Def = std::max(0, enemys->Def - 10);
			}
		}
		return;
	}
	// �Ϲ� ����
	auto target = selectTarget(enemy, { "����", "������", "��Ŀ" });
	if (target)
	{
		std::cout << name << "�� " << target->getName() << " ���� �⺻ ������ �մϴ�.\n" << std::endl;
		target->takeDamage(Atk);
	}
}
