#include "Player.h"


int Player::_id = 0;
//----------------------------- Constructors ----------------------------------\\

//Default constructor for player
Player::Player()
{
	_id++; //increments static int (id)
}

//Destructor for a player
Player::~Player()
{
}

//Copy constructor for a player 
Player::Player(const Player& player)
{
	this->_id = player._id;
	this->_name = player._name;
	
	//Iterates through list and copies onjects
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
//Parameterized constructor accpeting a string and increments the id
Player::Player(string name) :_name(name)
{
	_id++; //increments static int (id)
}

//Parameterized constructor accpeting a list of orders, a list of cards and a list of territories.
Player::Player(string name, vector<Orders*>* orders, vector<Cards*>* cards, vector<Territory*>* territories) : _name(name), _orderList(*orders), _hand(*cards), _territoryList(*territories)
{
	_id++; //increments static int (id)
}

//------------------------------------ Getters -----------------------------\\

//get method that returns a players name of type string
string Player::getName()
{
	return _name;
}

//get method that returns a players list of orders
vector<Orders*>* Player::getOrderList()
{
	return &_orderList;
}
//get method that returns list of cards in a players hand
vector<Cards*>* Player::getHand()
{
	return &_hand;
}

//get method that returns a list of territories owned 
vector<Territory*>* Player::getTerritoryList()
{
	return &_territoryList;
}

//---------------------------------- Setters --------------------------------\\

//set players name 
bool Player::setName(string name)
{
	if (name != "") {
		_name = name;
		return true;
	}
	return false;
}
//add order to players order's list
bool Player::addOrder(Orders* order)
{
	if (order != NULL)
	{
		_orderList.push_back(order);
		return true;
	}
	return false;
}

//add cards to players hand
bool Player::addCard(Cards* card)
{
	if (card != NULL)
	{
		_hand.push_back(card);
		return true;
	}
	return false;
}

//add territories to players list of territories
bool Player::conquerTerritory(Territory* territory)
{
	//similar code in Map // get territory list from Map and create a copy in player
	if (territory != NULL)
	{
		_territoryList.push_back(territory);
		territory->setOwner(this);
		return true;
	}
	return false;
}

//--------------------------------------------- Methods ---------------------------\\

//Overwritting assign operator 
Player& Player::operator=(const Player& player)
{
	return *(new Player(player));
}

//method that returns a list of territories to defend
vector<Territory*>* Player::toDefend()
{
	//write some stuff for console
	return getTerritoryList();
}

//method that returns a list of territories to attack (not owned by player)
vector<Territory*>* Player::toAttack()
{	
	//arbitrary set of territories to attack
	Territory* Canada = new Territory(0, "Canada", 0);
	Territory* USA = new Territory(1, "USA", 0);

	vector<Territory*> *terrList = new vector<Territory*>();
	terrList->push_back(Canada);
	terrList->push_back(USA);

	return terrList;
}

//method that creates order and adds it to player's order list
void Player::issueOrder()
{
	//maybe recieve order as parameter
	Orders* newOrder = new Orders();
	addOrder(newOrder);
}

//overwritting string operator for class player
ostream& operator<< (ostream& stream, const Player& player)
{
	return stream << player._name << " currently has " << player._orderList.size() << " orders, " << player._hand.size() << " cards, and has " << player._territoryList.size() << " territories." << endl;
}