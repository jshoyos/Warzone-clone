#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "Player.h"

using namespace std;


class Player;
//-----------------------------------------------------------------------------------TERRITORY-------------------------------------------------------------------------------------------------------
//Represents the territory node
class Territory {
	// id of territory, this is used to refer to territories 0 to n
	int _id=0; 
	//Name of the territory
	string _territoryName = "";
	//id of the continent it belongs to. This id is the index in the list of continents created in the Map object
	int _continent;
	//pointer to the owner of the current territory
	Player* _owner = NULL;
	//this number represent the number of armies currently in the territory
	int _armies = 0;
	//Link between territories is made via pointers
	vector<Territory*> _adjacentTerritories;
public:
#pragma region constructos
	//armies,adjacentterritories,continent can be set after the object is created
	Territory();
	Territory(const Territory&);
	Territory(int id, string territoryName, int continent);
	Territory(int,string, int, vector<Territory*>*);
	~Territory();//clears the adjacent territories vector
#pragma endregion
#pragma region methods 
	Territory& operator=(const Territory&);
	bool   setOwner(Player*);
	bool   setArmies(int);
	int    getArmies();
	int    getContinent();
	int    getId();
	Player* getOwner();
	vector<Territory*>* getAdjacent();
	string getTerritoryName();
	//This method is used to add a link to a specific territory
	bool addBorder(Territory*);
	friend ostream& operator<< (ostream&, const Territory&);
#pragma endregion
};
ostream& operator<< (ostream& stream, const Territory& territory);
//----------------------------------------------------------------------------------------------CONTINENT-------------------------------------------------------------------------------------------------------
class Continent {
	// id of territory, this is used to refer to continents 0 to n
	int _id =0;
	//Name of the continent
	string _continentName = "";
	//The number of bonus armies the player receives for conquering this continent
	int _bonusArmies = 0;
	//List of all territories belonging to the same Continent
	vector<Territory*> _territories;
	//For now the continents are not connected to eachother
	/*vector<Continent*> _adjacentContinents;*/
public:
#pragma region constructos
	Continent();//Default constructor, should not be used but here to avoid errors
	Continent(int id,string continentName);//Initializes the id and name of the continent
	Continent(const Continent& continent);
	Continent(int id,string continentName, int bonusArmies);//Initializes the id, name of the continent, and the bonusArmies
	Continent(int id,string continentName, int bonusArmies, vector<Territory*>* adjacentTerritories);//Initializes the id, name of the continent, the bonusArmies, and the vector of adjacent territories
	~Continent();//clears the territories vector
	friend ostream& operator<<(ostream&, const Continent&);
#pragma endregion
#pragma region methods
	Continent& operator=(const Continent&);
	bool setBonusArmies(int);//This method sets the value of the bonus armies, ensures the bonus is not negative
	int  getBonusArmies();//This method returns the value of the bonus armies
	int  continentSize();//This method returns the number of territories sharing the same continent
	int  getId();//Returns the id of the continent
	bool addTerritory(Territory*);//This method adds a terriotry to this continent making sure the territory is not null and it has a name
	string getContinentName();
	//I don't think the continents are supposed to be connected uncomment if they are suppose to
	//bool addBorder(Continent*);
	vector<Territory*>* getTerritories();//returns a lits of all the territories in the continent. Careful it contains pointers to the territories changes to territories will be applied to the territroy
#pragma endregion
};
ostream& operator<<(ostream& stream, const Continent& continent);
//---------------------------------------------------------------------------------------------------------------------------- MAP-------------------------------------------------------------------------------------------------------
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
	Map(int);//initializes the size of the map by passing the number of continents in the map
	Map(int, vector<Continent*>*);//initializes the size of the map by passing the number of continents in the map. Initializes the vector of continents
	~Map();//clears the continents and territories vecors and destroyes everything in the map(i.e territories and continents) ONLY THIS DESTRUCTOR HAS TO BE CALLED
#pragma endregion
#pragma region methods
	Map& operator=(const Map&);
	bool addContinent(Continent*);//add a continent to the list containing all the continents in the map. Makes sure its an acceptable continent
	bool addTerritory(Territory*);//add a territory to the list containing all the territories in the map. Makes sure its an acceptable territory
	bool validate();
	bool isConnected();
	bool checkTerritories();
	vector<Territory*>* getTerritories();// returns a list containing a copy of all the territories in the Map
	vector<Continent*>* getContinents();// returns a list containing a copy of all the continents in the Map
	Territory* getTerritoryById(int);//gets a territory by its id from the list of all territories. Be careful its a pointer
	Continent* getContinentById(int);//gets a continent by its id from the list of all continents. Be careful its a pointer
	int getMapSizeTerritory();//gets the size of the map by the number of territories in the map
	int getMapSizeContinent();//gets the size of the map by the number of continents in the map
	void territoryDFS(Territory* start, vector<bool>& visited);
	//For now I don't think this is necessary as I don't think the continents are connected
	//void continentDFS(Continent* start, map<Continent*, bool> visited);
#pragma endregion
};
