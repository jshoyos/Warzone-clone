#include <string>
#include <iostream>
#include <vector>

using namespace std;

#pragma once
class Order
{
	string _orderType;	//Since there are different types of orders, this variable will contain the specific type being referred to
public: 

	//constructors
	Order();
	Order(string);
	Order(const Order&);
	
	//methods
	friend ostream& operator << (ostream&, const Order&); //creating stream insertion operator

	string getOrderType(); //getter for _orderType since it is a private variable
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
	
	vector<Order*>* remove(vector<Order*>*, int);	//remove method for OrdersList class
	vector<Order*>* move(vector<Order*>*, int, int); //move method for OrdersList class
	bool queueOrder(Order*);	//method used to put an order into the list of orders
	friend ostream& operator << (ostream&, const OrdersList&);

#pragma endregion

};
ostream& operator << (ostream&, const OrdersList&);

//All the classes that correspond to an order
class Deploy :public Order {
public:
	Deploy(string);
	bool validate(vector<Order*>*);	//validate method for the deploy order
	void execute(vector<Order*>*);	//execute method for the deploy order

};
class Advance :public Order {
public:

	Advance(string);
	bool validate(vector<Order*>*);	//validate method for the advance order
	void execute(vector<Order*>*);	//execute method for the advance order

};
class Bomb :public Order {
public:

	Bomb(string);
	bool validate(vector<Order*>*);	//validate method for the bomb order
	void execute(vector<Order*>*);	//execute method for the bomb order

};
class Blockade :public Order {
public:

	Blockade(string);
	bool validate(vector<Order*>*);	//validate method for the blockade order
	void execute(vector<Order*>*);	//execute method for the blockade order

};
class Airlift :public Order {
public:

	Airlift(string);
	bool validate(vector<Order*>*);	//validate method for the airlift order
	void execute(vector<Order*>*);	//execute method for the airlift order

};
class Negotiate :public Order {
public:

	Negotiate(string);
	bool validate(vector<Order*>*);	//validate method for the negotiate order
	void execute(vector<Order*>*);	//execute method for the negotiate order

};