#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Player.h"

class Player;
class Territory;
using namespace std;

class Order
{
	Player* _p;
	Territory* _target;
	int _numberOfArmies;

public: 

	//constructors
	Order();
	Order(const Order&);
	Order(Player*);
	Order(Player*, Territory*, int);
	
	//methods
	friend ostream& operator << (ostream&, const Order&); //creating stream insertion operator

	virtual void execute() = 0;

	//getters
	Player* getPlayer();
	Territory* getTarget();
	int getNumberOfArmies();

	//setters
	bool setPlayer(Player* p);
	bool setTarget(Territory* target);
	bool setNumberOfArmies(int numberOfArmies);

};

ostream& operator << (ostream&, const Order&);

class OrdersList
{
	int _size = 0;
public:
	vector<Order*> _ordersList;	//This is the list of orders where all the individual orders will be stored
#pragma region constructors
	OrdersList();
	OrdersList(int);
	OrdersList(const OrdersList&);
	~OrdersList();//clears the adjacent order vector

#pragma endregion
#pragma region methods 
	
	void remove(int);	//remove method for OrdersList class
	void move(int, int); //move method for OrdersList class
	bool queueOrder(Order*);	//method used to put an order into the list of orders
	friend ostream& operator << (ostream&, const OrdersList&);

#pragma endregion

};
ostream& operator << (ostream&, const OrdersList&);

//All the classes that correspond to an order
class Deploy :public Order {

public:
	Deploy();
	Deploy(const Deploy&);
	Deploy(Player*, Territory*, int);
	bool validate();	//validate method for the deploy order
	void execute();	//execute method for the deploy order

};
class Advance :public Order {
	Territory* _source;
public:
	Advance();
	Advance(const Advance&);
	Advance(Player*, Territory*, Territory*, int);
	bool validate();	//validate method for the advance order
	void execute();	//execute method for the advance order

	//getter
	Territory* getSource();

	//setter
	bool setSource(Territory* source);

};
class Bomb :public Order {
public:

	Bomb();
	Bomb(const Bomb&);
	Bomb(Player*, Territory*, int);
	bool validate();	//validate method for the bomb order
	void execute();	//execute method for the bomb order

};
class Blockade :public Order {
public:

	Blockade();
	Blockade(const Blockade&);
	Blockade(Player*, Territory*, int);
	bool validate();	//validate method for the blockade order
	void execute();	//execute method for the blockade order

};
class Airlift :public Order {
	Territory* _source;
public:

	Airlift();
	Airlift(const Airlift&);
	Airlift(Player*, Territory*, Territory*, int);
	bool validate();	//validate method for the airlift order
	void execute();	//execute method for the airlift order

	//getter
	Territory* getSource();

	//setter
	bool setSource(Territory* source);

};
class Negotiate :public Order {
	Player* _p2;
public:

	Negotiate();
	Negotiate(const Negotiate&);
	Negotiate(Player*, Player*);
	bool validate();	//validate method for the negotiate order
	void execute();	//execute method for the negotiate order

};