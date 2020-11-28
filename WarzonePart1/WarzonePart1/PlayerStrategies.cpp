#include "PlayerStrategies.h"

void HumanPlayerStrategy::issueOrder(string, Player*, Player*, Territory*, Territory*, int)
{
}

vector<Territory*>* HumanPlayerStrategy::toAttack()
{
	return nullptr;
}

vector<Territory*>* HumanPlayerStrategy::toDefend()
{
	return nullptr;
}

void AggressivePlayerStrategy::issueOrder(string, Player*, Player*, Territory*, Territory*, int)
{
}

vector<Territory*>* AggressivePlayerStrategy::toAttack()
{
	return nullptr;
}

vector<Territory*>* AggressivePlayerStrategy::toDefend()
{
	return nullptr;
}

void BenevolentPlayerStrategy::issueOrder(string, Player*, Player*, Territory*, Territory*, int)
{
}

vector<Territory*>* BenevolentPlayerStrategy::toAttack()
{
	return nullptr;
}

vector<Territory*>* BenevolentPlayerStrategy::toDefend()
{
	return nullptr;
}

void NeutralPlayerStrategy::issueOrder(string, Player*, Player*, Territory*, Territory*, int)
{
}

vector<Territory*>* NeutralPlayerStrategy::toAttack()
{
	return nullptr;
}

vector<Territory*>* NeutralPlayerStrategy::toDefend()
{
	return nullptr;
}
