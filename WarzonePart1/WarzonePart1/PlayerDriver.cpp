#include <iostream>
#include "Player.h"
using namespace std;

int main()
{
	//--------------------WElCOME TO THE PLAYER DRIVER-----------------------------------\\

	string name;
	cout << "Enter Player name" << endl;
	cin >> name; 
	cout << endl;

	cout << "Hi "<< name << ", welcome to warzone!"<< endl;
	Player* player1 = new Player(name);			//declaring new pointer to player
	
	//creating territory list for player1
	Territory* Malvinas = new Territory(0, "Islas Malvinas", 0);
	Territory* Tierra_del_Fuego = new Territory(1, "Tierra_del_Fuego", 0);
	Territory* Santa_Cruz = new Territory(2, "Santa_Cruz", 0);
	Territory* Río_Negro = new Territory(3, "Río_Negro", 0);
	Territory* Neuquén = new Territory(4, "Neuquén", 0);
	//Player 1 conquers territories inorder to own them (stored in players territory list variable)
	player1->conquerTerritory(Malvinas);
	player1->conquerTerritory(Tierra_del_Fuego);
	player1->conquerTerritory(Santa_Cruz);
	player1->conquerTerritory(Río_Negro);
	player1->conquerTerritory(Neuquén);

	cout << endl << *player1 << endl;
	//List of territories for player to defend
	vector<Territory*> defendTerr = *(player1->toDefend());
	cout << "---------------------------------------------------------------------" << endl;
	cout << "Here is a list of territories to Defend:" << endl;
	cout << endl;

	//displays territories for player 1 to defend 
	for (int i = 0; i < defendTerr.size();i++) {
		cout << " -" << *defendTerr[i];
		cout << endl;
	}

	//List of territories for player to attack
	vector<Territory*> attackTerr = *(player1->toAttack());

	cout << "---------------------------------------------------------------------" << endl;
	cout << "Here is a list of territories to attack:" << endl;
	cout << endl;

	//displays territories for player 1 to defend 
	for (int i = 0;i < attackTerr.size();i++) {
		cout<< " -" << *attackTerr[i] <<endl;
	}

	cout << "---------------------------------------------------------------------" << endl;
	cout << name << " issues an order!"<<endl;
	cout << endl;
	
	//player 1 issues new order based on order class
	player1->issueOrder();
	

	//Deletion of pointers to clear the memory.

	delete player1; player1 = NULL;
	//delete defendTerr; defendTerr = NULL;
	//delete attackTerr; attackTerr = NULL;
	delete Malvinas; Malvinas = NULL;
	delete Tierra_del_Fuego; Tierra_del_Fuego = NULL;
	delete Santa_Cruz; Santa_Cruz = NULL;
	delete Río_Negro; Río_Negro = NULL;
	delete Neuquén; Neuquén = NULL; 
	
	return 0;
}