#include "Map.h"

Map::Map(int numberOfContinents) : _numberOfContinents(numberOfContinents) {}

Map::Map(int numberOfContinents, vector<Continent*> continents):_numberOfContinents(numberOfContinents),_continents(continents)
{
}

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
