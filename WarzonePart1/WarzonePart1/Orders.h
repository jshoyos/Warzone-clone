#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include "GameObservers.h"

class Player;
class Territory;
using namespace std;

class Order
{
	Player* _p;
	Territory* _target;
protected:
	Publisher phasePublisher;
	GameStatisticsObserver* statsObserver;

public: 

	//constructors
	Order();
	Order(const Order&);
	Order(Player*);
	Order(Player*, Territory*);
	
	//methods
	friend ostream& operator << (ostream&, const Order&); //creating stream insertion operator

	virtual void execute() = 0;

	//getters
	Player* getPlayer();
	Territory* getTarget();

	//setters
	bool setPlayer(Player* p);
	bool setTarget(Territory* target);

};

ostream& operator << (ostream&, const Order&);

class OrdersList
{
	int _size = 0;

private :
		vector<Order*> _ordersList;	//This is the list of orders where all the individual orders will be stored
public:
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

	//getter
	vector<Order*> getOrdersList();

#pragma endregion

};
ostream& operator << (ostream&, const OrdersList&);

//All the classes that correspond to an order
class Deploy :public Order {
	int _numberOfArmies;
public:
	Deploy();
	Deploy(const Deploy&);
	Deploy(Player*, Territory*, int);
	bool validate();	//validate method for the deploy order
	void execute();	//execute method for the deploy order

	//getter
	int getNumberOfArmies();

	//setter
	bool setNumberOfArmies(int numberOfArmies);
};
class Advance :public Order {
	int _numberOfArmies;
	Territory* _source;
public:
	Advance();
	Advance(const Advance&);
	Advance(Player*, Territory*, Territory*, int);
	bool validate();	//validate method for the advance order
	void execute();	//execute method for the advance order

	//getters
	Territory* getSource();
	int getNumberOfArmies();

	//setters
	bool setSource(Territory* source);
	bool setNumberOfArmies(int numberOfArmies);

};
class Bomb :public Order {
public:

	Bomb();
	Bomb(const Bomb&);
	Bomb(Player*, Territory*);
	bool validate();	//validate method for the bomb order
	void execute();	//execute method for the bomb order

};
class Blockade :public Order {
public:

	Blockade();
	Blockade(const Blockade&);
	Blockade(Player*, Territory*);
	bool validate();	//validate method for the blockade order
	void execute();	//execute method for the blockade order

};
class Airlift :public Order {
	int _numberOfArmies;
	Territory* _source;
public:

	Airlift();
	Airlift(const Airlift&);
	Airlift(Player*, Territory*, Territory*, int);
	bool validate();	//validate method for the airlift order
	void execute();	//execute method for the airlift order

	//getter
	Territory* getSource();
	int getNumberOfArmies();

	//setter
	bool setSource(Territory* source);
	bool setNumberOfArmies(int numberOfArmies);

};
class Negotiate :public Order {
	Player* _p2;
public:

	Negotiate();
	Negotiate(const Negotiate&);
	Negotiate(Player*, Player*);
	bool validate();	//validate method for the negotiate order
	void execute();	//execute method for the negotiate order

	//getter
	Player* getPlayer2();
};