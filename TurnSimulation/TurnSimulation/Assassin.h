#pragma once
#include "Dealer.h"

class Assassin : public Dealer
{
public:
	Assassin(std::string name);

	void skills(std::vector<Character*>& team, std::vector<Character*> enemy) override;
};
