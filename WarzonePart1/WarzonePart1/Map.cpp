#include "Map.h"
#include <map>
#include <list>

Map::Map(int numberOfContinents) : _numberOfContinents(numberOfContinents) {}

Map::Map(int numberOfContinents, vector<Continent*> continents):_numberOfContinents(numberOfContinents),_continents(continents)
{
}

bool Map::validate() 
{

	// Check if undirected graph is connected by doing DFS
	// wont mean anything if graph is not undirected
	if (!isConnected()) {
		return false;
	}

	return true;
}

bool Map::checkTerritories() {

	// TODO
	// check if each continent has a territory

	for (Continent* continent : _continents)
		if (continent->territoriesSize() == 0) {
			return 0;
		}

	// TODO
	// 1. put all territories in continents into a collection
	// 2. take unique elements
	// 3. if territories size != unique elements, there is an issue

	list<string> uniqueNames;

	uniqueNames.sort();
	uniqueNames.unique();

	if (uniqueNames.size() !=  _territories.size())
		return 0;
}

bool Map::isConnected()
{
	map<Territory*, bool> visited1;
	map<Continent*, bool> visited2;

	for (auto territory : _territories)
		visited1.insert(pair<Territory*, bool>(territory, false));

	for (auto p : visited1) {
		if (p.second)
			return false; 
	}

	return true;
}

void Map::territoryDFS(Territory* startNode, map<Territory*, bool> visited)
{
	visited[startNode] = true;

	for (auto adjNode : startNode->getAdjacent()) {
		if (!visited[adjNode]) {
			territoryDFS(adjNode, visited);
		}
	}
}

// void Map::continentDFS(Continent* startNode, map<Continent*, bool> visited)
// {

	

// }



bool Map::addContinent(Continent* continent)
{
	if (continent != NULL) {
		_continents.push_back(continent);
		return true;
	}
	return false;
}

bool Map::addTerritory(Territory* territory)
{
	if (territory != NULL && territory->getTerritoryName() != "" && territory->getContinent() != 0)
	{
		_territories.push_back(territory);
		_continents[territory->getContinent()]->addTerritory(territory);
		return true;
	}
	return false;
}

Territory::Territory():_territoryName(),_continent()
{
}

Territory::Territory(string territoryName, int continent):_territoryName(territoryName),_continent(continent)
{
}

Territory::Territory(string territoryName, int continent, vector<Territory*> adjacentTerritories):_territoryName(territoryName),_continent(continent),_adjacentTerritories(adjacentTerritories)
{
}

bool Territory::setOwner(Player* owner)
{
	if (owner != NULL) {
		_owner = owner;
		return true;
	}
	return false;
}

bool Territory::setArmies(int armies)
{
	if (armies >= 0 /*TODO: make sure someone owns the territory && getOwner()!=NULL*/) {
		_armies = armies;
		return true;
	}
	return false;
}

int Territory::getArmies()
{
	return _armies;
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

string Territory::getTerritoryName()
{
	return string(_territoryName);
}

bool Territory::addBorder(Territory* territory)
{
	if (territory != NULL && territory->_territoryName != "") {
		_adjacentTerritories.push_back(territory);
		return true;
	}
	return false;
}

Continent::Continent():_continentName(),_bonusArmies()
{
}

Continent::Continent(int bonusArmies):_bonusArmies(bonusArmies)
{
}

Continent::Continent(int bonusArmies, vector<Territory*> territories):_bonusArmies(bonusArmies),_territories(territories)
{
}

bool Continent::setBonusArmies(int bonus)
{
	if (bonus>=0){
		_bonusArmies = bonus;
		return true;
	}
	return false;
}

int Continent::getBonusArmies()
{
	return _bonusArmies;
}

bool Continent::addTerritory(Territory* territory)
{
	if (territory != NULL && territory->getTerritoryName() != "" && territory->getContinent() != 0) {
		_territories.push_back(territory);
		return true;
	}
	return false;
}

