#include "Player.h"

int Player::_id = 0;
//----------------------------- Constructors ----------------------------------\\

//Default constructor for player
Player::Player()
{
	_reinforcementPool = 0;
	_name = "";
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
	this->_reinforcementPool = player._reinforcementPool;
	
	//Iterates through list and copies onjects
	for (int i = 0; i < player._orderList->_ordersList.size();i++) {
		this->_orderList->_ordersList[i] = player._orderList->_ordersList[i];
	}
	for (int i = 0; i < player._territoryList.size();i++) {
		this->_territoryList[i] = player._territoryList[i];
	}
	for (int i = 0; i < player._hand->handOfCards.size();i++) {
		this->_hand->handOfCards[i] = player._hand->handOfCards[i];
	}
	
}
//Parameterized constructor accpeting a string, and increments the id
Player::Player(string name) :_name(name)
{
	_reinforcementPool = 0;
	_hand = new Hand();
	_orderList = new OrdersList();
	_id++; //increments static int (id)
}

//Parameterized constructor accpeting a string, an int and increments the id
Player::Player(string name, int num) :_name(name),_reinforcementPool(num)
{
	_hand = new Hand();
	_orderList = new OrdersList();
	_id++; //increments static int (id)
}

//Parameterized constructor accpeting a list of orders, a list of cards and a list of territories.
Player::Player(string name, OrdersList* orders, Hand* hand, vector<Territory*>* territories,int num) : _name(name), _orderList(orders), _hand(hand), _territoryList(*territories), _reinforcementPool(num)
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

int Player::getReinforcementPool()
{
	return _reinforcementPool;
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

bool Player::setReinforcementPool(int reinforcementPool)
{
	if (reinforcementPool != NULL) {
		_reinforcementPool = reinforcementPool;
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
	vector<Territory*>* attackList = new vector<Territory*>();

	for (Territory* terr : *getTerritoryList()) {

		for (Territory* adjTerr : *terr->getAdjacent()) {

			//checks if adjacent territories are part of the players territories.
			if (!(std::find(getTerritoryList()->begin(), getTerritoryList()->end(), adjTerr) != getTerritoryList()->end())){
				attackList->push_back(adjTerr);
			}
		}

	}

	return attackList;
}

//method that creates order and adds it to player's order list
void Player::issueOrder(string orderName)
{
	if (orderName._Equal("deploy")) {
		Order* newOrder = new Order(orderName);
		addOrder(newOrder);

	}
	else if(orderName._Equal("advance")){
		Order* newOrder = new Order(orderName);
		addOrder(newOrder);
	}
	else {
		Order* newOrder = new Order(orderName);
		addOrder(newOrder);
	}


}

//overwritting string operator for class player
ostream& operator<< (ostream& stream, const Player& player)
{
	return stream << player._name << " currently has " << player._orderList->_ordersList.size() << " orders, " << player._hand->handOfCards.size() << " cards, " << player._territoryList.size() << " territories, and " << player._reinforcementPool<< "armies in pool."<< endl;
}