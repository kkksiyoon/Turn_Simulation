#include "ShieldWarrior.h"
#include <algorithm>

ShieldWarrior::ShieldWarrior(std::string name)
	: Tanker(name, 90, 15, 20)
{
}

void ShieldWarrior::skills(std::vector<Character*>& team, std::vector<Character*> enemy)
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

	// ��ȭ ��� ��ų
	bool buffActive = defenseBuff > 0;
	bool lowHp = false;
	Character* targetCharacter = nullptr;
	for (auto& teams : team)
	{
		if (teams->isLive() && teams->getHp() <= teams->getMaxHp() * 0.5)
		{
			lowHp = true;
			if (teams->defenseBuff == 0)
			{
				targetCharacter = teams;
				break;
			}
		}
	}
	if ((Hp < maxHp * 0.5 || lowHp) && !buffActive)
	{
		if (targetCharacter)
		{
			std::cout << name << " : ��ȭ�� ���� ���� ������ ���Ƴ��ϴ�.\n" << std::endl;
			targetCharacter->defBuff(10, 2);
		}
		else
		{
			std::cout << name << ": ��ȭ�� ���� ���� ������ ���Ƴ��ϴ�.\n" << std::endl;
			defBuff(10, 2);
		}
		return;
	}
	// ȸ���� ����
	if (Hp <= maxHp * 0.3)
	{
		std::cout << name << " : ȸ���� ���з� �����θ� ġ���մϴ�.\n" << std::endl;
		heal(20);
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
