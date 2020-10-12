#include "Orders.h"
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


//Default constructor for Order
Order::Order()
{
}

//Parameterized constructor for Order
Order::Order(string orderName) : _orderType(orderName)
{
}

//Copy constructor for Order
Order::Order(const Order&)
{
}

//GET method for orderType variable
string Order::getOrderType(){
	return _orderType;
}
//Insertion stream operator
ostream& operator<<(ostream& stream, const Order& order)
{
	string output = "";
	return stream << order._orderType<< endl;
	

}

//Another insertion stream operator for the OrdersList class
ostream& operator<<(ostream& stream, const OrdersList& list)
{
	string output = "";
	for(int i=0; i < list._ordersList.size(); i++)
	{
		output = output + list._ordersList[i]->getOrderType() + " ";
	}
	return stream << output << endl;
}

Deploy::Deploy(string type):Order(type)
{

}

//validate method for the deploy order
bool Deploy::validate(vector<Order*>* list)
{
	if(list->size()>0)
	{
		return true;
	}
	else
	{
		cout << "Validation failed, no orders have been added to the list" << endl;
		return false;
	}
}
//execute method for the deploy order
void Deploy::execute(vector<Order*>* list)
{
	if(validate(list))
	{
		cout << "Deploying armies" << endl;
	}
}

Advance::Advance(string type) :Order(type)
{

}
//validate method for the advance order
bool Advance::validate(vector<Order*>* list)
{
	if (list->size() > 0)
	{
		return true;
	}
	else
	{
		cout << "Validation failed, no orders have been added to the list" << endl;
		return false;
	}
}
//execute method for the advance order
void Advance::execute(vector<Order*>* list)
{
	if (validate(list))
	{
		cout << "Advancing armies" << endl;
	}
}

Bomb::Bomb(string type) :Order(type)
{

}
//validate method for the bomb order
bool Bomb::validate(vector<Order*>* list)
{
	if (list->size() > 0)
	{
		return true;
	}
	else
	{
		cout << "Validation failed, no orders have been added to the list" << endl;
		return false;
	}
}
//execute method for the bomb order
void Bomb::execute(vector<Order*>* list)
{
	if (validate(list))
	{
		cout << "Bombing territory" << endl;
	}
}

Blockade::Blockade(string type) :Order(type)
{

}
//validate method for the blockade order
bool Blockade::validate(vector<Order*>* list)
{
	if (list->size() > 0)
	{
		return true;
	}
	else
	{
		cout << "Validation failed, no orders have been added to the list" << endl;
		return false;
	}
}
//execute method for the blockade order
void Blockade::execute(vector<Order*>* list)
{
	if (validate(list))
	{
		cout << "Creating blockade" << endl;
	}
}

Airlift::Airlift(string type) :Order(type)
{

}
//validate method for the airlift order
bool Airlift::validate(vector<Order*>* list)
{
	if (list->size() > 0)
	{
		return true;
	}
	else
	{
		cout << "Validation failed, no orders have been added to the list" << endl;
		return false;
	}
}
//execute method for the airlift order
void Airlift::execute(vector<Order*>* list)
{
	if (validate(list))
	{
		cout << "Air lifting armies" << endl;
	}
}

Negotiate::Negotiate(string type) :Order(type)
{

}
//validate method for the negotiate order
bool Negotiate::validate(vector<Order*>* list)
{
	if (list->size() > 0)
	{
		return true;
	}
	else 
	{
		cout << "Validation failed, no orders have been added to the list" << endl;
		return false;
	}
}
//execute method for the negotiate order
void Negotiate::execute(vector<Order*>* list)
{
	if (validate(list))
	{
		cout << "Negotiating with opposing army" << endl;
	}
}

OrdersList::OrdersList()
{

}
//Setter for OrdersList class
OrdersList::OrdersList(int size) :_size(size)
{
}
//Setter for copy constructor
OrdersList::OrdersList(const OrdersList&)
{
}
//Destructor for OrdersList
OrdersList::~OrdersList()
{
	cout << "Destroying OrdersList" << endl;
	for (auto order : _ordersList) {
		delete order;
		order = NULL;
	}
}
//remove method for OrdersList class
vector<Order*>* OrdersList::remove(vector<Order*>* list, int index)
{
	list->erase(list->begin() + (index - 1));
	return list;
}
//move method for OrdersList class
vector<Order*>* OrdersList::move(vector<Order*>* list, int a, int b)
{
	iter_swap(list->begin() + (a-1), list->begin() + (b-1));
	return list;
}
//method used to put an order into the list of orders
bool OrdersList::queueOrder(Order* order)
{
	if(order != NULL)
	{
		_ordersList.push_back(order);	//Adds order to list of orders
		
		return true;
	}
	return false;
	
}

