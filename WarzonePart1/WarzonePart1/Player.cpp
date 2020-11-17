#include "Player.h"


int Player::_id = 0;
//----------------------------- Constructors ----------------------------------\\

//Default constructor for player
Player::Player()
{
	_hand = new Hand();
	_orderList = new OrdersList();
	_id++; //increments static int (id)
}

//Destructor for a player
Player::~Player()
{
	delete _orderList; _orderList = NULL;
	delete _hand; _hand = NULL;
}

//Copy constructor for a player 
Player::Player(const Player& player)
{
	this->_id = player._id;
	this->_name = player._name;
	
	//Iterates through list and copies onjects
}
//Parameterized constructor accpeting a string and increments the id
Player::Player(string name) :_name(name)
{
	_hand = new Hand();
	_orderList = new OrdersList();
	_id++; //increments static int (id)
}

//Parameterized constructor accpeting a list of orders, a list of cards and a list of territories.
Player::Player(string name, OrdersList* orders, Hand* hand, vector<Territory*>* territories) : _name(name), _orderList(orders), _hand(hand), _territoryList(*territories)
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
OrdersList* Player::getOrderList()
{
	return _orderList;
}
//get method that returns list of cards in a players hand
Hand* Player::getHand()
{
	return _hand;
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
bool Player::addOrder(Order* order)
{
	return _orderList->queueOrder(order);
}

//add cards to players hand
void Player::addCard(Card card)
{
	_hand->insertCard(card);
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
void Player::issueOrder(string orderName)
{
	//maybe recieve order as parameter
//	Order* newOrder = new Order(orderName);
//	addOrder(newOrder);
}

//overwritting string operator for class player
ostream& operator<< (ostream& stream, const Player& player)
{
	return stream << player._name << " currently has " << player._orderList->getOrdersList().size() << " orders, " << player._hand->handOfCards.size() << " cards, and " << player._territoryList.size() << " territories." << endl;
}