#include "Map.h"
#include <map>
#include <list>

Map::Map(int numberOfContinents) : _numberOfContinents(numberOfContinents) {}

Map::Map(int numberOfContinents, vector<Continent *> continents) : _numberOfContinents(numberOfContinents), _continents(continents)
{
}

bool Map::validate()
{

	// Check if undirected graph is connected by doing DFS
	// wont mean anything if graph is not undirected
	//
	// I think you might have to do it for every node in the graph to ensure undirected
	if (!isConnected())
	{
		return false;
	}
	return true;
}

// 	return true;
// }

bool Map::checkTerritories()
{

	// i honesetly dont know if this one works

	// check for empty continents

	// for (Continent *continent : _continents)
	// 	if (continent->territoriesSize() == 0)
	// 	{
	// 		return 0;
	// 	}

	// 1. put all territories in continents into a collection
	// 2. take unique elements
	// 3. if territories size != unique elements, there is an issue

	list<int> ids;

	for (auto continent : _continents) {
	}

	ids.sort();
	ids.unique();

	if (ids.size() != _territories.size())
		return 0;
}

bool Map::isConnected()
{

	int continents_size = getContinentsSize();
	int territories_size = getTerritoriesSize();

	// IS IT NOT UNDIRECTED? WHO CARES. JUST TRY EVERY NODE
	// AND FIND OUT.
	for (int i = 0; i < territories_size; ++i)
	{

		Territory *root_node = getTerritoryById(i);
		vector<bool> visited_territories(territories_size, false);

		territoryDFS(root_node, visited_territories);

		for (bool vis : visited_territories)
		{
			if (!vis)
			{
				cout << "I found a path I could not reach :(" << endl;
				return false;
			}
		}
	}

	cout << "Yay! I am fully connected! :)" << endl;
	return true;
}

// version using unique id
void Map::territoryDFS(Territory *startNode, vector<bool> &visited)
{
	int node_id = startNode->getId();
	visited[node_id] = true;

	for (Territory *adj_node : startNode->getAdjacent())
	{
		int adj_id = adj_node->getId();
		if (!visited[adj_id])
		{
			territoryDFS(adj_node, visited);
		}
	}
}

bool Map::addContinent(Continent *continent)
{
	if (continent != NULL)
	{
		_continents.push_back(continent);
		return true;
	}
	return false;
}

bool Map::addTerritory(Territory *territory)
{
	if (territory != NULL && territory->getTerritoryName() != "")
	// i commented this out because i think the ids can be 0
	//territory->getContinent() != 0
	{
		_territories.push_back(territory);
		_continents[territory->getContinent()]->addTerritory(territory);
		return true;
	}
	return false;
}

Territory::Territory() : _territoryName(), _continent()
{
}

Territory::Territory(int id, string territoryName, int continent) : _id(id), _territoryName(territoryName), _continent(continent)
{
}

Territory::Territory(string territoryName, int continent) : _territoryName(territoryName), _continent(continent)
{
}

Territory::Territory(string territoryName, int continent, vector<Territory *> adjacentTerritories) : _territoryName(territoryName), _continent(continent), _adjacentTerritories(adjacentTerritories)
{
}

bool Territory::setOwner(Player *owner)
{
	if (owner != NULL)
	{
		_owner = owner;
		return true;
	}
	return false;
}

bool Territory::setArmies(int armies)
{
	if (armies >= 0 /*TODO: make sure someone owns the territory && getOwner()!=NULL*/)
	{
		_armies = armies;
		return true;
	}
	return false;
}

int Territory::getArmies()
{
	return _armies;
}

Territory *Map::getTerritoryById(int id)
{
	return _territories[id];
}

Continent *Map::getContinentById(int id)
{
	return _continents[id];
}

int Map::getContinentsSize()
{
	return _continents.size();
}

int Map::getTerritoriesSize()
{
	return _territories.size();
}

Player Territory::getOwner()
{
	//TODO: once the player class has a copy constructor return a copy of the player
	return *_owner;
	//return new Player(*_owner);
}

int Territory::getContinent()
{
	return _continent;
}

vector<Territory *> Territory::getAdjacent()
{
	return _adjacentTerritories;
}

int Territory::getId()
{
	return _id;
}

string Territory::getTerritoryName()
{
	return string(_territoryName);
}

bool Territory::addBorder(Territory *territory)
{
	if (territory != NULL && territory->_territoryName != "")
	{
		_adjacentTerritories.push_back(territory);
		return true;
	}
	return false;
}

ostream &operator<<(ostream &stream, const Territory &territory)
{
	if (territory._owner != NULL)
	{
		return stream << territory._territoryName << " currently has " << territory._armies << "owned by " << territory._owner << endl;
	}
	else
	{
		return stream << territory._territoryName << " belongs to no one " << endl;
	}
}

Continent::Continent(string name) : _continentName(name)
{
}

Continent::Continent(int id, string continentName) : _id(id), _continentName(continentName)
{
}

Continent::Continent() : _continentName(), _bonusArmies()
{
}

Continent::Continent(int bonusArmies) : _bonusArmies(bonusArmies)
{
}

Continent::Continent(int bonusArmies, vector<Territory *> territories) : _bonusArmies(bonusArmies), _territories(territories)
{
}

bool Continent::setBonusArmies(int bonus)
{
	if (bonus >= 0)
	{
		_bonusArmies = bonus;
		return true;
	}
	return false;
}

int Continent::getBonusArmies()
{
	return _bonusArmies;
}

int Continent::getId()
{
	return _id;
}

bool Continent::addTerritory(Territory *territory)
{
	if (territory != NULL && territory->getTerritoryName() != "")
	{
		// territory->getContinent() != 0
		_territories.push_back(territory);
		return true;
	}
	return false;
}

ostream &operator<<(ostream &stream, const Continent &continent)
{
	return stream << "Conquering " << continent._continentName << " gives you " << continent._bonusArmies << " armies" << endl;
}
