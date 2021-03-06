#include "Map.h"
#include <map>
#include <list>
#include <algorithm>
//--------------------------------------------------------------------------------------------------------------------MAP---------------------------------------------------------------------------------------------
Map::Map() :_numberOfContinents(0)
{
	//cout << "Creating a Default Map:" << endl;
}

Map::Map(const Map& map)
{
	cout << "Creating a Map Copy: " << endl;
	this->_numberOfContinents = map._numberOfContinents;
	for (auto continent : map._continents) {
		this->_continents.push_back(new Continent(*continent));
	}
	for (auto territory : map._territories) {
		this->_territories.push_back(new Territory(*territory));
	}
}
Map::Map(int numberOfContinents) : _numberOfContinents(numberOfContinents)
{
	//cout << "Creating a Map:" << endl;
	cout << "Number of continents in the map: " << numberOfContinents<<endl<<endl;
}

Map::Map(int numberOfContinents, vector<Continent*>* continents) : _numberOfContinents(numberOfContinents), _continents(*continents)
{
	//cout << "Creating a Map:" << endl;
	cout << "Number of continents in the map: " << _continents.size()<<endl;
}

Map::~Map()
{
	cout << "\n>>> Map is now deleted. System will exit." << endl;
	for (auto territory : _territories) {
		delete territory;
		territory = NULL;
	}
	for (auto continent : _continents) {
		delete continent;
		continent = NULL;
	}
	EXIT_FAILURE;
}

bool Map::validate()
{

	// Check if undirected graph is connected by doing DFS
	// wont mean anything if graph is not undirected
	//
	// I think you might have to do it for every node in the graph to ensure undirected
	if (!isConnected() && !checkTerritories())
	{
		return false;
	}
	return true;
}

Map& Map::operator=(const Map& map)
{
	return *(new Map(map));
}

bool Map::checkTerritories()
{

// 	// check for empty continents

	for (Continent* continent : _continents) {
		if (continent->continentSize() == 0)
		{
			return false;
		}
	 }

// 	// 1. put all territories in continents into a collection
// 	// 2. take unique elements
// 	// 3. if territories size != unique elements, there is an issue
	list<string> territoriesNames;

	for (auto continent : _continents) {
		vector<Territory*>* temp = continent->getTerritories();
		for (auto territory : *temp) {
			territoriesNames.push_back(territory->getTerritoryName());
		}
	}
	int initialListSize = territoriesNames.size();
	territoriesNames.sort();
	territoriesNames.unique();


	if (territoriesNames.size() != initialListSize) {
		cout << ">>> Map_Error: A duplicate territory has been detected.\n>>> Map will be deleted and system will exit. " << endl;
		return false;
	}
	return true;
}

bool Map::isConnected()
{

	int continents_size = getMapSizeContinent();
	int territories_size = getMapSizeTerritory();

	for (int i = 0; i < territories_size; ++i)
	{

		Territory* root_node = getTerritoryById(i);
		vector<bool> visited_territories(territories_size, false);

		territoryDFS(root_node, visited_territories);

		for (bool vis : visited_territories)
		{
			if (!vis)
			{
				cout << ">>> MAP_DFS_Error: A territory could not be reached! \n>>> Map is not a connected graph. \n>>> Map will be deleted and system will exit." << endl;
				exit(1);
				return false;
			}
		}
	}

	cout << "Success! The map is a fully connected graph." << endl;
	return true;
}

// version using unique id
void Map::territoryDFS(Territory* startNode, vector<bool>& visited)
{
	int node_id = startNode->getId();
	visited[node_id] = true;

	for (Territory* adj_node : *(startNode->getAdjacent()))
	{
		int adj_id = adj_node->getId();
		if (!visited[adj_id])
		{
			territoryDFS(adj_node, visited);
		}
	}
}

bool Map::addContinent(Continent* continent)
{
	if (continent != NULL)
	{
		_continents.push_back(continent);
		//cout << "Continent " << continent->getContinentName() << " has been added. " << endl;
		return true;
	}
	return false;
}

bool Map::addTerritory(Territory* territory)
{
	//cout << "Territory " << territory->getTerritoryName() << endl;
	if (territory != NULL && territory->getTerritoryName() != "")
	{
		
		_territories.push_back(territory);
		_continents[territory->getContinent()]->addTerritory(territory);
		return true;
	}
	return false;
}

vector<Territory*>* Map::getTerritories()
{
	return &_territories;
}

vector<Continent*>* Map::getContinents()
{
	return &_continents;
}

Territory* Map::getTerritoryById(int id)
{
	return _territories[id];
}

Continent* Map::getContinentById(int id)
{
	return _continents[id];
}

int Map::getMapSizeContinent()
{
	return static_cast<int>(_continents.size());
}

int Map::getMapSizeTerritory()
{
	return static_cast<int>(_territories.size());
}
//---------------------------------------------------------------------------------------------------------TERRITORY--------------------------------------------------------------------------------------------------------------------
Territory::Territory() :_id(),_territoryName(), _continent()
{
	cout << "Creating a Default Territory:" << endl;
}

Territory::Territory(const Territory& territory)
{
	this->_continent = territory._continent;
	this->_territoryName = territory._territoryName;
	this->_armies = territory._armies;
	this->_owner = new Player(*(territory._owner));
	for (auto adjNode : territory._adjacentTerritories) {
		this->_adjacentTerritories.push_back(new Territory(*adjNode));
	}
}


Territory& Territory::operator=(const Territory& territory)
{
	cout << "Creating a Territory Copy:" << endl;
	return *(new Territory(territory));
}

Territory::Territory(int id, string territoryName, int continent) : _id(id), _territoryName(territoryName), _continent(continent)
{
	cout << "\n>>> Creating a new territory:" << endl;
	cout << "ID: " << id << ", Name: " << territoryName << ", Continent: " << continent << endl;
}

Territory::Territory(int id,string territoryName, int continent, vector<Territory*>* adjacentTerritories) :_id(id), _territoryName(territoryName), _continent(continent), _adjacentTerritories(*adjacentTerritories)
{
	cout << ">>> Creating a new territory:" << endl;
	cout << "ID: " << id << ", Name: " << territoryName << ", Continent: " << continent <<"\n"<< territoryName <<" shares borders with "<<adjacentTerritories->size()<<" other territories." << endl;
}

Territory::~Territory()
{
	cout << "Destroying Territory: " << _territoryName << endl;
	_adjacentTerritories.erase(_adjacentTerritories.begin(),_adjacentTerritories.end());
}

bool Territory::setOwner(Player* owner)
{
	_owner = owner;
	return true;
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


Player* Territory::getOwner()
{
	//TODO: once the player class has a copy constructor return a copy of the player
	return _owner;
	//return new Player(*_owner);
}

int Territory::getContinent()
{
	return _continent;
}

vector<Territory*>* Territory::getAdjacent()
{
	return &_adjacentTerritories;
}

int Territory::getId()
{
	return _id;
}

string Territory::getTerritoryName()
{
	return string(_territoryName);
}

bool Territory::addBorder(Territory* territory)
{
	if (territory != NULL && territory->_territoryName != "")
	{
		_adjacentTerritories.push_back(territory);
		cout << "A link from " << this->getTerritoryName() << " and " << territory->getTerritoryName() << " has been added." << endl;
		return true;
	}
	return false;
}

ostream& operator<< (ostream& stream, const Territory& territory) {
	if (territory._owner != NULL) {
		return stream << territory._territoryName << " currently has " << territory._armies << " armies owned by " << territory._owner->getName() << "." << endl;
	}
	else {
		return stream << territory._territoryName << " currently belongs to no one." << endl;
	}
}
//------------------------------------------------------------------------------------------------CONTINENT-----------------------------------------------------------------------------------------------------------------------------------------
Continent::Continent() :_continentName(), _bonusArmies()
{
	cout << "Creating default continent:" << endl;
}

Continent::Continent(const Continent& continent)
{
	cout << "Creating a Continent Copy:" << endl;
	this->_continentName = continent._continentName;
	this->_bonusArmies = continent._bonusArmies;
	for (auto adjNode : continent._territories) {
		this->_territories.push_back(new Territory(*adjNode));
	}
	//For now there will not be any link between continents
	/*for (auto adjNode : continent._adjacentContinents) {
		this->_adjacentContinents.push_back(new Continent(*adjNode));
	}*/
}

Continent::Continent(int id,string continentName, int bonusArmies) :_id(id),_continentName(continentName), _bonusArmies(bonusArmies)
{
	cout << ">>> Creating a new continent:" << endl;
	cout << "ID: " << id << ", Name: " << continentName << ", Bonus Armies: " << bonusArmies << endl;
}

Continent::Continent(int id,string continentName, int bonusArmies, vector<Territory*>* territories) :_id(id), _continentName(continentName), _bonusArmies(bonusArmies), _territories(*territories)
{
	cout << ">>> Creating a new continent:" << endl;
	cout << "ID: " << id << ", Name: " << continentName << ", Bonus Armies: " << bonusArmies <<"\n"<< continentName <<" contains "<<territories->size()<<" territories."<< endl;
}

Continent::~Continent()
{
	cout << "Destroying continent: " << _continentName << endl;
	_territories.erase(_territories.begin(), _territories.end());
	//I don't think it should destroy the territories as each territory will call its own destructor
	/*for (auto territory : _territories) {
		delete territory;
		territory = NULL;
	}*/
}

Continent& Continent::operator=(const Continent& continent)
{
	cout << "Creating a continent copy:" << endl;
	return *(new Continent(continent));
}

Continent::Continent(int id, string continentName) : _id(id), _continentName(continentName)
{
	cout << ">>> Creating a new continent:" << endl;
	cout << "ID: " << id << ", Name: " << continentName << endl;
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

int Continent::continentSize()
{
	return static_cast<int>(_territories.size());
}
int Continent::getId()
{
	return _id;
}

bool Continent::addTerritory(Territory* territory)
{
	if (territory != NULL && territory->getTerritoryName() != "")
	{
		// territory->getContinent() != 0
		_territories.push_back(territory);
		//cout << "Territory " << territory->getTerritoryName() << " has been added." << endl;
		return true;
	}
	return false;
}
string Continent::getContinentName()
{
	return _continentName;
}
ostream& operator<<(ostream& stream, const Continent& continent) {
	return stream << "Conquering " << continent._continentName << " gives you " << continent._bonusArmies << " bonus armies" << endl;
}
vector<Territory*>* Continent::getTerritories()
{
	return &_territories;
}
