#include <iostream>
#include "Player.h"
using namespace std;

int main()
{
	cout << "Enter Player name" << endl;
	Player* player1 = new Player("Noah");

	Territory* Malvinas = new Territory(0, "Islas Malvinas", 0);
	Territory* Tierra_del_Fuego = new Territory(1, "Tierra_del_Fuego", 0);
	Territory* Santa_Cruz = new Territory(2, "Santa_Cruz", 0);
	Territory* R�o_Negro = new Territory(3, "R�o_Negro", 0);
	Territory* Neuqu�n = new Territory(4, "Neuqu�n", 0);

	vector<Territory*> terrList;
		
	terrList.push_back(Malvinas);
	terrList.push_back(Tierra_del_Fuego);
	terrList.push_back(Santa_Cruz);
	terrList.push_back(R�o_Negro);
	terrList.push_back(Neuqu�n);

	//Player* player2 = new Player("John", vector<Orders*>, vector<Cards*>, terrList);

	player1->issueOrder();
	//player2->toAttack();
	//player2->toDefend();
	

	return 0;
}