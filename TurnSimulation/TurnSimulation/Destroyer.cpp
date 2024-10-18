#include "Destroyer.h"
#include <algorithm>

Destroyer::Destroyer(std::string name)
	: Dealer(name, 45, 20, 7)
{
}

void Destroyer::skills(std::vector<Character*>& team, std::vector<Character*> enemy)
{
	auto target = selectTarget(enemy, { "딜러", "제어자", "탱커" });

	// 일격 필살 : 선택한 적에게 큰 피해를 입힘
	if (target && target->getHp() <= target->getHp() * 0.3)
	{
		std::cout << name << " : 치명적인 일격을 가합니다.\n" << std::endl;
		target->takeDamage(25);
	}

	int aliveEnemy = std::count_if(enemy.begin(), enemy.end(), [](Character* character) {return character->isLive(); });
	if (aliveEnemy >= 2)
	{
		std::cout << name << " :  모든 적에게 대폭발을 일으킵니다.\n " << std::endl;

		for (auto& enemys : enemy)
		{
			if (enemys->isLive())
			{
				enemys->takeDamage(15);
			}
		}

		return;
	}

	// 일반 공격
	if (target)
	{
		std::cout << name << "는 " << target->getName() << " 에게 기본 공격을 합니다.\n" << std::endl;
		target->takeDamage(Atk);
	}
}
