#include "Character.h"

Character::Character(std::string name, std::string type, int hp, int atk, int def)
	: name(name)
	, type(type)
	, Hp(hp)
	, maxHp(hp)
	, Atk(atk)
	, Def(def)
{
}

void Character::takeDamage(int damage)
{
	int damages = std::max(0, damage - getDef());
	Hp -= damages;
	Hp = std::max(0, Hp);
	std::cout << name << "은 " << damages << "의 피해를 입었습니다. 남은 체력 : " << Hp << "/" << maxHp << "\n" << std::endl;
}

void Character::takeStatus(StatusEffect statusEf, int duration, int damage)
{
	status = statusEf;
	if (statusEf == StatusEffect::Poisoned)
	{
		poisonDuration = duration;
		poisonDamage = damage;
	}
	else if (statusEf == StatusEffect::Stunned)
	{

	}
	else if (statusEf == StatusEffect::Taunted)
	{
		tauntDuration = duration;
		isTaunted = true;
	}
}

void Character::updateStatus()
{
	if (status == StatusEffect::Poisoned)
	{
		if (poisonDuration > 0)
		{
			Hp -= poisonDamage;
			Hp = std::max(0, Hp);
			std::cout << name << "는(은) 독 피해로 " << poisonDamage << "의 피해를 입었습니다. 남은 체력: " << Hp << "/" << maxHp << "\n" << std::endl;
			poisonDuration--;
		}
		if (poisonDuration == 0)
		{
			status = StatusEffect::None;
			poisonDamage = 0;
		}
	}
	if (defenseBuffDuration > 0)
	{
		defenseBuffDuration--;
		if (defenseBuffDuration == 0)
		{
			defenseBuff = 0;
			std::cout << name << "의 방어력 증가 효과가 사라졌습니다.\n";
		}
	}
	if (tauntDuration > 0)
	{
		tauntDuration--;
		if (tauntDuration == 0)
		{
			isTaunted = false;
			std::cout << name << "의 도발 효과가 사라졌습니다.\n";
		}
	}
}

void Character::defBuff(int buffamount, int duration)
{
	defenseBuff += buffamount;
	defenseBuffDuration = duration;
}

void Character::heal(int amount)
{
	Hp += amount;
	Hp = std::min(Hp, maxHp);
	std::cout << name << "의 체력이 " << amount << "만큼 회복되었습니다. 현재 체력 : " << Hp << "/" << maxHp << "\n" << std::endl;
}

void Character::turn(std::vector<Character*>& team, std::vector<Character*> enemy)
{
	if (!isLive())
	{
		return;
	}

	updateStatus();

	if (status == StatusEffect::Stunned)
	{
		std::cout << name << "는 기절하여 행동할 수 없습니다." << std::endl;
		status = StatusEffect::None; // 기절은 한턴만
		return;
	}

	skills(team, enemy);
}


Character* Character::selectTarget(const std::vector<Character*>& enemy, const std::vector<std::string>& priority, bool canKill)
{
	std::vector<Character*> list;

	for (const auto& type : priority)
	{
		for (auto* enemys : enemy)  // 적을 순회
		{ 						    
			if (enemys->isLive())   // 살아있는지 확인
			{
				if (canKill && enemys->getHp() <= getAtk()) // 적의 hp가 나의 공격력보다 작거나 같은지 확인
				{
					return enemys;
				}

				list.push_back(enemys);
			}
		}
	}
	// 후보가 없으면 살아있는 적을 아무나 선택
	if (list.empty())
	{
		for (const auto& enemys : enemy)
		{
			if (enemys->isLive())
			{
				list.push_back(enemys);
			}
		}
	}
	// 후보중 랜덤 선택
	if (!list.empty())
	{
		return list[rand() % list.size()];
	}

	return nullptr;
}
