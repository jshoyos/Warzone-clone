// WarzonePart1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Map.h"
using namespace std;

int main()
{
	Continent* Argentina = new Continent(0,"Argentina", 4-1);
	Continent* Uruguay = new Continent(1,"Uruguay", 1-1);
	cout << *Argentina << endl;
	cout << *Uruguay << endl;
	Territory* Malvinas = new Territory(0,"Islas Malvinas", 1-1);
	Territory* Tierra_del_Fuego = new Territory(1,"Tierra_del_Fuego", 1-1);
	Territory* Santa_Cruz = new Territory(2,"Santa_Cruz", 1-1);
	Territory* Río_Negro = new Territory(3,"Río_Negro", 1-1);
	Territory* Neuquén = new Territory(4,"Neuquén", 1-1);

	Territory* Paysandú = new Territory(5,"Paysandú", 2-1);
	Territory* Maldonado = new Territory(6,"Maldonado", 2-1);
	Territory* Montevideo = new Territory(7,"Montevideo", 2-1);

	Map* map = new Map(2);
	map->addContinent(Argentina);
	map->addContinent(Uruguay);

	map->addTerritory(Malvinas);
	map->addTerritory(Tierra_del_Fuego);
	map->addTerritory(Santa_Cruz);
	map->addTerritory(Río_Negro);
	map->addTerritory(Neuquén);
	map->addTerritory(Paysandú);
	map->addTerritory(Maldonado);
	map->addTerritory(Montevideo);
	cout << "Countries in Continents" << endl;
	vector<Continent> temp = map->getContinents();
	for (int i = 0; i < temp.size(); i++) {
		cout << temp[i] << endl;
		vector<Territory> territories= *temp[i].getTerritories();
		for (int j = 0; j < territories.size(); j++) {
			cout << territories[j];
		}
		cout << endl;
	}
	cout << "Validating Map" << endl;
	bool isvalid=map->validate();
	cout << "map is valid: " << isvalid << endl;
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
