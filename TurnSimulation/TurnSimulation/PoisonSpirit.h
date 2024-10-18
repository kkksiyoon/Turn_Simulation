#pragma once
#include "Controller.h"

class PoisonSpirit : public Controller
{
public:
	PoisonSpirit(std::string name);

	void skills(std::vector<Character*>& team, std::vector<Character*> enemy) override;
};
