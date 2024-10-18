#pragma once
#include "Tanker.h"

class ShieldWarrior : public Tanker
{
public:
	ShieldWarrior(std::string name);

	void skills(std::vector<Character*>& team, std::vector<Character*> enemy) override;
};
