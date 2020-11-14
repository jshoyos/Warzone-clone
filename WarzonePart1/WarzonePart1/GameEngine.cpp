#include "GameEngine.h"
#include<iostream>
#include<filesystem>
#include<string>
#include <cmath>
#include <stdlib.h> 
#include <time.h>
#include <typeinfo>

using namespace std;
namespace fs = std::filesystem;

static int turn;
static int deployOrderLeft; //variable used to check if deploy orders remain
const string GameStart::PATH = "Maps/";
int GameStart::selectedOption = 0;
vector<string> GameStart::maps = vector<string>();
MapLoader  * GameStart::mapLoader = new MapLoader();
vector <Player*> GameStart::players = vector<Player*>();
Deck* GameStart::deck = nullptr;
Map* GameStart::map = nullptr;

void GameStart::displayMapOptions()
{
    cout << "Please Select One of the Following Available Maps:" << endl;
    int index = 0;
    
    for (auto& entry : fs::directory_iterator(PATH)) {
        GameStart::maps.push_back(entry.path().string());
        cout << "(" << index << ") " << entry.path() << endl;
        index++;
    }
}
int GameStart::numberOfPlayersSelection()
{
    int numberOfPlayers;
    cout << "Please enter the number of players [2-5]: ";
    cin >> numberOfPlayers;
    while (numberOfPlayers < 2 || numberOfPlayers > 5) {
        cout << "INVALID NUMBER OF PLAYERS" << endl;
        cout << "This game can only be played between 2 and 5 players. Make a new selection: ";
        cin >> numberOfPlayers;
    }
    return numberOfPlayers;
}
void GameStart::generateDeck()
{
    int deckSize;
    cout << "Please enter a deck size: ";
    cin >> deckSize;
    cout << "Genarating Deck..." << endl;
    GameStart::deck = new Deck(deckSize);
}

void GameStart::toggleObserverOnOff(Publisher* publisher,IObservable* observer,bool on)
{
    if (on && !publisher->isSubscribed(observer)) {
        publisher->subscribe(observer);
    }
    else {
        publisher->unsubscribe(observer);
    }
}
Map* GameStart::selectMap()
{
    displayMapOptions();
    cout << "Type your selection here: ";
    cin >> selectedOption;

    while (selectedOption < 0 || selectedOption > (int)GameStart::maps.size()) {
        cout << "Invalid selection..." << endl << "Please select again: ";
        cin >> selectedOption;
    }
    mapLoader-> setFileName(GameStart::maps[selectedOption]);
    cout << "Creaing map from " << GameStart::maps[selectedOption] << "..." << endl;
    Map *map = mapLoader->createMap();
    return map;
}

void GameStart::createPlayers()
{
    int numberOfPlayers = numberOfPlayersSelection();
    for (int i = 0; i < numberOfPlayers; ++i) {
        string name;
        cout << "Enter player " << i + 1 << " name: ";
        cin >> name;
        players.push_back(new Player(name));
    }
}

void GameStart::start()
{
	GameStart::map = GameStart::selectMap();
	GameStart::createPlayers();
	GameStart::generateDeck();
}


// ------------------------------------------- Main Game Loop ---------------------------------------- \\

void MainGameLoop::runMainloop()
{
	GameStart::start();	//sets up the initial parameters of the game
   
    turn = 1;
	while (true) { //map != conquered 
		
		for (Player* player : GameStart::players) {
			reinforcementPhase(player);
		}

		for (Player* player : GameStart::players) {
			issueOrderPhase(player);
		}
        //executes just the deploy orders of the players
        deployOrderLeft = 0;
        while (!(deployOrderLeft == GameStart::players.size())) {
            
        }
        //Deploy order execution phase
        for (Player* player : GameStart::players) {
            orderExecutionPhase(player);
        }
        //Remaining orders execution phase 
        for (Player* player : GameStart::players) {
            orderExecutionPhase(player);
        }
		
        turn++;
	}

}

void MainGameLoop::reinforcementPhase(Player* player)
{
	int playerTerritoryNum = player->getTerritoryList()->size();
	int armyNum = floor(playerTerritoryNum / 3);

	for (Continent* cont : *GameStart::map->getContinents())
	{
		if (checkOwnedContinent(player, cont)) {
			armyNum = armyNum + cont->getBonusArmies();
		}
	}
	player->setReinforcementPool(armyNum);

}

void MainGameLoop::issueOrderPhase(Player* player)
{
    Territory* source = nullptr;
    Territory* target = nullptr;
    int max = 0, min = 0, randTerrIndex = 0, randomArmyNum = 0;
    int armyNumber = 0, tempNum = 0;
    //on the first turn ditribute the armies evenly amongst the owned territories
    if (turn == 1) {
        armyNumber = player->getReinforcementPool();             
        tempNum = ceil(armyNumber / player->toDefend()->size()); 
        for (Territory* terr : *player->getTerritoryList()) {
            armyNumber = player->getReinforcementPool();
            //place remaining armies in last territory
            if (armyNumber < tempNum) {
                terr->setArmies(armyNumber);
                player->setReinforcementPool(0);
            }
            else {
                terr->setArmies(tempNum);
                player->setReinforcementPool(armyNumber - tempNum);
            }  
        }
    }

    else {
        //----- First step is to Issue the deploy order -----\\

         srand(time(0));
        
        //loops until there is no more army members in reinforcement pool
        while (player->getReinforcementPool() != 0) { 

            //gets number of armies from players pool
            armyNumber = player->getReinforcementPool();
            //initialize variables to 0
            max = 0, min = 0, randTerrIndex = 0, randomArmyNum = 0;
            //Max index for defending territory list
            max = player->toDefend()->size();
            //chooses a random number for the index of the territory list (between 0 and list.size()-1)
            randTerrIndex = rand() % max;
            max = player->getReinforcementPool() + 1;
            //chooses a random number of armies to deploy (between 0 and total armies in reinforcement pool)
            randomArmyNum = rand() % max;
            //choose target territory to deploy troups
            target = player->toDefend()->at(randTerrIndex);

            //changes the troups number in the reinforcementPool
            player->setReinforcementPool(player->getReinforcementPool() - armyNumber);

            cout << player->getName() << "issues deploy order" << endl;

            //issue deploy order (added to player's orderList)
            player->issueOrder("deploy", player, nullptr, nullptr, target, randomArmyNum);
        }

        // ------------------------------------------------------------------------------- \\

        //----- Second step is to for a player to issue an advance  -----\\
        
        //initialize variables to 0
        max = 0, min = 0, randTerrIndex = 0, randomArmyNum = 0;
        //randomly chooses between 1 (attack) and 0 (defend)
        int advanceStrategy = rand() % 2;   

        //Attack Strategy
        if (advanceStrategy == 1) {

            //max index for attack Territory list
            max = player->toAttack()->size();
            //random territory index from attack list
            randTerrIndex = rand() % max;    
            
            //Choose which owned territory will attack
            target = player->toAttack()->at(randTerrIndex);
            //finds owned territory that is adjacent to attacking territory
            for (Territory* terr : *target->getAdjacent()) {
                if (terr->getOwner().getName()._Equal(player->getName())) {
                    if (terr->getArmies() == 0) {
                        cout << "no troups left to attack target territory" << endl;
                    }
                    else {
                        //sets the source territory
                        source = terr;
                        //max number of troups to send from selected territory. Minimum of 1 troup to send out
                        max = source->getArmies(); min = 1;
                        //random number of troups to attack with
                        randomArmyNum = rand() % max + min;
                        break;
                    }
                }
            }
            cout << player->getName() << "issues advance attack order" << endl;

            //issue advance attack order (added to player's orderList)
            player->issueOrder("advance", player, nullptr, source, target, randomArmyNum);

        }
        //Defence Strategy
        else if(advanceStrategy == 0) {
            //max index for defend Territory list
            max = player->toDefend()->size();
            //random territory index from defend list
            randTerrIndex = rand() % max;

            //Choose which owned territory will be defended
            target = player->toDefend()->at(randTerrIndex);
            //finds owned territory that is adjacent to attacking territory
            for (Territory* terr : *target->getAdjacent()) {
                if (terr->getOwner().getName()._Equal(player->getName())) {
                    if (terr->getArmies() == 0) {
                        cout << "no troups left to defend target territory" << endl;
                    }
                    else {
                        //sets the source territory
                        source = terr;
                        //max number of troups to send from selected territory. Minimum of 1 troup to send out
                        max = source->getArmies(); min = 1;
                        //random number of troups to attack with
                        randomArmyNum = rand() % max + min;
                        break;
                    }
                }
            }
            cout << player->getName() << "issues advance attack order" << endl;

            //issue advance defence order (added to player's orderList)
            player->issueOrder("advance", player, nullptr, source, target, randomArmyNum);
        }


        // ------------------------------------------------------------------------------- \\

        //----- Third step is to play a card from players hand and issue its order -----\\
        
       
        max = player->toDefend()->size();
        max = player->toAttack()->size();
        randTerrIndex = rand() % max;

        Card* card = player->getHand()->handOfCards.at(0);
        
        if (card->getCardType() == Card::Bomb) {
          
        }
        else if (card->getCardType() == Card::Reinforcement) {
           
        }
        else if (card->getCardType() == Card::Blockade) {

        }
        else if (card->getCardType() == Card::Airlift) {
           
        }
        else if (card->getCardType() == Card::Diplomacy) {
          
        }
        //implement random actions with random teritories and random armies
        card->play2(player, player, nullptr, nullptr, player->toDefend()->at(0),1);
        player->removeCardFromHand(card);
        GameStart::deck->insertCard(*card);
       
        // ------------------------------------------------------------------------------- \\
        
       
    }
    

}

void MainGameLoop::orderExecutionPhase(Player* player)
{
    //orderList size
    int orderListSize = player->getOrderList()->_ordersList.size();
    int index = orderListSize - 1;
    
    index = 0;
    for (Order* order : player->getOrderList()->_ordersList) {
        string orderName = typeid(order).name();
        if (!(orderName._Equal("deploy") || deployOrderLeft == GameStart::players.size())) {
            deployOrderLeft++;
            return;
        }
        order->execute();
        player->getOrderList()->remove(index);
        index++;
     }
       
    
    

}

bool MainGameLoop::checkOwnedContinent(Player* player, Continent* cont)
{
	for (Territory* terr : *cont->getTerritories()) {
			
		if (terr->getOwner().getName() != player->getName()) {
			return false;
		}
	}
	
	return true;
}

bool MainGameLoop::priorityOrderList(Player* player) {
    bool check = false;
    int orderListSize = player->getOrderList()->_ordersList.size();
    int index = orderListSize - 1;
    int j = 0;
    //need to reorder list to represent priority list
    while (check)
    {
        for (size_t i = j; i < orderListSize; i++)
        {
            string orderName = typeid(player->getOrderList()->_ordersList.at(i)).name();

            if (orderName._Equal("deploy"))
            {
                //player->getOrderList()->move(,)
            }
            else if (orderName._Equal("airlift")) {

            }
            else if (orderName._Equal("blockade")) {

            }
            else {

            }

        }
    }
    return true;
}

