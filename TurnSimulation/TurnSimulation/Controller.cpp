#include "Controller.h"

Controller::Controller(std::string name, int hp, int atk, int def)
	: Character(name,"������", hp, atk, def)
{
}

void Controller::skills(std::vector<Character*>& team, std::vector<Character*> enemy)
{
}
