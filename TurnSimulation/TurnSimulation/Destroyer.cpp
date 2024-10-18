#include "Destroyer.h"
#include <algorithm>

Destroyer::Destroyer(std::string name)
	: Dealer(name, 45, 20, 7)
{
}

void Destroyer::skills(std::vector<Character*>& team, std::vector<Character*> enemy)
{
	auto target = selectTarget(enemy, { "����", "������", "��Ŀ" });

	// �ϰ� �ʻ� : ������ ������ ū ���ظ� ����
	if (target && target->getHp() <= target->getHp() * 0.3)
	{
		std::cout << name << " : ġ������ �ϰ��� ���մϴ�.\n" << std::endl;
		target->takeDamage(25);
	}

	int aliveEnemy = std::count_if(enemy.begin(), enemy.end(), [](Character* character) {return character->isLive(); });
	if (aliveEnemy >= 2)
	{
		std::cout << name << " :  ��� ������ �������� ����ŵ�ϴ�.\n " << std::endl;

		for (auto& enemys : enemy)
		{
			if (enemys->isLive())
			{
				enemys->takeDamage(15);
			}
		}

		return;
	}

	// �Ϲ� ����
	if (target)
	{
		std::cout << name << "�� " << target->getName() << " ���� �⺻ ������ �մϴ�.\n" << std::endl;
		target->takeDamage(Atk);
	}
}
