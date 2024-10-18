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
		auto target = selectTarget(enemy, { "딜러", "제어자", "탱커" });
		if (target)
		{
			std::cout << getName() << "는 " << target->getName() << " 에게 기본 공격을 합니다.\n" << std::endl;
			target->takeDamage(Atk);
		}
	}

	// 강인한 방어
	for (auto& enemys : enemy)
	{
		if (enemys->isLive() && enemys->getHp() <= enemys->getMaxHp() * 0.2 && enemys->defenseBuff == 0)
		{
			std::cout << name << " : 강인한 방어로 아군을 보호합니다.\n" << std::endl;
			enemys->defBuff(5, 3);
			return;
		}
	}
	// 전장의 분노
	bool lowHp = std::any_of(team.begin(), team.end(), [](Character* character)
		{
			return character->isLive() && character->getHp() <= character->getMaxHp() * 0.3;
		});
	if (lowHp && !isTaunted)
	{
		std::cout << name << " : 적을 분노하게 하여 공격을 유도합니다.\n" << std::endl;
		takeStatus(StatusEffect::Taunted, 3, 0);
		return;
	}
	// 수호의 의지
	bool allLowHp = std::any_of(team.begin(), team.end(), [](Character* character)
		{
			return character->isLive() && character->getHp() <= character->getMaxHp() * 0.5;
		});
	if (allLowHp)
	{
		std::cout << name << " : 수호의 의지로 팀을 방어합니다.\n" << std::endl;
		for (auto& enemys : enemy)
		{
			if (enemys != this)
			{
				enemys->defBuff(10, 1);
			}
		}
		return;
	}
	// 기본 공격
	auto target = selectTarget(enemy, { "딜러", "제어자", "탱커" });
	if (target)
	{
		std::cout << name << "는 " << target->getName() << " 에게 기본 공격을 합니다.\n" << std::endl;
		target->takeDamage(Atk);
	}
}
