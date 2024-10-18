#include <ctime>

#include "Character.h"
#include "GameManager.h"
#include "Team.h"

#include "Destroyer.h"
#include "Assassin.h"
#include "ShieldWarrior.h"
#include "BraveGuardian.h"
#include "DarkSorcerer.h"
#include "PoisonSpirit.h"

int main()
{
	std::vector<Character*> characters;

	GameManager gameManager(characters);
	gameManager.GameStart();

	for (Character* character : characters)
	{
		delete character;
	}

	return 0;
}