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
				new Destroyer("�ı���")
		,		new Assassin("�ϻ���")
		,		new ShieldWarrior("���� ����")
		,		new BraveGuardian("����� ��ȣ��")
		,		new DarkSorcerer("����� ������")
		,		new PoisonSpirit("���� ����")
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
	std::cout << "== redTeam �� �����մϴ�  ==\n" << std::endl;
	std::cout << "redTeam" << std::endl;
	redTeam.TeamInfo();
	std::cout << std::endl;
	std::cout << "== blueTeam �� �����մϴ� ==\n" << std::endl;
	std::cout << "blueTeam" << std::endl;
	blueTeam.TeamInfo();
	std::cout << std::endl;
}

void GameManager::GameStart()
{
	std::cout << "====================  ���ӽ���  ====================\n" << std::endl;

	while (redTeam.MemberStatus() && blueTeam.MemberStatus())
	{
		std::cout << "====================================================\n" << std::endl;
		std::cout << tunecount << "  ��° �� ����\n" << std::endl;
		std::cout << "====================================================\n" << std::endl;
		std::cout << "redTeam ���� \n" << std::endl;
		GameTurn(redTeam.getMember(), blueTeam.getMember());

		if (!blueTeam.MemberStatus())
		{
			break;
		}

		std::cout << "====================================================\n" << std::endl;
		std::cout << "blueTeam ���� \n" << std::endl;
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
		std::cout << "\nredTeam �� �¸��߽��ϴ�!\n" << std::endl;
		std::cout << "====================================================" << std::endl;
	}
	else if (blueTeam.MemberStatus() && !redTeam.MemberStatus())
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "\nblueTeam �� �¸��߽��ϴ�!\n" << std::endl;
		std::cout << "====================================================" << std::endl;
	}
	else
	{
		std::cout << "====================================================" << std::endl;
		std::cout << "\n100�Ͼȿ� ������� �ʾ����Ƿ� ���º� �Դϴ�.\n" << std::endl;
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


