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
			std::cout << name << ": 암살자의 일격을 날립니다.\n" << std::endl;
			target->takeDamage(30);
			return;
		}
	}

	// 30% 이하일때
	bool lowHp = std::any_of(team.begin(), team.end(), [](Character* character)
		{
			return character->isLive() && character->getHp() <= character->getMaxHp() * 0.3;
		});
	if (lowHp)
	{
		auto target = selectTarget(enemy, { "딜러", "제어자", "탱커" });
		if (target)
		{
			std::cout << name << ": 암살자의 일격을 날립니다.\n" << std::endl;
			target->takeDamage(30);
			return;
		}
	}

	if (aliveEnemy >= 2)
	{
		std::cout << name << " : 죽음의 비가 적들을 덮칩니다.\n" << std::endl;
		for (auto& enemys : enemy)
		{
			if (enemys->isLive())
			{
				enemys->takeDamage(10);
			}
		}
		return;
	}

	// 일반 공격
	auto target = selectTarget(enemy, { "딜러", "제어자", "탱커" });
	if (target)
	{
		std::cout << name << "는 " << target->getName() << " 에게 기본공격을 합니다. \n" << std::endl;
		target->takeDamage(Atk);
	}

}
