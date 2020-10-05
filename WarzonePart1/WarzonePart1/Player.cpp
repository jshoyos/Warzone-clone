#include "Player.h"


int Player::_id = 0;
//----------------------------- Constructors ----------------------------------\\

Player::Player()
{
	_id++;
}

Player::~Player()
{
}

Player::Player(const Player& player)
{
	this->_id = player._id;
	this->_name = player._name;
	//this->_hand = player._hand;
	//this->_orderList = player._orderList;
	//this->_territoryList = player._territoryList;
	
	for (int i = 0; i < player._orderList.size();i++) {
		this->_orderList[i] = player._orderList[i];
	}
	for (int i = 0; i < player._territoryList.size();i++) {
		this->_territoryList[i] = player._territoryList[i];
	}
	for (int i = 0; i < player._hand.size();i++) {
		this->_hand[i] = player._hand[i];
	}

}

Player::Player(string name) :_name(name)
{
	_id++;
}

Player::Player(string name, vector<Orders*> orders, vector<Cards*> cards, vector<Territory*> territories) : _name(name), _orderList(orders), _hand(cards), _territoryList(territories)
{
	_id++;
}

//------------------------------------ Getters -----------------------------\\

string Player::getName()
{
	return _name;
}

vector<Orders*> Player::getOrderList()
{
	return _orderList;
}

vector<Cards*> Player::getHand()
{
	return _hand;
}

vector<Territory*> Player::getTerritoryList()
{
	//return the copied list pointers (maybe)
	return _territoryList;
}

//---------------------------------- Setters --------------------------------\\

bool Player::setName(string name)
{
	if (name != "") {
		_name = name;
		return true;
	}
	return false;
}

bool Player::addOrder(Orders* order)
{
	if (order != NULL)
	{
		_orderList.push_back(order);
		return true;
	}
	return false;
}

bool Player::addCard(Cards* card)
{
	if (card != NULL)
	{
		_hand.push_back(card);
		return true;
	}
	return false;
}

bool Player::conquerTerritory(Territory* territory)
{
	//similar code in Map // get territory list from Map and create a copy in player
	if (territory != NULL)
	{
		_territoryList.push_back(territory);
		return true;
	}
	return false;
}

//--------------------------------------------- Methods ---------------------------\\

Player& Player::operator=(const Player& player)
{
	return *(new Player(player));
}

vector<Territory*> Player::toDefend()
{
	//write some stuff for console
	cout << "list of territories to defend" << endl;
	return getTerritoryList();
}

vector<Territory*> Player::toAttack()
{	//receives a list of strings/ints from user and creates a list of territories to attack
	//write stuff to console 
	cout << "list of territories to attack" << endl;

	return vector<Territory*>();
}

void Player::issueOrder()
{
	//maybe recieve order as parameter
	Orders* newOrder = new Orders();
	addOrder(newOrder);
}

ostream& operator<< (ostream& stream, const Player& player)
{
	return stream << player._name << " currently has " << player._orderList.size() << "orders, " << player._hand.size() << "cards, and has " << player._territoryList.size() << "territories." << endl;
}