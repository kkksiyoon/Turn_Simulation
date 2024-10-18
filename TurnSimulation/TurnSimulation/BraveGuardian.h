#pragma once
#include "Tanker.h"

class BraveGuardian : public Tanker
{
public:
	BraveGuardian(std::string name);

	void skills(std::vector<Character*>& team, std::vector<Character*> enemy) override;
};
