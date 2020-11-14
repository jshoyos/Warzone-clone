#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

using namespace std;

class OrdersList;
class Territory;
class Order;
class Hand;
class Card;

class Player
{
	//Player id //not needed
	static int _id;
	//Player's name
	string _name = "";
	//The list of orders made by a player
	OrdersList* _orderList;
	//The list of cards given to a player
	Hand* _hand;
	//List of the Player's Territories
	vector<Territory*> _territoryList;
<<<<<<< HEAD
	//Number of armies for a player
=======
	//Number of Armies in the Player's Reinforcement Pool
>>>>>>> 350fc43d0c30d5e950e9c23e2edee6af9f372155
	int _reinforcementPool;

public:
	//constructors
	Player();						//default constructor 
	~Player();						//destructor
	Player(const Player&);			//copy constructor
	Player(string);					//parameterized constructor accepting a string (name)
	Player(string,int);				//parameterized constructor accepting a string (name), and int (num)
	Player(string, OrdersList*, Hand*, vector<Territory*>*,int); //parameterized constructor 

	//methods
	Player& operator= (const Player&);	//Overwritting assign operator
	friend ostream& operator<< (ostream&, const Player&);	//Overloading of string operator
	vector<Territory*>* toDefend();		//toDefend() method for a player
	vector<Territory*>* toAttack();		//toAttack() method for a player
<<<<<<< HEAD
	void issueOrder(string , Player*, Player* ,Territory*,Territory*, int );			//issueOrder() method for a player
	bool removeTerritory(Territory*);	//removes territory from player's territory list
	void displayTerrList();				//displays the names of territories from a player's territory list 
	bool removeCardFromHand(Card*);		// removes a card from the a hand

=======
	void issueOrder(string);			//issueOrder() method for a player
>>>>>>> 350fc43d0c30d5e950e9c23e2edee6af9f372155

	//getters
	string getName();
	OrdersList* getOrderList();
	Hand* getHand();
	vector<Territory*>* getTerritoryList();
	int getReinforcementPool();
<<<<<<< HEAD
=======

	int getID();         //d_rivi
>>>>>>> 350fc43d0c30d5e950e9c23e2edee6af9f372155

	//setters
	bool setName(string);
	bool setOrderList(OrdersList*);
	bool addOrder(Order*);
	void addCard(Card*);
	bool conquerTerritory(Territory*);
	bool setReinforcementPool(int);
<<<<<<< HEAD
=======

	void setID(int new_id);        //d_rivi
>>>>>>> 350fc43d0c30d5e950e9c23e2edee6af9f372155
};

