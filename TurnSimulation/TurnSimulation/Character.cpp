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
	std::cout << name << "�� " << damages << "�� ���ظ� �Ծ����ϴ�. ���� ü�� : " << Hp << "/" << maxHp << "\n" << std::endl;
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
			std::cout << name << "��(��) �� ���ط� " << poisonDamage << "�� ���ظ� �Ծ����ϴ�. ���� ü��: " << Hp << "/" << maxHp << "\n" << std::endl;
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
			std::cout << name << "�� ���� ���� ȿ���� ��������ϴ�.\n";
		}
	}
	if (tauntDuration > 0)
	{
		tauntDuration--;
		if (tauntDuration == 0)
		{
			isTaunted = false;
			std::cout << name << "�� ���� ȿ���� ��������ϴ�.\n";
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
	std::cout << name << "�� ü���� " << amount << "��ŭ ȸ���Ǿ����ϴ�. ���� ü�� : " << Hp << "/" << maxHp << "\n" << std::endl;
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
		std::cout << name << "�� �����Ͽ� �ൿ�� �� �����ϴ�." << std::endl;
		status = StatusEffect::None; // ������ ���ϸ�
		return;
	}

	skills(team, enemy);
}


Character* Character::selectTarget(const std::vector<Character*>& enemy, const std::vector<std::string>& priority, bool canKill)
{
	std::vector<Character*> list;

	for (const auto& type : priority)
	{
		for (auto* enemys : enemy)  // ���� ��ȸ
		{ 						    
			if (enemys->isLive())   // ����ִ��� Ȯ��
			{
				if (canKill && enemys->getHp() <= getAtk()) // ���� hp�� ���� ���ݷº��� �۰ų� ������ Ȯ��
				{
					return enemys;
				}

				list.push_back(enemys);
			}
		}
	}
	// �ĺ��� ������ ����ִ� ���� �ƹ��� ����
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
	// �ĺ��� ���� ����
	if (!list.empty())
	{
		return list[rand() % list.size()];
	}

	return nullptr;
}
