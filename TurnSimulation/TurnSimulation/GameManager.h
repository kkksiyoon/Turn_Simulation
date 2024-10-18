#pragma once
#include "Team.h"

class GameManager
{

public:
	std::vector<Character*> characters;

	int tunecount = 1;

	Team redTeam;
	Team blueTeam;

	GameManager(const std::vector<Character*>& character);


	void RandomTeam(std::vector<Character*>& characters);
	void GameStart();
	void GameTurn(std::vector<Character*>& team, std::vector<Character*>& enemy);
};

