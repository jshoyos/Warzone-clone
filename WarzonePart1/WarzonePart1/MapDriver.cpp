// WarzonePart1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Map.h"
#include "MapLoader.h"
using namespace std;

int main()
{
	Continent* Argentina = new Continent(0,"Argentina", 4-1);
	Continent* Uruguay = new Continent(1,"Uruguay", 1-1);
	cout << *Argentina << endl;
	cout << *Uruguay << endl;
	Territory* Malvinas = new Territory(0,"Islas Malvinas", 0);
	Territory* Tierra_del_Fuego = new Territory(1,"Tierra_del_Fuego", 0);
	Territory* Santa_Cruz = new Territory(2,"Santa_Cruz", 0);
	Territory* Rio_Negro = new Territory(3,"Río_Negro", 0);
	Territory* Neuquen = new Territory(4,"Neuquén", 0);

	Territory* Paysandu = new Territory(5,"Paysandú", 1);
	Territory* Maldonado = new Territory(6,"Maldonado", 1);
	Territory* Montevideo = new Territory(7,"Montevideo", 1);
	Territory* Shapeshifter = new Territory(0, "Islas Malvinas", 1);

	Map* map = new Map(2);
	map->addContinent(Argentina);
	map->addContinent(Uruguay);

	map->addTerritory(Malvinas);
	map->addTerritory(Tierra_del_Fuego);
	map->addTerritory(Santa_Cruz);
	map->addTerritory(Rio_Negro);
	map->addTerritory(Neuquen);
	map->addTerritory(Paysandu);
	map->addTerritory(Maldonado);
	map->addTerritory(Montevideo);
	map->addTerritory(Shapeshifter);

	cout <<endl<< "Countries in Continents (this will make a copy of each continent)" << endl;
	vector<Continent*> continent = *(map->getContinents());
	for (int i = 0; i < continent.size(); i++) {
		cout << *continent[i]<<endl;
		vector<Territory*> territories = *(continent[i]->getTerritories());
		cout << "Printing all territories in " << continent[i]->getContinentName() << endl;
		for (int j = 0; j < territories.size(); j++) {
			cout << *territories[j];
		}
		cout << endl;
	}
	cout <<endl<< "Validating Map" << endl;
	map->validate();

	cout << "THANOS HAS SNAPPED HIS FINGERS!!!!!!" << endl;
	delete map ;map = NULL;
	Malvinas=NULL;
	Tierra_del_Fuego=NULL;
	Santa_Cruz=NULL;
	Rio_Negro=NULL;
	Neuquen=NULL;
	Paysandu=NULL;
	Maldonado=NULL;
	Montevideo=NULL;
	Argentina=NULL;
	Uruguay=NULL;

	//----------------------------------------------------------------SECOND TEST----------------------------------------------------------------------------------------
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!SECOND TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	MapLoader loader = MapLoader("solar.map");
	map = loader.createMap();
	map->validate();
	delete map; map = NULL;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file 
