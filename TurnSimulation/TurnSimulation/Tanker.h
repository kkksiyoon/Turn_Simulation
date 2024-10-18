#pragma once
#include "Character.h"

class Tanker : public Character
{
public:
	Tanker(std::string name, int hp, int atk, int def);

	void skills(std::vector<Character*>& team, std::vector<Character*> enemy) override;
};
