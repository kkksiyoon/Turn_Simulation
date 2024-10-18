#pragma once
#include "Character.h"

#include <vector>

class Team
{
private:
	std::string teamName;
	std::vector<Character*> members;

public:
	Team();
	~Team();

	void Addteam(Character* character);
	bool MemberStatus() const;
	void TeamInfo() const;

	std::vector<Character*>& getMember() { return members; }
	std::string getName() const { return teamName; }

};
