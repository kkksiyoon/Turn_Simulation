#pragma once
#include "Character.h"

class Dealer : public Character
{
public:
	Dealer(std::string name, int hp, int atk, int def);

	void skills(std::vector<Character*>& team, std::vector<Character*> enemy) override;
};


