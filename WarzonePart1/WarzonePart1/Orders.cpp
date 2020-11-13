#include "Orders.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h> 
#include <time.h>
#include <typeinfo>

using namespace std;


//Default constructor for Order
Order::Order()
{
	_p = nullptr;
	_target = nullptr;
	_numberOfArmies = 0;
}

//Copy constructor for Order
Order::Order(const Order&)
{
}

Order::Order(Player* p, Territory* target, int numberOfArmies) : _p(p), _target(target), _numberOfArmies(numberOfArmies)
{
	
}


Player* Order::getPlayer()
{
	return _p;
}

Territory* Order::getTarget()
{
	return _target;
}

int Order::getNumberOfArmies()
{
	return _numberOfArmies;
}

bool Order::setPlayer(Player* p)
{
	if (p != NULL)
	{
		_p = p;
		return true;
	}
	return false;
}


bool Order::setTarget(Territory* target)
{
	if (target != NULL)
	{
		_target = target;
		return true;
	}
	return false;
}

bool Order::setNumberOfArmies(int numberOfArmies)
{
	_numberOfArmies = numberOfArmies;
	return true;
}

//Insertion stream operator
ostream& operator<<(ostream& stream, const Order& order)
{
	string output = "";
	return stream << typeid(order).name()<< endl;
	

}

//Another insertion stream operator for the OrdersList class
ostream& operator<<(ostream& stream, const OrdersList& list)
{
	string output = "";
	for(int i=0; i < list._ordersList.size(); i++)
	{
		output = output + typeid(*list._ordersList[i]).name() + " ";
	}
	return stream << output << endl;
}

Deploy::Deploy()
{
}

Deploy::Deploy(const Deploy&)
{
}

Deploy::Deploy(Player* p, Territory* target, int numberOfArmies):Order(p, target, numberOfArmies)
{

}

//validate method for the deploy order
bool Deploy::validate()
{
	/*vector<Territory*> *territoryList = getPlayer()->getTerritoryList();
	if (getNumberOfArmies() <= 0)
	{
		if (std::find(territoryList->begin(), territoryList->end(), getTarget()) != territoryList->end()) {
				return true;
			}

			else {
			cout << "ERROR: " << getTarget()->getTerritoryName() << " either does not belong to " << getPlayer()->getName() << " or does not exist." << endl;
				return false;
			}
	}
	else {
		cout << "ERROR: " << getNumberOfArmies() << " must be greater than 0 " << endl;
		return false;
	}*/
	return false;
}
//execute method for the deploy order
void Deploy::execute()
{
	/*if(validate())
	{
		getTarget()->setArmies(getTarget()->getArmies() + getNumberOfArmies());
		cout << "Deploying" << getNumberOfArmies() << " armies to " << getTarget()->getTerritoryName() << endl;
	}*/
}

Advance::Advance()
{
}
Advance::Advance(const Advance&)
{
}
Advance::Advance(Player* p, Territory* source, Territory* target, int numberOfArmies):Order(p, target, numberOfArmies)
{
	_source = source;
}
//validate method for the advance order
bool Advance::validate()
{
	vector<Territory*> territoryList = *getPlayer()->getTerritoryList();
	vector<Territory*> adjacentList = *getSource()->getAdjacent();

	if (getNumberOfArmies() <= 0)
	{
		if (std::find(territoryList.begin(), territoryList.end(), getSource()) != territoryList.end()) {
			
			if (std::find(adjacentList.begin(), adjacentList.end(), getTarget()) != adjacentList.end()) {

				return true;
			}

			else {
				cout << "ERROR: " << getTarget()->getTerritoryName() << " is not an adjacent to " << getSource()->getTerritoryName() << endl;
				return false;
			}
		}

		else {
			cout << "ERROR: " << getSource()->getTerritoryName() << " does not belong to " << getPlayer()->getName() << endl;
			return false;
		}
	}
	else {
		cout << "ERROR: " << getNumberOfArmies() << " must be greater than 0 " << endl;
		return false;
	}
	return false;

}
Territory* Advance::getSource()
{
	return _source;
}
bool Advance::setSource(Territory* source)
{
	if (source != NULL)
	{
		_source = source;
		return true;
	}

	return false;
}
//execute method for the advance order
void Advance::execute()
{
	vector<Territory*> territoryList = *getPlayer()->getTerritoryList();
	vector<Territory*> adjacentList = *getSource()->getAdjacent();
	if (validate())
	{
		if (std::find(territoryList.begin(), territoryList.end(), getSource) != territoryList.end() && std::find(territoryList.begin(), territoryList.end(), getTarget()) != territoryList.end()) {
			getSource()->setArmies(getSource()->getArmies() - getNumberOfArmies());
			getTarget()->setArmies(getTarget()->getArmies() + getNumberOfArmies());
		}
		cout << "Advancing " << getNumberOfArmies() << " armies from " << getSource() << " to" << getTarget() << endl;
	}

	if (validate())
	{
		if (std::find(territoryList.begin(), territoryList.end(), getSource()) != territoryList.end() && !(std::find(territoryList.begin(), territoryList.end(), getTarget()) != territoryList.end())) {
			cout << "Attacking " << getTarget()->getTerritoryName() << " with " << getNumberOfArmies() << endl;
			srand(time(0));
			int attackers = getNumberOfArmies();
			int defenders = getTarget()->getArmies();

			while (attackers != 0 && defenders != 0) {
				int random1= rand() % 10 + 1;
				int random2= rand() % 10 + 1;
				if (random1 < 7)
				{
					defenders--;
				}
				if (random2 < 8)
				{
					attackers--;
				}
			}

			if (attackers == 0)
			{
				getSource()->setArmies(getSource()->getArmies() - getNumberOfArmies());
				getTarget()->setArmies(defenders);
				cout << "All invading armies have been killed,  " << defenders << " armies remain in " << getTarget()->getTerritoryName() << endl;
			}

			if (defenders == 0)
			{
				getSource()->setArmies(getSource()->getArmies() - getNumberOfArmies());
				getTarget()->setArmies(attackers);
				cout << "All defending armies have been killed,  " << attackers << " armies have conquered " << getTarget()->getTerritoryName() << endl;

				//Pointer to territory
				getPlayer()->conquerTerritory(getTarget());
				vector<Territory*> listToUpdate = *getTarget()->getOwner().getTerritoryList();
				listToUpdate.erase((std::remove(listToUpdate.begin(), listToUpdate.end(), getTarget()), listToUpdate.end()));

				//TODO: add card after conquering territory
			}

		}
	}


}


Bomb::Bomb()
{
}

Bomb::Bomb(const Bomb&)
{
}

Bomb::Bomb(Player* p, Territory* target, int numberOfArmies) : Order(p, target, numberOfArmies)
{
}

//validate method for the bomb order
bool Bomb::validate()
{

}
//execute method for the bomb order
void Bomb::execute()
{
	
}


Blockade::Blockade()
{
}

Blockade::Blockade(const Blockade&)
{
}

Blockade::Blockade(Player* p, Territory* target, int numberOfArmies) : Order(p, target, numberOfArmies)
{
}

//validate method for the blockade order
bool Blockade::validate()
{
	
}
//execute method for the blockade order
void Blockade::execute()
{
	
}

Airlift::Airlift()
{
}
Airlift::Airlift(const Airlift&)
{
}
Airlift::Airlift(Player* p, Territory* source, Territory* target, int numberOfArmies) :Order(p, target, numberOfArmies)
{
	_source = source;
}
//validate method for the airlift order
bool Airlift::validate(vector<Order*>* list)
{
	
}

Territory* Airlift::getSource()
{
	return _source;
}
bool Airlift::setSource(Territory* source)
{
	if (source != NULL)
	{
		_source = source;
		return true;
	}

	return false;
}

//execute method for the airlift order
void Airlift::execute(vector<Order*>* list)
{
	
}


Negotiate::Negotiate()
{
}

Negotiate::Negotiate(const Negotiate&)
{
}

Negotiate::Negotiate(Player*, Territory*, Territory*, int)
{
}

//validate method for the negotiate order
bool Negotiate::validate(vector<Order*>* list)
{
	
}

Territory* Negotiate::getSource()
{
	return _source;
}
bool Negotiate::setSource(Territory* source)
{
	if (source != NULL)
	{
		_source = source;
		return true;
	}

	return false;
}

//execute method for the negotiate order
void Negotiate::execute(vector<Order*>* list)
{
	
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
	index = index - 1;
	list->erase(list->begin() + (index));
	return list;
}
//move method for OrdersList class
vector<Order*>* OrdersList::move(vector<Order*>* list, int a, int b)
{
	a = (a - 1);
	b = (b - 1);
	iter_swap(list->begin() + (a), list->begin() + (b));
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

