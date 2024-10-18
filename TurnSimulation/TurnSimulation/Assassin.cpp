#include "Assassin.h"
#include <algorithm>

Assassin::Assassin(std::string name)
	: Dealer(name, 45, 20, 7)
{
}

void Assassin::skills(std::vector<Character*>& team, std::vector<Character*> enemy)
{
	int aliveEnemy = std::count_if(enemy.begin(), enemy.end(), [](Character* character) {return character->isLive(); });
	if (aliveEnemy == 1)
	{
		auto target = enemy.front();
		if (target->isLive())
		{
			std::cout << name << ": �ϻ����� �ϰ��� �����ϴ�.\n" << std::endl;
			target->takeDamage(30);
			return;
		}
	}

	// 30% �����϶�
	bool lowHp = std::any_of(team.begin(), team.end(), [](Character* character)
		{
			return character->isLive() && character->getHp() <= character->getMaxHp() * 0.3;
		});
	if (lowHp)
	{
		auto target = selectTarget(enemy, { "����", "������", "��Ŀ" });
		if (target)
		{
			std::cout << name << ": �ϻ����� �ϰ��� �����ϴ�.\n" << std::endl;
			target->takeDamage(30);
			return;
		}
	}

	if (aliveEnemy >= 2)
	{
		std::cout << name << " : ������ �� ������ ��Ĩ�ϴ�.\n" << std::endl;
		for (auto& enemys : enemy)
		{
			if (enemys->isLive())
			{
				enemys->takeDamage(10);
			}
		}
		return;
	}

	// �Ϲ� ����
	auto target = selectTarget(enemy, { "����", "������", "��Ŀ" });
	if (target)
	{
		std::cout << name << "�� " << target->getName() << " ���� �⺻������ �մϴ�. \n" << std::endl;
		target->takeDamage(Atk);
	}

}
