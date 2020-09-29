#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "Player.h"
using namespace std;

#pragma once
//-----------------------------------------------------------------------------------CLASS TERRITORY-------------------------------------------------------------------------------------------------------
//Represents the territory node
class Territory {
	//Name of the territory
	string _territoryName="";
	//id of the continent it belongs to. This id is the index in the list of continents created in the Map object
	int _continent;
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
	Territory(const Territory&);
	Territory(string, int);
	Territory(string, int, vector<Territory*>);
#pragma endregion
#pragma region methods
	Territory& operator=(const Territory&);
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
ostream& operator<< (ostream& stream, const Territory& territory);
//------------------------------------------------------------------------------------CLASS CONTINENT-------------------------------------------------------------------------------------------------------
class Continent {
	//Name of the continent
	string _continentName="";
	//The number of bonus armies the player receives for conquering this continent
	int _bonusArmies=0;
	//List of all territories belonging to the same Continent
	vector<Territory*> _territories;
	vector<Continent*> _adjacentContinents;
public:
#pragma region constructos
	Continent();
	Continent(const Continent&);
	/*Continent(int);
	Continent(int, vector<Territory*>);*/
	Continent(string);
	Continent(string, int);
	Continent(string, int, vector<Territory*>);
	friend ostream& operator<<(ostream&, const Continent&);
#pragma endregion
#pragma region methods
	Continent& operator=(const Continent&);
	bool setBonusArmies(int);
	int  getBonusArmies();
	int  territoriesSize();
	bool addTerritory(Territory*);
	//bool addBorder(Continent*);
	vector<Territory> getTerritories();
#pragma endregion
}; 
ostream& operator<<(ostream& stream, const Continent& continent);
//---------------------------------------------------------------------------------------------CLASS MAP-------------------------------------------------------------------------------------------------------
class Map {
	//the number of continents in the map
	int _numberOfContinents;
	//List containing all the continents in the map.From this list it is possible to access the territories as well.
	vector<Continent*> _continents;
	//List containing all the territories in the map.
	vector<Territory*> _territories;
public:
#pragma region constructors
	Map();
	Map(const Map&);
	Map(int);
	Map(int, vector<Continent*>);
#pragma endregion
#pragma region methods
	Map& operator=(const Map&);
	bool addContinent(Continent*);
	bool addTerritory(Territory*);
	bool validate();
	bool isConnected();
	bool checkTerritories();
	void territoryDFS(Territory* start, map<Territory*, bool> visited);
	void continentDFS(Continent* start, map<Continent*, bool> visited);
	vector<Territory> getTerritories();
	vector<Continent> getContinents();
	//TODO: add method to get a territory or continent by the name
#pragma endregion
};