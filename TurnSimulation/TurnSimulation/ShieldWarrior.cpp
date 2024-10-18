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
		auto target = selectTarget(enemy, { "딜러", "제어자", "탱커" });
		if (target)
		{
			std::cout << getName() << "는 " << target->getName() << " 에게 기본 공격을 합니다.\n" << std::endl;
			target->takeDamage(Atk);
		}
	}

	// 강화 방어 스킬
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
			std::cout << name << " : 강화된 방어로 적의 공격을 막아냅니다.\n" << std::endl;
			targetCharacter->defBuff(10, 2);
		}
		else
		{
			std::cout << name << ": 강화된 방어로 적의 공격을 막아냅니다.\n" << std::endl;
			defBuff(10, 2);
		}
		return;
	}
	// 회복의 방패
	if (Hp <= maxHp * 0.3)
	{
		std::cout << name << " : 회복의 방패로 스스로를 치유합니다.\n" << std::endl;
		heal(20);
		return;
	}
	// 일반 공격
	auto target = selectTarget(enemy, { "딜러", "제어자", "탱커" });
	if (target)
	{
		std::cout << name << "는 " << target->getName() << " 에게 기본 공격을 합니다.\n" << std::endl;
		target->takeDamage(Atk);
	}
}
