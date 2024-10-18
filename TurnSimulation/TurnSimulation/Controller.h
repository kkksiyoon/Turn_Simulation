#pragma once
#include "Character.h"

class Controller : public Character
{
public:
	Controller(std::string name, int hp, int atk, int def);

	void skills(std::vector<Character*>& team, std::vector<Character*> enemy) override;
};
