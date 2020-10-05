#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

using namespace std;

class Territory;

class Player
{
	//Player id //not needed
	static int _id;
	//Player's name
	string _name = "";
	//The list of orders made by a player
	vector<Orders*> _orderList;
	//The list of cards given to a player
	vector<Cards*> _hand;
	//List of the Player's Territories
	vector<Territory*> _territoryList;

public:
	//constructors
	Player();
	~Player();
	Player(const Player&);
	Player(string);
	Player(string, vector<Orders*>, vector<Cards*>, vector<Territory*>);

	//methods
	Player& operator= (const Player&);
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	friend ostream& operator<< (ostream&, const Player&);
	void issueOrder();

	//getters
	string getName();
	vector<Orders*> getOrderList();
	vector<Cards*> getHand();
	vector<Territory*> getTerritoryList();

	//setters
	bool setName(string);
	bool addOrder(Orders*);
	bool addCard(Cards*);
	bool conquerTerritory(Territory*);

};

