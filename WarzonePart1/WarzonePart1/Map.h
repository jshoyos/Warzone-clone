#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
using namespace std;

#pragma once
//-----------------------------------------------------------------------------------CLASS TERRITORY-------------------------------------------------------------------------------------------------------
//Represents the territory node
class Territory {
	//Name of the territory
	string _territoryName="";
	//id of the continent it belongs to. This id is the index in the list of continents created in the Map object
	const int _continent;
	//pointer to the owner of the current territory
	Player* _owner=NULL;
	//this number represent the number of armies currently in the territory
	int _armies=0;
	//Link between territories is made via pointers
	vector<Territory*> _adjacentTerritories;
public:
#pragma region constructos
	//armies,adjacentterritories,continent can be set after the object is created
	Territory();
	Territory(string, int);
	Territory(string, int, vector<Territory*>);
#pragma endregion
#pragma region methods
	bool   setOwner(Player*);
	bool   setArmies(int);
	int    getArmies();
	Player getOwner();
	int    getContinent();
	string getTerritoryName();
	//This method is used to add a link to a specific territory
	bool addBorder(Territory*);
	friend ostream& operator<< (ostream&, const Territory&);
#pragma endregion
};
ostream& operator<< (ostream& stream, const Territory& territory) {
	if (territory._owner != NULL) {
		return stream << territory._territoryName << " currently has " << territory._armies << "owned by " << territory._owner << endl;
	}
	else {
		return stream << territory._territoryName << " belongs to no one "<< endl;
	}
}
//------------------------------------------------------------------------------------CLASS CONTINENT-------------------------------------------------------------------------------------------------------
class Continent {
	//Name of the continent
	string _continentName="";
	//The number of bonus armies the player receives for conquering this continent
	int _bonusArmies=0;
	//List of all territories belonging to the same Continent
	vector<Territory*> _territories;
public:
#pragma region constructos
	Continent();
	Continent(int);
	Continent(int, vector<Territory*>);
	friend ostream& operator<<(ostream&, const Continent&);
#pragma endregion
#pragma region methods
	bool setBonusArmies(int);
	int  getBonusArmies();
	bool addTerritory(Territory*);
#pragma endregion
}; 
ostream& operator<<(ostream& stream, const Continent& continent) {
	return stream << "Conquering " << continent._continentName << " gives you " << continent._bonusArmies << " armies" << endl;
}
//---------------------------------------------------------------------------------------------CLASS MAP-------------------------------------------------------------------------------------------------------
class Map {
	//the number of continents in the map
	const int _numberOfContinents;
	//List containing all the continents in the map.From this list it is possible to access the territories as well.
	vector<Continent*> _continents;
	//List containing all the territories in the map.
	vector<Territory*> _territories;
public:
#pragma region constructors
	Map(int);
	Map(int, vector<Continent*>);
#pragma endregion
#pragma region methods
	bool addContinent(Continent*);
	bool addTerritory(Territory*);
	//TODO: add methods to get a copy of both lists
	//TODO: add method to get a territory or continent by the name
#pragma endregion
};