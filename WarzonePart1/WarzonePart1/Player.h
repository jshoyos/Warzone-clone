#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

using namespace std;

class Territory;
class Cards;

class Player
{
	//Player id //not needed
	static int _id;
	//Player's name
	string _name = "";
	//The list of orders made by a player
	vector<Order*> _orderList;
	//The list of cards given to a player
	vector<Cards*> _hand;
	//List of the Player's Territories
	vector<Territory*> _territoryList;

public:
	//constructors
	Player();						//default constructor 
	~Player();						//destructor
	Player(const Player&);			//copy constructor
	Player(string);					//parameterized constructor accepting a string (name)
	Player(string, vector<Order*>*, vector<Cards*>*, vector<Territory*>*); //parameterized connstructor 

	//methods
	Player& operator= (const Player&);	//Overwritting assign operator
	friend ostream& operator<< (ostream&, const Player&);	//Overloading of string operator
	vector<Territory*>* toDefend();		//toDefend() method for a player
	vector<Territory*>* toAttack();		//toAttack() method for a player
	void issueOrder();					//issueOrder() method for a player

	//getters
	string getName();
	vector<Order*>* getOrderList();
	vector<Cards*>* getHand();
	vector<Territory*>* getTerritoryList();

	//setters
	bool setName(string);
	bool addOrder(Order*);
	bool addCard(Cards*);
	bool conquerTerritory(Territory*);
};

