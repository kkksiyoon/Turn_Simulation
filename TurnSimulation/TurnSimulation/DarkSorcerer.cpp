#include "DarkSorcerer.h"
#include <algorithm>

DarkSorcerer::DarkSorcerer(std::string name)
	: Controller(name, 55, 12, 10)
{
}

void DarkSorcerer::skills(std::vector<Character*>& team, std::vector<Character*> enemy)
{
	// 아군에 탱커가 없을 때
	bool tanker = std::any_of(team.begin(), team.end(), [](Character* character)
		{
			return character->isLive() && character->getType() == "탱커";
		});
	if (!tanker)
	{
		auto target = selectTarget(enemy, { "딜러", "제어자", "탱커" });
		if (target)
		{
			std::cout << name << " : 어둠의 손길이 적을 기절시킵니다.\n" << std::endl;
			target->takeStatus(StatusEffect::Stunned, 0, 0);
			return;
		}
	}
	// 체력이 20%이하인 적이 있을 때
	for (auto& enemys : enemy)
	{
		if (enemys->isLive() && enemys->getHp() <= enemys->getMaxHp() * 0.2)
		{
			std::cout << name << " : 어둠의 손길이 적을 기절시킵니다.\n" << std::endl;
			enemys->takeStatus(StatusEffect::Stunned, 0, 0);
			return;
		}
	}
	//어둠의 구름
	int lowHpEnemy = std::count_if(enemy.begin(), enemy.end(), [](Character* character)
		{
			return character->isLive() && character->getHp() <= character->getMaxHp() * 0.5;
		});
	if (lowHpEnemy >= 2)
	{
		std::cout << name << " : 어둠의 구름이 적의 힘과 방어력을 약화시킵니다.\n" << std::endl;
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
	// 일반 공격
	auto target = selectTarget(enemy, { "딜러", "제어자", "탱커" });
	if (target)
	{
		std::cout << name << "는 " << target->getName() << " 에게 기본 공격을 합니다.\n" << std::endl;
		target->takeDamage(Atk);
	}
}
