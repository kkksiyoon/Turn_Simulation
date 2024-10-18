#include "BraveGuardian.h"
#include <algorithm>

BraveGuardian::BraveGuardian(std::string name)
	: Tanker(name, 85, 30, 18)
{
}

void BraveGuardian::skills(std::vector<Character*>& team, std::vector<Character*> enemy)
{
	int aliveEnemy = std::count_if(enemy.begin(), enemy.end(), [](Character* character) {return character->isLive(); });
	if (aliveEnemy <= 1)
	{
		auto target = selectTarget(enemy, { "����", "������", "��Ŀ" });
		if (target)
		{
			std::cout << getName() << "�� " << target->getName() << " ���� �⺻ ������ �մϴ�.\n" << std::endl;
			target->takeDamage(Atk);
		}
	}

	// ������ ���
	for (auto& enemys : enemy)
	{
		if (enemys->isLive() && enemys->getHp() <= enemys->getMaxHp() * 0.2 && enemys->defenseBuff == 0)
		{
			std::cout << name << " : ������ ���� �Ʊ��� ��ȣ�մϴ�.\n" << std::endl;
			enemys->defBuff(5, 3);
			return;
		}
	}
	// ������ �г�
	bool lowHp = std::any_of(team.begin(), team.end(), [](Character* character)
		{
			return character->isLive() && character->getHp() <= character->getMaxHp() * 0.3;
		});
	if (lowHp && !isTaunted)
	{
		std::cout << name << " : ���� �г��ϰ� �Ͽ� ������ �����մϴ�.\n" << std::endl;
		takeStatus(StatusEffect::Taunted, 3, 0);
		return;
	}
	// ��ȣ�� ����
	bool allLowHp = std::any_of(team.begin(), team.end(), [](Character* character)
		{
			return character->isLive() && character->getHp() <= character->getMaxHp() * 0.5;
		});
	if (allLowHp)
	{
		std::cout << name << " : ��ȣ�� ������ ���� ����մϴ�.\n" << std::endl;
		for (auto& enemys : enemy)
		{
			if (enemys != this)
			{
				enemys->defBuff(10, 1);
			}
		}
		return;
	}
	// �⺻ ����
	auto target = selectTarget(enemy, { "����", "������", "��Ŀ" });
	if (target)
	{
		std::cout << name << "�� " << target->getName() << " ���� �⺻ ������ �մϴ�.\n" << std::endl;
		target->takeDamage(Atk);
	}
}
