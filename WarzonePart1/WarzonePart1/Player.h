#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

using namespace std;

class Territory;
class Order;
class OrdersList;

class Player
{
	//Player id //not needed
	static int _id;
	//Player's name
	string _name = "";
	//The list of orders made by a player
	OrdersList *_orderList;
	//The list of cards given to a player
	Hand *_hand;
	//List of the Player's Territories
	vector<Territory*> _territoryList;

public:
	//constructors
	Player();						//default constructor 
	~Player();						//destructor
	Player(const Player&);			//copy constructor
	Player(string);					//parameterized constructor accepting a string (name)
	Player(string, OrdersList*, Hand*, vector<Territory*>*); //parameterized constructor 

	//methods
	Player& operator= (const Player&);	//Overwritting assign operator
	friend ostream& operator<< (ostream&, const Player&);	//Overloading of string operator
	vector<Territory*>* toDefend();		//toDefend() method for a player
	vector<Territory*>* toAttack();		//toAttack() method for a player
	void issueOrder(string);					//issueOrder() method for a player

	//getters
	string getName();
	OrdersList* getOrderList();
	Hand* getHand();
	vector<Territory*>* getTerritoryList();

	//setters
	bool setName(string);
	bool addOrder(Order*);
	void addCard(Card);
	bool conquerTerritory(Territory*);
};

