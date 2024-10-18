#pragma once
#include <string>
#include <iostream>
#include <vector>

enum class StatusEffect
{
	None,
	Stunned,
	Poisoned,
	Taunted,
};

class Character
{
public:

	std::string name;
	std::string type;
	StatusEffect status = StatusEffect::None;
	int Hp;
	int maxHp;
	int Atk;
	int Def;
	int poisonDuration = 0;
	int poisonDamage = 0;
	int defenseBuff = 0;
	int defenseBuffDuration = 0;
	bool isTaunted = false;
	int tauntDuration = 0;

public:
	Character(std::string name, std::string type, int hp, int atk, int def);
	virtual ~Character() = default;

	void takeDamage(int damage);
	void takeStatus(StatusEffect statusEf, int duration, int damage);
	void updateStatus();
	void defBuff(int buffamount, int duration);
	void heal(int amount);
	void turn(std::vector<Character*>& team, std::vector<Character*> enemy);   


	virtual void skills(std::vector<Character*>& team, std::vector<Character*> enemy) = 0;

	Character* selectTarget(const std::vector<Character*>& enemy, const std::vector<std::string>& priority, bool canKill = false);

	bool isLive() const { return Hp > 0; }
	int getHp() const { return Hp; }
	int getMaxHp() const { return maxHp; }
	int getAtk() const { return Atk; }
	int getDef() const { return Def; }
	std::string getName() const { return name; }
	std::string getType() const { return type; }
	StatusEffect getStatus() const{ return status; }
};

