//#include <iostream>
//#include "Player.h"
//using namespace std;
//
//int main()
//{
//	//--------------------WElCOME TO THE PLAYER DRIVER-----------------------------------\\
//	//creating deck for the game
//	cout << "Lets first create a deck of cards for the game." << endl;
//	Deck myDeck = Deck(20);
//	Card card_drawn;
//	string name;
//	cout << endl <<"Enter Player name" << endl;
//	cin >> name; 
//	cout << endl;
//
//	cout << "Hi "<< name << ", welcome to warzone!"<< endl;
//	Player* player1 = new Player(name);			//declaring new pointer to player
//	cout << endl << *player1 << endl;
//	cout << player1->getName() << " receives initial territories, draws 5 cards. and issues 4 orders" << endl;
//
//
//	cout << "---------------------------------------------------------------------" << endl;
//	//creating territory list for player1
//	Territory* Malvinas = new Territory(0, "Islas Malvinas", 0);
//	Territory* Tierra_del_Fuego = new Territory(1, "Tierra_del_Fuego", 0);
//	Territory* Santa_Cruz = new Territory(2, "Santa_Cruz", 0);
//	Territory* Río_Negro = new Territory(3, "Río_Negro", 0);
//	Territory* Neuquén = new Territory(4, "Neuquén", 0);
//	//Player 1 conquers territories inorder to own them (stored in players territory list variable)
//	player1->conquerTerritory(Malvinas);
//	player1->conquerTerritory(Tierra_del_Fuego);
//	player1->conquerTerritory(Santa_Cruz);
//	player1->conquerTerritory(Río_Negro);
//	player1->conquerTerritory(Neuquén);
//	cout << "---------------------------------------------------------------------" << endl;
<<<<<<< HEAD
//	cout << "TESTETSTETSTETSTEST" << endl;
//	player1->displayTerrList();
//	cout << "remove terr"<<endl;
//	player1->removeTerritory(Malvinas);
//	player1->displayTerrList();
//
//	////creating orders for player 1
//	//Order* order1 = dynamic_cast<Order*>(new Deploy("deploy"));
//	//Bomb* order2 = new Bomb("bomb");
//	//Airlift* order3 = new Airlift("airlift");
//	//Negotiate* order4 = new Negotiate("negotiate");
//
//	//player1->addOrder(order1);
//	//player1->addOrder(order2);
//	//player1->addOrder(order3);
//	//player1->addOrder(order4);
//
//	////creating hand of cards for a player
//	//
//	//for (int i = 0; i < 5; i++) {
//	//	card_drawn = myDeck.draw();
//	//	player1->addCard(card_drawn);
//	//}
//
//
//	//cout << endl << *player1 << endl;
//	////List of territories for player to defend
//	//vector<Territory*> defendTerr = *(player1->toDefend());
//	//cout << "---------------------------------------------------------------------" << endl;
//	//cout << "Here is a list of territories to Defend:" << endl;
//	//cout << endl;
//
//	////displays territories for player 1 to defend 
//	//for (int i = 0; i < defendTerr.size();i++) {
//	//	cout << " -" << *defendTerr[i];
//	//	cout << endl;
//	//}
//	//cout << "---------------------------------------------------------------------" << endl;
//	////List of territories for player to attack
//	//vector<Territory*> attackTerr = *(player1->toAttack());
//
//	//cout << "---------------------------------------------------------------------" << endl;
//	//cout << "Here is a list of territories to attack:" << endl;
//	//cout << endl;
//
//	////displays territories for player 1 to defend 
//	//for (int i = 0;i < attackTerr.size();i++) {
//	//	cout<< " -" << *attackTerr[i] <<endl;
//	//}
//
//	//cout << "---------------------------------------------------------------------" << endl;
//	//cout << endl << name << " issues a new order: \"create a blockade!\""<<endl;
//	//cout << endl;
//	//
//	////player 1 issues new order based on order class
//	//player1->issueOrder("blockade");
//	////displays player's list of orders
//	//cout << "List of orders issued by " << player1->getName()<< ": ";
//	//cout << endl << *player1->getOrderList() << endl;
//	//cout << "---------------------------------------------------------------------";
//	//cout << endl << *player1 << endl;
//	//cout << endl << "Thank you "<<player1->getName()<< " for playing Warzone! " << endl;
//	//cout << "---------------------------------------------------------------------" << endl;
=======
//
//
//	//creating orders for player 1
//	Order* order1 = dynamic_cast<Order*>(new Deploy("deploy"));
//	Bomb* order2 = new Bomb("bomb");
//	Airlift* order3 = new Airlift("airlift");
//	Negotiate* order4 = new Negotiate("negotiate");
//
//	player1->addOrder(order1);
//	player1->addOrder(order2);
//	player1->addOrder(order3);
//	player1->addOrder(order4);
//
//	//creating hand of cards for a player
//	
//	for (int i = 0; i < 5; i++) {
//		card_drawn = myDeck.draw();
//		player1->addCard(card_drawn);
//	}
//
//
//	cout << endl << *player1 << endl;
//	//List of territories for player to defend
//	vector<Territory*> defendTerr = *(player1->toDefend());
//	cout << "---------------------------------------------------------------------" << endl;
//	cout << "Here is a list of territories to Defend:" << endl;
//	cout << endl;
//
//	//displays territories for player 1 to defend 
//	for (int i = 0; i < defendTerr.size();i++) {
//		cout << " -" << *defendTerr[i];
//		cout << endl;
//	}
//	cout << "---------------------------------------------------------------------" << endl;
//	//List of territories for player to attack
//	vector<Territory*> attackTerr = *(player1->toAttack());
//
//	cout << "---------------------------------------------------------------------" << endl;
//	cout << "Here is a list of territories to attack:" << endl;
//	cout << endl;
//
//	//displays territories for player 1 to defend 
//	for (int i = 0;i < attackTerr.size();i++) {
//		cout<< " -" << *attackTerr[i] <<endl;
//	}
//
//	cout << "---------------------------------------------------------------------" << endl;
//	cout << endl << name << " issues a new order: \"create a blockade!\""<<endl;
//	cout << endl;
//	
//	//player 1 issues new order based on order class
//	player1->issueOrder("blockade");
//	//displays player's list of orders
//	cout << "List of orders issued by " << player1->getName()<< ": ";
//	cout << endl << *player1->getOrderList() << endl;
//	cout << "---------------------------------------------------------------------";
//	cout << endl << *player1 << endl;
//	cout << endl << "Thank you "<<player1->getName()<< " for playing Warzone! " << endl;
//	cout << "---------------------------------------------------------------------" << endl;
>>>>>>> 350fc43d0c30d5e950e9c23e2edee6af9f372155
//	
//	
//
//	//Deletion of pointers to clear the memory.
//	delete Malvinas; Malvinas = NULL;
//	delete Tierra_del_Fuego; Tierra_del_Fuego = NULL;
//	delete Santa_Cruz; Santa_Cruz = NULL;
//	delete Río_Negro; Río_Negro = NULL;
//	delete Neuquén; Neuquén = NULL; 
//	
//	delete player1; player1 = NULL;
//
//	return 0;
//}