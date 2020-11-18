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
	_hand = NULL;
	cout << ">>>>>Deleting Player" << endl;
}

//Copy constructor for a player 
Player::Player(const Player& player)
{
	this->_id = player._id;
	this->_name = player._name;
	this->_reinforcementPool = player._reinforcementPool;
	this->_orderList = player._orderList;
	this->_hand = player._hand;
	this->_territoryList = player._territoryList;
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

int Player::getID() {        //d_rivi
	return _id;
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

//set players id 
void Player::setID(int id) {        //d_rivi
	_id = id;
}

bool Player::setOrderList(OrdersList* list)
{
	_orderList = list;
	return false;
}
//add order to players order's list
bool Player::addOrder(Order* order)
{
	return _orderList->queueOrder(order);
}

//add cards to players hand
void Player::addCard(Card* card)
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

void Player::setReinforcementPool(int reinforcementPool)
{
		_reinforcementPool = reinforcementPool;
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
				
				if (!(std::find(attackList->begin(), attackList->end(), adjTerr) != attackList->end())) {
					attackList->push_back(adjTerr);
				}	
			}
		}

	}

	return attackList;
}

//method that creates order and adds it to player's order list
void Player::issueOrder(string orderName, Player* p1, Player* p2, Territory* source, Territory* target, int numberOfArmies)
{
	if (orderName._Equal("deploy")) {
		Deploy* newOrder = new Deploy(p1, target, numberOfArmies);
		addOrder(newOrder);
	}
	else if(orderName._Equal("advance")){
		Advance* newOrder = new Advance(p1, source, target, numberOfArmies);
		addOrder(newOrder);
	}
	else if(orderName._Equal("airlift")){
		Airlift* newOrder = new Airlift(p1,source, target, numberOfArmies);
		addOrder(newOrder);
	}
	else if (orderName._Equal("bomb")) {
		Bomb* newOrder = new Bomb(p1, target);
		addOrder(newOrder);
	}
	else if (orderName._Equal("blockade")) {
		Blockade* newOrder = new Blockade(p1, target);
		addOrder(newOrder);
	}
	else if (orderName._Equal("negotiate")) {
		Negotiate* newOrder = new Negotiate(p1,p2);
		addOrder(newOrder);
	}
	else {
		cout << "ERROR: unrecognized order!" << endl;
	}

}

//removes territory from players territoryList
bool Player::removeTerritory(Territory* terr)
{
	if (std::find(getTerritoryList()->begin(), getTerritoryList()->end(), terr) != getTerritoryList()->end()) {
		_territoryList.erase(std::remove(_territoryList.begin(), _territoryList.end(), terr), _territoryList.end());
		terr->setOwner(nullptr);
		return true;
	}
	

	return false;
}

bool Player::removeCardFromHand(Card* card)
{
	if (std::find(getHand()->handOfCards.begin(), getHand()->handOfCards.end(), card) != getHand()->handOfCards.end()) {
		getHand()->handOfCards.erase(std::remove(getHand()->handOfCards.begin(), getHand()->handOfCards.end(), card), getHand()->handOfCards.end());
		return true;
	}
	return false;
}
void Player::displayTerrList()
{
	for (Territory* terr : *getTerritoryList()) {
		cout << terr->getTerritoryName() << endl;
	}
}

//overwritting string operator for class player
ostream& operator<< (ostream& stream, const Player& player)
{
	return stream << player._name << " currently has " << player._orderList->getOrdersList().size() << " orders, " << player._hand->handOfCards.size() << " cards, and " << player._territoryList.size() << " territories." << endl;
}