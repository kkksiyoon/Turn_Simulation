#pragma once
#include "Dealer.h"

class Destroyer : public Dealer
{
public:
	Destroyer(std::string name);

	void skills(std::vector<Character*>& team, std::vector<Character*> enemy) override;
};

