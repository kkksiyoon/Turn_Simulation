#pragma once
#include "Controller.h"

class DarkSorcerer : public Controller
{
public:
	DarkSorcerer(std::string name);

	void skills(std::vector<Character*>& team, std::vector<Character*> enemy) override;
};
