#include "PlayerStrategies.h"

void HumanPlayerStrategy::issueOrder(string orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies)
{
	int response = 0;
	cout << "Would you like to issue the " << orderName <<" order! Enter 1 for yes 0 for no."<<endl;
	cin >> response;
	if (response) {
		if (orderName._Equal("deploy")) {
		Deploy* newOrder = new Deploy(p1, target, numberOfArmies);
		p1->addOrder(newOrder);
		}
		else if(orderName._Equal("advance")){
			Advance* newOrder = new Advance(p1, source, target, numberOfArmies);
			p1->addOrder(newOrder);
		}
		else if(orderName._Equal("airlift")){
			Airlift* newOrder = new Airlift(p1,source, target, numberOfArmies);
			p1->addOrder(newOrder);
		}
		else if (orderName._Equal("bomb")) {
			Bomb* newOrder = new Bomb(p1, target);
			p1->addOrder(newOrder);
		}
		else if (orderName._Equal("blockade")) {
			Blockade* newOrder = new Blockade(p1, target);
			p1->addOrder(newOrder);
		}
		else if (orderName._Equal("negotiate")) {
			Negotiate* newOrder = new Negotiate(p1,p2);
			p1->addOrder(newOrder);
		}
		else {
			cout << "ERROR: unrecognized order!" << endl;
		}
	}
}

vector<Territory*>* HumanPlayerStrategy::toAttack(Player* player)
{
	vector<Territory*>* attackList = new vector<Territory*>();
	
	for (Territory* terr : *player->getTerritoryList()) {
		if (terr->getArmies() == 0) {
			continue;
		}
		for (Territory* adjTerr : *terr->getAdjacent()) {

			//checks if adjacent territories are part of the players territories.
			if (!(std::find(player->getTerritoryList()->begin(), player->getTerritoryList()->end(), adjTerr) != player->getTerritoryList()->end())){
				
				if (!(std::find(attackList->begin(), attackList->end(), adjTerr) != attackList->end())) {
					attackList->push_back(adjTerr);
				}	
			}
		}
	}
	cout << "Here are the following territories to attack! Please enter the number of the territory you wish to attack." << endl;
	int index = 0;
	for (Territory* terr: *attackList) {
		cout <<"["<< index <<"] "<< *terr;
		index++;
	}
	cin >> index;

	vector<Territory*>* newList = new vector<Territory*>();
	newList->push_back(attackList->at(index));
	delete attackList; attackList = NULL;
	return newList;
}

vector<Territory*>* HumanPlayerStrategy::toDefend(Player* player)
{
	vector<Territory*>* defendList = player->getTerritoryList();
	int choice = 1;
	vector<Territory*>* newList = new vector<Territory*>();
	cout << "Here are the following territories to defend! Please enter the number of the territory you wish to reinforce." << endl;
	int index = 0;
	for (Territory* terr : *defendList) {
		cout << "[" << index << "] " << *terr;
		index++;
	}
	cin >> index;
	newList->push_back(defendList->at(index));

	return newList;
}

void AggressivePlayerStrategy::issueOrder(string orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies)
{
	if (orderName._Equal("deploy")) {
		Deploy* newOrder = new Deploy(p1, target, numberOfArmies);
		p1->addOrder(newOrder);
	}
	else if (orderName._Equal("advance")) {
		Advance* newOrder = new Advance(p1, source, target, numberOfArmies);
		p1->addOrder(newOrder);
	}
	else if (orderName._Equal("airlift")) {
		Airlift* newOrder = new Airlift(p1, source, target, numberOfArmies);
		p1->addOrder(newOrder);
	}
	else if (orderName._Equal("bomb")) {
		Bomb* newOrder = new Bomb(p1, target);
		p1->addOrder(newOrder);
	}
	else if (orderName._Equal("blockade")) {
		Blockade* newOrder = new Blockade(p1, target);
		p1->addOrder(newOrder);
	}
	else if (orderName._Equal("negotiate")) {
		cout << "I am an aggressive player! I do not wish to negotiate with anyone" << endl;
	}
	else {
		cout << "ERROR: unrecognized order!" << endl;
	}
}

vector<Territory*>* AggressivePlayerStrategy::toAttack(Player* player)
{
	vector<Territory*>* attackList = new vector<Territory*>();

	for (Territory* terr : *player->getTerritoryList()) {
		if (terr->getArmies() == 0) {
			continue;
		}
		for (Territory* adjTerr : *terr->getAdjacent()) {

			//checks if adjacent territories are part of the players territories.
			if (!(std::find(player->getTerritoryList()->begin(), player->getTerritoryList()->end(), adjTerr) != player->getTerritoryList()->end())) {

				if (!(std::find(attackList->begin(), attackList->end(), adjTerr) != attackList->end())) {
					attackList->push_back(adjTerr);
				}
			}
		}
	}
	//cout << player->getName()<<" :     SIZE ==============(" << attackList->size()<<")================" << endl;
	return attackList;
}

vector<Territory*>* AggressivePlayerStrategy::toDefend(Player* player)
{
	int armyCount = 0;
	Territory* territoryToDefend = nullptr;

	vector<Territory*>* defendList = new vector<Territory*>();

	for (Territory* terr : *player->getTerritoryList()) {
		if (terr->getArmies() >= armyCount) {
			territoryToDefend = terr;
			armyCount = terr->getArmies();
		}
	}
	defendList->push_back(territoryToDefend);
	return defendList;
}

void BenevolentPlayerStrategy::issueOrder(string orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies)
{
	if (orderName._Equal("deploy")) {
		Deploy* newOrder = new Deploy(p1, target, numberOfArmies);
		p1->addOrder(newOrder);
	}
	else if (orderName._Equal("advance")) {
		Advance* newOrder = new Advance(p1, source, target, numberOfArmies);
		p1->addOrder(newOrder);
	}
	else if (orderName._Equal("attack")) {
		cout << "I am a good person I shall not attack anyone" << endl;
	}
	else if (orderName._Equal("airlift")) {
		Airlift* newOrder = new Airlift(p1, source, target, numberOfArmies);
		p1->addOrder(newOrder);
	}
	else if (orderName._Equal("bomb")) {
		cout << "I am a good person I shall not bomb this territory!" << endl;
	}
	else if (orderName._Equal("blockade")) {
		Blockade* newOrder = new Blockade(p1, target);
		p1->addOrder(newOrder);
	}
	else if (orderName._Equal("negotiate")) {
		Negotiate* newOrder = new Negotiate(p1, p2);
		p1->addOrder(newOrder);
	}
	else {
		cout << "ERROR: unrecognized order!" << endl;
	}
}

vector<Territory*>* BenevolentPlayerStrategy::toAttack(Player* player)
{
	cout << "I am a good person, I would never attack anyone."<<endl;
	return nullptr;	//TODO: check null pointer exceptions
}

vector<Territory*>* BenevolentPlayerStrategy::toDefend(Player* player)
{
	int armyCount = player->getTerritoryList()->at(0)->getArmies();	//gets initial count
	Territory* territoryToDefend = nullptr;

	vector<Territory*>* defendList = new vector<Territory*>();

	for (Territory* terr : *player->getTerritoryList()) {
		if (terr->getArmies() <= armyCount) {
			territoryToDefend = terr;
			armyCount = terr->getArmies();
		}
	}
	defendList->push_back(territoryToDefend);
	return defendList;
}

void NeutralPlayerStrategy::issueOrder(string orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies)
{
	cout << p1->getName() << " is a Neutral player, I do not issue any orders" << endl;
}

vector<Territory*>* NeutralPlayerStrategy::toAttack(Player* player)
{
	return nullptr;//TODO: check null pointer exceptions
}

vector<Territory*>* NeutralPlayerStrategy::toDefend(Player* player)
{
	return nullptr;//TODO: check null pointer exceptions
}
