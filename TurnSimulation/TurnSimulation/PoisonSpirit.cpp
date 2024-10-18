#include "PoisonSpirit.h"
#include <algorithm>

PoisonSpirit::PoisonSpirit(std::string name)
	: Controller(name, 60, 10, 9)
{
}

void PoisonSpirit::skills(std::vector<Character*>& team, std::vector<Character*> enemy)
{
	// 적 탱커의 체력이 50% 이상일 때 그 탱커에게 사용
	for (auto& enemys : enemy)
	{
		if (enemys->isLive() && enemys->getType() == "탱커" && enemys->getMaxHp() * 0.5 && enemys->getStatus() != StatusEffect::Poisoned)
		{
			std::cout << name << " : 저주의 손길이 적을 3턴동안 중독시킵니다. \n" << std::endl;
			enemys->takeStatus(StatusEffect::Poisoned, 3, 5);
			return;
		}
	}

	// 체력이 30% 이하인 적이 있을 때 
	for (auto& enemys : enemy)
	{
		if (enemys->isLive() && enemys->getHp() <= enemys->getMaxHp() * 0.3 && enemys->getStatus() != StatusEffect::Poisoned)
		{
			std::cout << name << " : 저주의 손길이 적을 3턴동안 중독 시킵니다. \n" << std::endl;
			enemys->takeStatus(StatusEffect::Poisoned, 3, 5);
			return;
		}
	}

	// 독의 폭풍
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
		std::cout << name << " : 독의 폭풍이 적들을 3턴동안 휩쓸고 갑니다.\n" << std::endl;
		for (auto& enemys : enemy)
		{
			if (enemys->isLive())
			{
				enemys->takeStatus(StatusEffect::Poisoned, 3, 5);
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
