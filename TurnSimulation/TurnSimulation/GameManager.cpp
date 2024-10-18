#include "GameManager.h"
#include "DarkSorcerer.h"
#include "PoisonSpirit.h"
#include "Assassin.h"
#include "Destroyer.h"
#include "BraveGuardian.h"
#include "ShieldWarrior.h"
#include <algorithm>


GameManager::GameManager(const std::vector<Character*>& character)
	: characters(characters)
{
	std::vector<Character*> characters =
	{
				new Destroyer("파괴자")
		,		new Assassin("암살자")
		,		new ShieldWarrior("방패 전사")
		,		new BraveGuardian("용맹한 수호자")
		,		new DarkSorcerer("어둠의 마법사")
		,		new PoisonSpirit("독성 정령")
	};

	RandomTeam(characters);
}

void GameManager::RandomTeam(std::vector<Character*>& characters)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	std::random_shuffle(characters.begin(), characters.end());


	for (size_t i = 0; i < characters.size(); i++)
	{
		if (i % 2 == 0)
		{
			redTeam.Addteam(characters[i]);
		}
		else
		{
			blueTeam.Addteam(characters[i]);
		}
	}
	std::cout << "== redTeam 을 생성합니다  ==\n" << std::endl;
	std::cout << "redTeam" << std::endl;
	redTeam.TeamInfo();
	std::cout << std::endl;
	std::cout << "== blueTeam 을 생성합니다 ==\n" << std::endl;
	std::cout << "blueTeam" << std::endl;
	blueTeam.TeamInfo();
	std::cout << std::endl;
}

void GameManager::GameStart()
{
	std::cout << "====================  게임시작  ====================\n" << std::endl;

	while (redTeam.MemberStatus() && blueTeam.MemberStatus())
	{
		std::cout << "====================================================\n" << std::endl;
		std::cout << tunecount << "  번째 턴 시작\n" << std::endl;
		std::cout << "====================================================\n" << std::endl;
		std::cout << "redTeam 공격 \n" << std::endl;
		GameTurn(redTeam.getMember(), blueTeam.getMember());

		if (!blueTeam.MemberStatus())
		{
			break;
		}

		std::cout << "====================================================\n" << std::endl;
		std::cout << "blueTeam 공격 \n" << std::endl;
		GameTurn(blueTeam.getMember(), redTeam.getMember());

		if (!redTeam.MemberStatus())
		{
			break;
		}

		tunecount++;

		if (tunecount >= 101)
		{
			break;
		}
	}

	if (redTeam.MemberStatus() && !blueTeam.MemberStatus())
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "\nredTeam 이 승리했습니다!\n" << std::endl;
		std::cout << "====================================================" << std::endl;
	}
	else if (blueTeam.MemberStatus() && !redTeam.MemberStatus())
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "\nblueTeam 이 승리했습니다!\n" << std::endl;
		std::cout << "====================================================" << std::endl;
	}
	else
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "\n100턴안에 종료되지 않았으므로 무승부 입니다.\n" << std::endl;
		std::cout << "====================================================" << std::endl;
	}
}

void GameManager::GameTurn(std::vector<Character*>& team, std::vector<Character*>& enemy)
{
	for (Character* character : team)
	{
		if (character->isLive())
		{
			character->skills(team, enemy);
		}
	}
}


