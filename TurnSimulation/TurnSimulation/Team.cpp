#include "Team.h"
#include <algorithm>

Team::Team()
{
}

Team::~Team()
{
	for (auto member : members)
	{
		delete member;
	}
}

void Team::Addteam(Character* character)
{
	members.push_back(character);
}

bool Team::MemberStatus() const
{
	return std::any_of(members.begin(), members.end(), [](Character* characters) { return characters->isLive(); });
}

void Team::TeamInfo() const
{
	for (const auto& member : members)
	{
		std::cout << member->getName() << " (" << member->getType() << ")\n";
	}
}

