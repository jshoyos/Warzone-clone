#include "GameEngine.h"
#include<iostream>
#include<filesystem>
#include<string>
#include <vector>
#include <random>
#include <cmath>
#include <stdlib.h> 
#include <time.h>
#include <typeinfo>

using namespace std;
namespace fs = std::filesystem;

int MainGameLoop::turn=1;
int MainGameLoop::deployOrderLeft=0; //variable used to check if deploy orders remain
const string GameStart::PATH = "Maps/";
int GameStart::selectedOption = 0;
vector<string> GameStart::maps = vector<string>();
MapLoader  * GameStart::mapLoader = new MapLoader();
vector <Player*> GameStart::players = vector<Player*>();
Deck* GameStart::deck = nullptr;
Map* GameStart::map = nullptr;

void GameStart::displayMapOptions()
{
    cout << "Welcome to Warzone! \n\nPlease Select One of the Following Available Maps:" << endl;

    int index = 0;
    
    for (auto& entry : fs::directory_iterator(PATH)) {
        GameStart::maps.push_back(entry.path().string());
        cout << "(" << index << ") " << entry.path() << endl;
        index++;
    }

    //for the purpose of a file-not-found error
    cout << "(" << index << ") \"Maps\/file_not_found.map\"" << endl;    

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
    cout << "\nPlease enter a deck size: ";
    cin >> deckSize;
    cout << "\nGenarating Deck..." << endl << endl;
    GameStart::deck = new Deck(deckSize);
}

void GameStart::toggleObserverOnOff(Publisher* publisher,IObservable* observer,bool on)
{
    if (on) {
        publisher->subscribe(observer);
    }
    else{
        publisher->unsubscribe(observer);
    }
}
Map* GameStart::selectMap()
{
    displayMapOptions();
    cout << "\nType your selection here: ";
    cin >> selectedOption;
    // for the purpose of a file-not-found error
    if (selectedOption == (int)GameStart::maps.size()) {                                               
        mapLoader->setFileName("file_not_found.maps");
        cout << "\nCreating map from Maps/file_not_found.map..." << endl << endl;
        GameStart::map = mapLoader->createMap();
    }
    while (selectedOption < 0 || selectedOption >= (int)GameStart::maps.size()) { 
        cout << "Invalid selection..." << endl << "Please select again: ";
        cin >> selectedOption;
    }
    mapLoader-> setFileName(GameStart::maps[selectedOption]);

    cout << "\nCreating map from " << GameStart::maps[selectedOption] << "..." << endl << endl;
    GameStart::map = mapLoader->createMap();
    
    cout << "\nMap has been created. \n\nLet's now validate the map:\n" << endl;
    map->validate();
    cout << endl;
    return map;
}

void GameStart::createPlayers()
{
    int numberOfPlayers = numberOfPlayersSelection();
    cout << endl;
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

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// This method shuffles our vector of Players. 
// Example: original vector: (bob, mike, chris), new vector: (mike, chris, bob), where players[0] is now mike. 

void GameStartup ::randomPlayerOrder() {

    random_device rd;
    mt19937 g(rd());
    cout << "\nAgain, our players are: \n" << endl;
    for (int i = 0; i < GameStart::players.size(); i++)
        cout << i << ". " << GameStart::players[i]->getName() << endl;

    shuffle(GameStart::players.begin(), GameStart::players.end(), g);

    cout << "\nThe order of play though will be determined randomly, and as follow: \n" << endl;
    for (int i = 0; i < GameStart::players.size(); i++)
        cout << "Player " << i << ": " << GameStart::players[i]->getName() << endl;

}

// This method randomly assigns territories to each player, in a round-robin fashion

void GameStartup::assignTerritories() {

    int mapSize = GameStart::map->getMapSizeTerritory();
    int numbPlayers = GameStart::players.size();
    cout << "\nUsing Round-Robin, let's randomly assign all " << mapSize << " territories to each player: \n" << endl;
    int playerIndex = 0;

    // Let's create a dummy_vec with values 0 to (n-1) where n = mapSize. 
    // Let's shuffle the values in that dummy (ie: 4, 13, 39, 17, 3, etc)
    // Then the value at index 0 (let's say it's 4) will be used as the index-value of our territories vector, in order to randomly assign a territory to a player.. 
    // So, following on this example, if value at dummy_vec[0] is 4, then we assign the territory at territories[4] to the first player, and we keep going like that in RR
    // until we went through all the dummy_vector values, and (ultimately) all territories have been randomly assigned to our players, in a round-robin fashion.

    random_device rd;
    mt19937 g(rd());
    vector<int> dummy_vec(mapSize);
    for (int i = 0; i < mapSize; i++)
        dummy_vec[i] = i;
    shuffle(dummy_vec.begin(), dummy_vec.end(), g);

    
    for (int i = 0; i < mapSize; i++) {

        if (playerIndex == numbPlayers)
            playerIndex = 0;

        GameStart::players[playerIndex % numbPlayers]->conquerTerritory(GameStart::map->getTerritoryById(dummy_vec[i]));
       
        // adding this would be redundant: (*GameStart::map->getTerritoryById(dummy_vec[i])).setOwner(players[playerIndex % numbPlayers]);
        // since Player::conquerTerritory takes care of doing it already: territory->setOwner(this);

        cout << "Player \"" << GameStart::players[playerIndex]->getName() << "\" was assigned Territory: \""
             << (GameStart::map->getTerritoryById(dummy_vec[i]))->getTerritoryName() << "\" " << endl;

        playerIndex++;
          
    }

    cout << "\nLet's review the list of territories of each player:\n" << endl;
    for (int i = 0; i < numbPlayers; i++)
        for (int j = 0; j < (GameStart::players[i]->getTerritoryList())->size(); j++)
            cout << *GameStart::players[i]->getTerritoryList()->at(j);

    cout << "\nLet's do the math quickly... \n\n";
    for (int i = 0; i < numbPlayers; i++)
        cout << "- Player \"" << GameStart::players[i]->getName() <<"\" has " << (GameStart::players[i]->getTerritoryList())->size() << " territories" << endl;
    cout << "\nThat's " << mapSize << " territories, which matches the number of territories in the map, awesome!";

}

void GameStartup::initializeArmies() {
    int numbPlayers = GameStart::players.size();
    switch (numbPlayers) {
        case 2:
            for (int i = 0; i < numbPlayers; i++)
                GameStart::players[i]->setReinforcementPool(40);
            break;
        case 3:
            for (int i = 0; i < numbPlayers; i++)
                GameStart::players[i]->setReinforcementPool(35);
            break;
        case 4:
            for (int i = 0; i < numbPlayers; i++)
                GameStart::players[i]->setReinforcementPool(30);
            break;
        case 5:
            for (int i = 0; i < numbPlayers; i++)
                GameStart::players[i]->setReinforcementPool(25);
            break;
    }

    cout << "\n\nLast but not least, since we have " << numbPlayers << " players, each will be receiving " << GameStart::players[0]->getReinforcementPool() 
         << " armies in their reinforcement pool. Let's verify that:\n" << endl;
    
    for (int i = 0; i < numbPlayers; i++) 
        cout << "- Player \"" << GameStart::players[i]->getName() << "\" has " << GameStart::players[i]->getReinforcementPool() << " armies in their reinforcement pool." << endl;
    cout << endl << "Alright! Looks like we're all set. And now, let the game begin!" << endl << endl;

}


void GameStartup::startupPhase() {
    randomPlayerOrder();
    assignTerritories();
    initializeArmies();
}


// ------------------------------------------- Main Game Loop ---------------------------------------- \\

Publisher MainGameLoop::phasePublisher = Publisher();
PhaseObserver* MainGameLoop::phaseObserver = new PhaseObserver();
GameStatisticsObserver* MainGameLoop::statsObserver = new GameStatisticsObserver();


void MainGameLoop::runMainloop()
{
    MainGameLoop::phasePublisher.subscribe(MainGameLoop::phaseObserver);
	GameStart::start();	//sets up the initial parameters of the game
    
    GameStart::toggleObserverOnOff(&MainGameLoop::phasePublisher, MainGameLoop::phaseObserver, true);
    GameStart::toggleObserverOnOff(&MainGameLoop::phasePublisher, MainGameLoop::statsObserver, true);

    GameStartup::startupPhase();
   
    MainGameLoop::turn = 1;
	while (GameStart::players.size()!=1) { //map != conquered 
        //Phase 1
        
		for (Player* player : GameStart::players) {
            cout << player->getName()<<"'s Reinforcement Phase!" << endl;
            if (player->getTerritoryList()->empty()) {
                continue;
            }
            issueOrderPhase(player);
            MainGameLoop::phasePublisher.notifyAll("phase1");
		}
       
        //Phase 2
		for (Player* player : GameStart::players) {
            cout << player->getName() << "'s IssueOrdering Phase!" << endl;
            if (player->getTerritoryList()->empty()) {
                continue;
            }
            issueOrderPhase(player);
            MainGameLoop::phasePublisher.notifyAll("phase2");
		}
        
        //executes just the deploy orders of the players
        MainGameLoop::deployOrderLeft = 0;
        //Phase 3
        //Deploy order execution phase
        for (Player* player : GameStart::players) {
            cout << player->getName() << "'s Deploy Execution Phase!" << endl;
            if (player->getTerritoryList()->empty()) {
                continue;
            }
            if (player->getTerritoryList()->size() == 0) {
                cout << "remove player from game! You lose!" << endl;
            }
            orderExecutionPhase(player);
            MainGameLoop::phasePublisher.notifyAll("phase3");
        }
        //Remaining orders execution phase 
        for (Player* player : GameStart::players) {
            cout << player->getName() << "'s Order Execution Phase!" << endl;
            if (player->getTerritoryList()->empty()) {
                continue;
            }
            //removes player from list if he does not own anymore territories
            if (player->getTerritoryList()->size() == 0) {
                cout << "remove player from game! You lose!" << endl;
                GameStart::players.erase(std::remove(GameStart::players.begin(), GameStart::players.end(), player), GameStart::players.end());
                continue;
            }
            orderExecutionPhase(player);
            MainGameLoop::phasePublisher.notifyAll("phase3");
        }
		
        MainGameLoop::turn++;
	}
    cout << GameStart::players.at(0) << " wins!" << endl;
    cout << " Thanks for Playing!" << endl;
}

void MainGameLoop::reinforcementPhase(Player* player)
{
    if (MainGameLoop::turn == 1) {
        return;
    }
	double playerTerritoryNum = player->getTerritoryList()->size();
	int armyNum = floor(playerTerritoryNum / 3);

	for (Continent* cont : *GameStart::map->getContinents())
	{
		if (checkOwnedContinent(player, cont)) {
			armyNum = armyNum + cont->getBonusArmies();
		}
	}
	player->setReinforcementPool(armyNum);
    //return to_string(armyNum) + " armies added;";
}

void MainGameLoop::issueOrderPhase(Player* player)
{
    //initializing variables
    Territory* source = nullptr;
    Territory* target = nullptr;
    int max = 0, min = 0, randTerrIndex = 0, randomArmyNum = 0;
    
    int armyNumber = 0;
    //on the first turn ditribute the armies evenly amongst the owned territories
    if (MainGameLoop::turn == 1) {
        //armyNumber = player->getReinforcementPool();             
        //tempNum = ceil(armyNumber / player->toDefend()->size()); 
        while (player->getReinforcementPool()!=0)
        {
            for (Territory* terr : *player->getTerritoryList()) {
                if (player->getReinforcementPool() == 0) {
                    break; 
                }
                armyNumber=terr->getArmies();
                terr->setArmies(++armyNumber);
                player->setReinforcementPool(player->getReinforcementPool() - 1);
            }
        } 
      
    }
    else {
        //----- First step is to Issue the deploy order -----\\
        
        //loops until there is no more army members in reinforcement pool
        while (player->getReinforcementPool() != 0) { 
            srand(time(0));
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
            //choose target territory to deploy troops
            target = player->toDefend()->at(randTerrIndex);

            //changes the troops number in the reinforcementPool
            player->setReinforcementPool(player->getReinforcementPool() - armyNumber);

            cout << player->getName() << " issues deploy order" << endl;

            //issue deploy order (added to player's orderList)
            player->issueOrder("deploy", player, nullptr, nullptr, target, randomArmyNum);
        }

        // ------------------------------------------------------------------------------- \\

        //----- Second step is to for a player to issue an advance  -----\\
        
        //initialize variables to 0
        srand(time(0));
        max = 0, min = 0, randTerrIndex = 0, randomArmyNum = 0;
        //randomly chooses between 1 (attack) and 0 (defend)
        int advanceStrategy = rand() % 2;   

        //Attack Strategy
        if (advanceStrategy == 1) {
            srand(time(0));
            //max index for attack Territory list
            max = player->toAttack()->size();
            //random territory index from attack list
            randTerrIndex = rand() % max;    
            
            //Choose which owned territory will attack
            target = player->toAttack()->at(randTerrIndex);
            //finds owned territory that is adjacent to attacking territory
            for (Territory* terr : *target->getAdjacent()) {
                if (terr->getOwner()->getName()._Equal(player->getName())) {
                    //sets the source territory
                    source = terr;
                    //max number of troops to send from selected territory. Minimum of 1 troop to send out
                    max = source->getArmies(); min = 1;
                    //random number of troops to attack with
                    if (max == 0) {
                        randomArmyNum = 0;
                    }
                    else if (MainGameLoop::turn > 20) {
                        randomArmyNum = max;
                    }
                    else{
                        randomArmyNum = rand() % max + min;
                    }
                    break;
                }
            }
            cout << player->getName() << " issues advance attack order" << endl;

            //issue advance attack order (added to player's orderList)
            player->issueOrder("advance", player, nullptr, source, target, randomArmyNum);

        }
        //Defense Strategy
        else if(advanceStrategy == 0) {
            srand(time(0));
            //max index for defend Territory list
            max = player->toDefend()->size();
            //random territory index from defend list
            randTerrIndex = rand() % max;

            //Choose which owned territory will be defended
            target = player->toDefend()->at(randTerrIndex);
            //finds owned territory that is adjacent to attacking territory
            for (Territory* terr : *target->getAdjacent()) {
                if (terr->getOwner()->getName()._Equal(player->getName())) {
                    //sets the source territory
                    source = terr;
                    //max number of troops to send from selected territory. Minimum of 1 troup to send out
                    max = source->getArmies(); min = 1;
                    //random number of troops to attack with
                    if (max == 0) {
                        randomArmyNum = 0;
                    }
                    else {
                        randomArmyNum = rand() % max + min;
                    }
                        
                    break;
                    
                }
            }
            cout << player->getName() << " issues advance defence order" << endl;

            //issue advance defence order (added to player's orderList)
            player->issueOrder("advance", player, nullptr, source, target, randomArmyNum);
        }


        // ------------------------------------------------------------------------------- \\

        //----- Third step is to play a card from players hand and issue its order -----\\
        
        //randomly chooses between 1 (attack) and 0 (defend)
        srand(time(0));
        advanceStrategy = rand() % 2;
        //selecting target territory
        if (advanceStrategy == 0) {
            max = player->toDefend()->size();
            randTerrIndex = rand() % max;
            target = player->toDefend()->at(randTerrIndex);
        }
        else if (advanceStrategy==1) {
            max = player->toAttack()->size();
            randTerrIndex = rand() % max ;
            target = player->toAttack()->at(randTerrIndex);
        }
        
        //random selecting source territory
        max = player->toDefend()->size();
        randTerrIndex = rand() % max;
        source = player->toDefend()->at(randTerrIndex);

        //random number of armies
        max = source->getArmies();min = 1;
        if (max == 0) {
            randomArmyNum = 0;
        }
        else {
            randomArmyNum = rand() % max + min;
        }
        

        //select random player that is not self
        max = player->toAttack()->size();
        randTerrIndex = rand() % max; 
        Player* p2 = player->toAttack()->at(randTerrIndex)->getOwner();

        if (player->getHand()->getHandSize() == 0) {
            cout << "no cards in hand" << endl;
        }
        else {
            Card* card = player->getHand()->handOfCards.at(0);

            //implement random actions with random teritories and random armies
            card->play2(player, p2, source, target, randomArmyNum);
            player->removeCardFromHand(card);
            GameStart::deck->insertCard(*card);
        }
        // ------------------------------------------------------------------------------- \\

        //return "helo";
    }
}

void MainGameLoop::orderExecutionPhase(Player* player)
{
    //orderList size
    int orderListSize = player->getOrderList()->getOrdersList().size();
    int index = orderListSize - 1;
    
    index = 0;
    for (Order* order : player->getOrderList()->getOrdersList()) {
        string orderName = typeid(*order).name();
        //makes sure deploy orders go first 
        if (!(orderName._Equal("class Deploy") || MainGameLoop::deployOrderLeft == GameStart::players.size())) {
            MainGameLoop::deployOrderLeft++;
            return;
        }
        order->execute();
        player->getOrderList()->remove(index);
        //index++;
     }
    //return "";
}

bool MainGameLoop::checkOwnedContinent(Player* player, Continent* cont)
{
	for (Territory* terr : *cont->getTerritories()) {
		if (terr->getOwner()->getName() != player->getName()) {
			return false;
		}
	}
	return true;
}

bool MainGameLoop::priorityOrderList(Player* player) {
    bool check = false;
    int orderListSize = player->getOrderList()->getOrdersList().size();
    int index = orderListSize - 1;
    int j = 0;
    //need to reorder list to represent priority list
    while (check)
    {
        for (size_t i = j; i < orderListSize; i++)
        {
            string orderName = typeid(player->getOrderList()->getOrdersList().at(i)).name();

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

