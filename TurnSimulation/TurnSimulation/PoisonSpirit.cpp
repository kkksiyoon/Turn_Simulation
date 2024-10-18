#include "PoisonSpirit.h"
#include <algorithm>

PoisonSpirit::PoisonSpirit(std::string name)
	: Controller(name, 60, 10, 9)
{
}

void PoisonSpirit::skills(std::vector<Character*>& team, std::vector<Character*> enemy)
{
	// �� ��Ŀ�� ü���� 50% �̻��� �� �� ��Ŀ���� ���
	for (auto& enemys : enemy)
	{
		if (enemys->isLive() && enemys->getType() == "��Ŀ" && enemys->getMaxHp() * 0.5 && enemys->getStatus() != StatusEffect::Poisoned)
		{
			std::cout << name << " : ������ �ձ��� ���� 3�ϵ��� �ߵ���ŵ�ϴ�. \n" << std::endl;
			enemys->takeStatus(StatusEffect::Poisoned, 3, 5);
			return;
		}
	}

	// ü���� 30% ������ ���� ���� �� 
	for (auto& enemys : enemy)
	{
		if (enemys->isLive() && enemys->getHp() <= enemys->getMaxHp() * 0.3 && enemys->getStatus() != StatusEffect::Poisoned)
		{
			std::cout << name << " : ������ �ձ��� ���� 3�ϵ��� �ߵ� ��ŵ�ϴ�. \n" << std::endl;
			enemys->takeStatus(StatusEffect::Poisoned, 3, 5);
			return;
		}
	}

	// ���� ��ǳ
	int lowHpEnemy = std::count_if(enemy.begin(), enemy.end(), [](Character* character)
		{
			return character->isLive() && character->getHp() <= character->getMaxHp() * 0.5;
		});
	bool poisonAtk = std::any_of(enemy.begin(), enemy.end(), [](Character* character)
		{
			return character->isLive() && character->getStatus() == StatusEffect::Poisoned;
		});
	if (lowHpEnemy >= 2 && !poisonAtk)
	{
		std::cout << name << " : ���� ��ǳ�� ������ 3�ϵ��� �۾��� ���ϴ�.\n" << std::endl;
		for (auto& enemys : enemy)
		{
			if (enemys->isLive())
			{
				enemys->takeStatus(StatusEffect::Poisoned, 3, 5);
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
