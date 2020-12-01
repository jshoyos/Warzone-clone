#include "GameEngine.h"


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
    int numberOfPlayers = 0;
    cout << "Please enter the number of players [2-5]: ";
    cin >> numberOfPlayers;
    while (numberOfPlayers < 2 || numberOfPlayers > 5) {//|| typeid(numberOfPlayers)
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
        string name;int choice = 0;
        cout << "Enter player " << i + 1 << " name: ";
        cin >> name;
        cout << "Now choose a strategy from the list below." << endl;
        cout << "[0] HumanPlayerStrategy" << endl;
        cout << "[1] AggressivePlayerStrategy" << endl;
        cout << "[2] BenevolentPlayerStrategy" << endl;
        cout << "[3] NeutralPlayerStrategy" << endl;
        cin >> choice;
        switch (choice)
        {
        case 0:
            players.push_back(new Player(name, new HumanPlayerStrategy()));
            break;
        case 1:
            players.push_back(new Player(name, new AggressivePlayerStrategy()));
            break;
        case 2:
            players.push_back(new Player(name, new BenevolentPlayerStrategy()));
            break;
        case 3: 
            players.push_back(new Player(name, new NeutralPlayerStrategy()));
            break;
        }
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

Publisher MainGameLoop::publisher = Publisher();
PhaseObserver* MainGameLoop::phaseObserver = new PhaseObserver("phase");
GameStatisticsObserver* MainGameLoop::statsObserver = new GameStatisticsObserver("stats");

//runs the main loop for the game
void MainGameLoop::runMainloop()
{
    MainGameLoop::publisher.subscribe(MainGameLoop::phaseObserver);
	GameStart::start();	//sets up the initial parameters of the game
    bool observeCheck = false;
    bool continueToggle = false;
    //cout/cin do you want to toggle the following observers on and off
    do
    {
        cout << "Would you like to observe the phases of the game (1 for yes, 0 for no): ";
        cin >> observeCheck;
        GameStart::toggleObserverOnOff(&MainGameLoop::publisher, MainGameLoop::phaseObserver, observeCheck); 
        cout << "Would you like to observe the statistics of the game (1 for yes, 0 for no): ";
        cin >> observeCheck;
        GameStart::toggleObserverOnOff(&MainGameLoop::publisher, MainGameLoop::statsObserver, observeCheck);
        cout << "Are you sure about these choices? (0 for yes, 1 for no): ";
        cin >> continueToggle;
    } while (continueToggle);

    GameStartup::startupPhase();
   
    MainGameLoop::turn = 1;
   
	while (GameStart::players.size()!=1 ) { 
        //checks if player's lose and removes the players respectively
        bool check = false;
        for (Player* player : GameStart::players) {
            if (player->getTerritoryList()->size() == 0) {
                cout << "remove " << player->getName()<<" from game! You lose!" << endl;
                GameStart::players.erase(std::remove(GameStart::players.begin(), GameStart::players.end(), player), GameStart::players.end());
                delete player; player = NULL;
                check = true;
                MainGameLoop::publisher.notifyAll("stats", "");
                continue;
            }
        }
        //checks if only one player exists
        if (check == true) {
            continue;
        }
        if (MainGameLoop::turn == 1) {
        //The first turn will distribute the player's initial armies evenly to their respective territories
        for (Player* player : GameStart::players) {
            int armyNumber = 0;
            //on the first turn ditribute the armies evenly amongst the owned territories
                while (player->getReinforcementPool() != 0)
                {
                    for (Territory* terr : *player->getTerritoryList()) {
                        if (player->getReinforcementPool() == 0) {
                            break;
                        }
                        armyNumber = terr->getArmies();
                        terr->setArmies(++armyNumber);
                        player->setReinforcementPool(player->getReinforcementPool() - 1);
                    }
                }
            }
        }
        //Option to change players strategy
        //TODO: check memory leak
    /*    if (turn % 10 == 0) {
            int choice=0;
            cout << "You have the option to change a player's strategy" << endl;
            for (Player* player : GameStart::players) {
                cout << "For player: " << player->getName() << endl;
                cout << "Choose a strategy from the list below or choose 0 to keep same strategy" << endl;
                cout << "[1] HumanPlayerStrategy" << endl;
                cout << "[2] AggressivePlayerStrategy" << endl;
                cout << "[3] BenevolentPlayerStrategy" << endl;
                cout << "[4] NeutralPlayerStrategy" << endl;
                cin >> choice;
                switch (choice)
                {
                case 0: 
                    break;
                case 1:
                    player->setStrategy(new AggressivePlayerStrategy());
                    break;
                case 2:
                    player->setStrategy(new BenevolentPlayerStrategy());
                    break;
                case 3:
                    player->setStrategy(new NeutralPlayerStrategy());
                    break;
                }
            }
        }*/
        //Phase 1
		for (Player* player : GameStart::players) {
            MainGameLoop::publisher.notifyAll("phase", player->getName() + "'s Reinforcement Phase!");
            if (player->getTerritoryList()->empty()) {
                continue;
            }
            reinforcementPhase(player);
		}

        //Phase 2
		for (Player* player : GameStart::players) {
            MainGameLoop::publisher.notifyAll("phase", player->getName() + "'s IssueOrdering Phase!");
            if (player->getTerritoryList()->empty()) {
                continue;
            }
            issueOrderPhase(player);
		}
        
        //executes just the deploy orders of the players
        MainGameLoop::deployOrderLeft = 0;
        //Phase 3
        //Deploy order execution phase
        for (Player* player : GameStart::players) {
            MainGameLoop::publisher.notifyAll("phase", player->getName() + "'s Order Execution Phase!");
            if (player->getTerritoryList()->empty()) {
                continue;
            }
            orderExecutionPhase(player);
        }
        //Remaining orders execution phase 
        for (Player* player : GameStart::players) {

            if (player->getTerritoryList()->empty()) {
                continue;
            }
            orderExecutionPhase(player);
        }
        //removes players orders from list and contracts
        for (Player* player : GameStart::players) {
            player->clearContractList();
        }
        MainGameLoop::turn++;
	}
    vector<Territory*>* tempToAttack = GameStart::players.at(0)->toAttack();
    if (tempToAttack->size() !=0 )
    {
        cout << "conquering remain territories" <<endl;
        for (Territory* terr : *tempToAttack) {
            GameStart::players.at(0)->conquerTerritory(terr);
        }
    }
    delete tempToAttack; tempToAttack = NULL;
    MainGameLoop::publisher.notifyAll("stats", to_string(MainGameLoop::turn));

    ///Deleting remaining items in game
    cout << endl << endl <<"<<<Deleting items from the game.S";
    delete GameStart::players.at(0);GameStart::players.at(0) = NULL;
    delete GameStart::map; GameStart::map = NULL;
    delete GameStart::deck; GameStart::deck = NULL;
   
}
void MainGameLoop::reinforcementPhase(Player* player)
{
    //On turn 1 there should be no reinforcement Phase for the players
	double playerTerritoryNum = player->getTerritoryList()->size();
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
    srand(time(0));
    //initializing variables
    Territory* source = nullptr;
    Territory* target = nullptr;
    int max = 0, min = 0, randTerrIndex = 0, randomArmyNum = 0,count=0;
    
    int armyNumber = 0;
    //on the first turn ditribute the armies evenly amongst the owned territories
    if (MainGameLoop::turn == 1) {
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

        //checks if player is a neutral player
        if ((typeid(*player->getStrategy()).name()) == (typeid(NeutralPlayerStrategy).name())) {
            player->issueOrder("attack", player, nullptr, nullptr, nullptr, 0);
            return;
        }
        //----- First step is to Issue the deploy order -----\\
        
        //loops until there is no more army members in reinforcement pool

        while (player->getReinforcementPool() != 0) {

            //gets number of armies from players pool
            armyNumber = player->getReinforcementPool();
            //initialize variables to 0
            max = 0, min = 0, randTerrIndex = 0, randomArmyNum = 0;
            //Max index for defending territory list
            vector<Territory*>* tempDefendList = player->toDefend();
            max = tempDefendList->size();
            //chooses a random number for the index of the territory list (between 0 and list.size()-1)
            randTerrIndex = rand() % max;
            max = player->getReinforcementPool();
            //chooses a random number of armies to deploy (between 0 and total armies in reinforcement pool)
            randomArmyNum = rand() % max + 1;
            //choose target territory to deploy troops
            target = tempDefendList->at(randTerrIndex);

            //changes the troops number in the reinforcementPool
            player->setReinforcementPool(player->getReinforcementPool() - armyNumber);

            //issue deploy order (added to player's orderList)
            player->issueOrder("deploy", player, nullptr, nullptr, target, randomArmyNum);
            delete tempDefendList; tempDefendList = NULL;
        }
        
        // ------------------------------------------------------------------------------- \\

        //----- Second step is to for a player to issue an advance  -----\\
        

        int num = 0;
        int advanceStrategy = 0;
        num = rand() % 5 + 1;

        for (int i = 0; i < num;i++) {
            max = 0, min = 0, randTerrIndex = 0, randomArmyNum = 0; source = nullptr;count = 0;
            //randomly chooses between 1 (attack) and 0 (defend)
            advanceStrategy = rand() % 2;
            if (typeid(AggressivePlayerStrategy).name() == typeid(*player->getStrategy()).name())
            {
                advanceStrategy = 1;    //agressive player attacks if able to
            }
            //checks if the strategy is a BenevolentPlayerStrategy
            if ((typeid(*player->getStrategy()).name()) == (typeid(BenevolentPlayerStrategy).name()) )
            {
                advanceStrategy = 0;
            }

            //Attack Strategy
            if (advanceStrategy == 1) {          
                //max index for attack Territory list
                vector<Territory*>* tempAttackList = player->toAttack();
                max = tempAttackList->size();
                //random territory index from attack list
                if (max == 0) {
                    cout << player->getName()<<"'s attack list is empty" << endl;
                    break;
                }
                randTerrIndex = rand() % max;
                //Choose which owned territory will attack
                target = tempAttackList->at(randTerrIndex);
                delete tempAttackList; tempAttackList = NULL;
                //finds owned territory that is adjacent to attacking territory
                for (Territory* terr : *target->getAdjacent()) {
                    if (terr->getOwner() != NULL && terr->getOwner()->getName()._Equal(player->getName()) && terr->getArmies() != 0) {
                        //sets the source territory
                        source = terr;
                        break;
                    }
                }
                //if (source == nullptr) {
                //    cout << "territory chosen to attack has no ";
                //    //source = target->getAdjacent()->at(0);
                //    break;
                //}
                //max number of troops to send from selected territory. Minimum of 1 troop to send out
                max = source->getArmies(); 
                //random number of troops to attack with

                if (max == 0) {
                    randomArmyNum = 0;
                }
                else if (MainGameLoop::turn > 20 || typeid(AggressivePlayerStrategy).name() == typeid(*player->getStrategy()).name()) {
                    randomArmyNum = max;
                }
                else {
                    randomArmyNum = rand() % max + 1;
                }
                //issue advance attack order (added to player's orderList)
                player->issueOrder("advance", player, nullptr, source, target, randomArmyNum);
            }
            //Defense Strategy
            else if (advanceStrategy == 0) {
                //max index for defend Territory list
                vector<Territory*>* tempDefendList = player->toDefend();
                max = tempDefendList->size();
                //random territory index from defend list
                randTerrIndex = rand() % max;
                //Choose which owned territory will be defended
                target = tempDefendList->at(randTerrIndex);
                //finds owned territory that is adjacent to attacking territory
                for (Territory* terr : *target->getAdjacent()) {
                    if (terr->getOwner() != NULL && terr->getOwner()->getName()._Equal(player->getName())) {
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
                //issue advance defence order (added to player's orderList)
                player->issueOrder("advance", player, nullptr, source, target, randomArmyNum);
                delete tempDefendList; tempDefendList = NULL;
            }
        }
           
        // ------------------------------------------------------------------------------- \\

        //----- Third step is to play a card from players hand and issue its order -----\\
        

        //Playing a card for a human player
        if (typeid(*player->getStrategy()).name() == (typeid(HumanPlayerStrategy).name())) {
            int cardSlot = 0;
            cout << "choose card from hand." << endl;
            player->getHand()->showHand();
            cin >> cardSlot;

            Card* card = player->getHand()->handOfCards.at(cardSlot);
            vector<Territory*>* tempAttackList;
            vector<Territory*>* tempDefendList;
            int index = 0;
            switch (card->type)
            {
            //bomb
            case 0:
                cout << "You played the BOMB card! Choose a territory to bomb from your attacking list." << endl;
                tempAttackList = player->toAttack();
                card->play2(player, nullptr,nullptr,target, 0);
                delete tempAttackList; tempAttackList = NULL;
                break;
            //Reinforce
            case 1:
                cout << "You played the REINFORCE card! First choose a territory to reinforce, from your defend list." << endl;
                tempDefendList = player->toDefend();
                target = tempDefendList->at(0);
                cout << "Next choose the adjacent territory you wish to move your armies from." << endl;
                index = 0;
                for (Territory* terr : *target->getAdjacent()) {
                    cout << "[" << index << "] " << *terr;
                    index++;
                }
                cin >> index;
                source = target->getAdjacent()->at(index);
                cout << "Lastly select the number of armies you wish to advance. Please select a number between 0 and " << source->getArmies()<< endl;
                index = 0;
                cin >> index;
                card->play2(player, nullptr, source, target, index);
                delete tempDefendList; tempDefendList = NULL;
                break;
            //Blockade
            case 2:
                cout << "You played the BLOCKADE card! Choose a territory to blockade from your defend list." << endl;
                tempDefendList = player->toDefend();
                card->play2(player, nullptr, nullptr, target, 0);
                delete tempDefendList; tempDefendList = NULL;
                break;
            //Airlift
            case 3:
                cout << "You played the AIRLIFT card! First choose a territory to airlift to, from your defend list." << endl;
                tempDefendList = player->toDefend();
                target = tempDefendList->at(0);
                cout << "Next choose the territory you wish to move your armies from." << endl;
                delete tempDefendList; tempDefendList = NULL;
                tempDefendList = player->toDefend();
                source = tempDefendList->at(0);
                cout << "Lastly select the number of armies you wish to AIRLIFT. Please select a number between 0 and " << source->getArmies() << endl;
                index = 0;
                cin >> index;
                card->play2(player, nullptr, source, target, index);
                delete tempDefendList; tempDefendList = NULL;
                break;
            //Diplomacy
            case 4:break;
                cout << "You played the DIPLOMACY card! Choose a player you wish to negotiate with." << endl;
                int playerIndex = 0; Player* p2 = nullptr;
                for (Player* players : GameStart::players) {
                    if (players->getName() != player->getName()) {
                        cout << "[" << playerIndex << "] " << players->getName();
                        playerIndex++;
                    }    
                }
                playerIndex = 0;
                cin >> playerIndex;
                p2=GameStart::players.at(playerIndex);
                card->play2(player, p2, nullptr, nullptr, 0);
                break;
            }
        }
        else if(player->getHand()->getHandSize() != 0){

            Card* card = player->getHand()->handOfCards.at(0);
            //randomly chooses between 1 (attack) and 0 (defend)
            advanceStrategy = rand() % 2;
            //selecting target territory
            vector<Territory*>* tempDefendList = player->toDefend();
            vector<Territory*>* tempAttackList = player->toAttack();
            //Checks if attacklist is empty

            if (advanceStrategy == 1 
                && typeid(*player->getStrategy()).name() != typeid(BenevolentPlayerStrategy).name() 
                && tempAttackList->size() !=0) 
            {
                max = tempAttackList->size();
                randTerrIndex = rand() % max;
                target = tempAttackList->at(randTerrIndex);
                delete tempAttackList; tempAttackList = NULL;
            }
            else if (advanceStrategy == 0) {
                max = tempDefendList->size();
                randTerrIndex = rand() % max;
                target = tempDefendList->at(randTerrIndex);
            }
            

            //random selecting source territory
            max = tempDefendList->size();
            randTerrIndex = rand() % max;
            source = tempDefendList->at(randTerrIndex);

            //random number of armies
            max = source->getArmies();min = 1;
            if (max == 0) {
                randomArmyNum = 0;
            }
            else {
                randomArmyNum = rand() % max + min;
            }

            //select random player that is not self
            Player* p2 = nullptr;
            int playerIndex = 0;
            for (Player* randPlayer : GameStart::players) {
                if (randPlayer->getName() != player->getName()) {
                    p2 = GameStart::players.at(playerIndex);
                    break;
                }
                playerIndex++;
            }

            //implement random actions with random teritories and random armies
            cout << player->getName() << " plays a card and issues it to their OrderList" << endl;
            card->play2(player, p2, source, target, randomArmyNum);
            player->removeCardFromHand(card);
            GameStart::deck->insertCard(card);
            
            delete tempDefendList; tempDefendList = NULL;
        }
        
        // ------------------------------------------------------------------------------- \\
        
        priorityOrderList(player);  // takes the orders issued and puts them in the correct order based on there priority

        //display orders in correct order
        for (Order* order : player->getOrderList()->getOrdersList()) {
            string orderName = typeid(*order).name();
            if (orderName._Equal("class Deploy")) {
                cout << player->getName() + " issues deploy order." << endl;
            }
            else if (orderName._Equal("class Advance")) {
                cout << player->getName() + " issues advance order." << endl;
            }
            else if (orderName._Equal("class Airlift")) {
                cout << player->getName() + " issues airlift order." << endl;
            }
            else if (orderName._Equal("class Bomb")) {
                cout << player->getName() + " issues bomb order." << endl;
            }
            else if (orderName._Equal("class Blockade")) {
                cout << player->getName() + " issues blockade order." << endl;
            }
            else if (orderName._Equal("class Negotiate")) {
                cout << player->getName() + " issues negotiate order." << endl;
            }
            else {
                cout << "ERROR: unrecognized order!" << endl;
            }
        }
    }
}
void MainGameLoop::orderExecutionPhase(Player* player)
{
    //orderList size
    int orderListSize = player->getOrderList()->getOrdersList().size();
    int index = 0;
    int initialTerritoryListSize = player->getTerritoryList()->size();
   
    for (Order* order : player->getOrderList()->getOrdersList()) {
        string orderName = typeid(*order).name();
        //makes sure deploy orders go first 
        if (!(orderName._Equal("class Deploy") || MainGameLoop::deployOrderLeft == GameStart::players.size())) {
            MainGameLoop::deployOrderLeft++;
            return;
        }
        order->execute();
        if (orderName._Equal("class Deploy")) {
            player->getOrderList()->remove(index);  //removes deploy orders from the player's order list
        }
        if (player->getOrderList()->getOrdersList().size()==0) {
            MainGameLoop::deployOrderLeft++;
            return;
        }
        
     }
    for (Order* order : player->getOrderList()->getOrdersList()) {
        player->getOrderList()->remove(0);
    }
    int newTerritoryListSize = player->getTerritoryList()->size();
    if (newTerritoryListSize > initialTerritoryListSize)
    {
        player->addCard(GameStart::deck->draw());
        MainGameLoop::publisher.notifyAll("stats", "");
    }
}
bool MainGameLoop::checkOwnedContinent(Player* player, Continent* cont)
{
	for (Territory* terr : *cont->getTerritories()) {
        if (terr->getOwner() == NULL ||terr->getOwner()->getName() != player->getName()) {
			return false;
		}
	}
	return true;
}
void MainGameLoop::priorityOrderList(Player* player) {
    
    int size = player->getOrderList()->getOrdersList().size();

    // Sort player's order list via selection sort
    for (int i = 0; i < size-1; i++) {

        int current_max = 0;
        int current_index = i;

        for (int j = i+1; j < size; j++) {

            string orderName = typeid(*player->getOrderList()->getOrdersList().at(i)).name();

            if (orderName._Equal("class Deploy"))
            {
                if (3 > current_max)
                {
                    current_index = j;
                    current_max = 3;
                }
            }

            else if (orderName._Equal("class Airlift"))
            {
                if (2 > current_max) {
                    current_index = j;
                    current_max = 2;
                }
            }

            else if (orderName._Equal("class Blockade"))
            {
                if (1 > current_max) {
                    current_index = j;
                    current_max = 1;
                }
            }
        }
        // Swap at i and current_index
        player->getOrderList()->move(current_index, i);
    }

    for (int i = 0; i < (int)(size / 2); i++) {
        player->getOrderList()->move((size-1) - i, i);
    }
}
void MainGameLoop::clearVector(vector<Territory*>* territories)
{
    for (Territory* terr : *territories) {
        delete terr; terr = NULL;
    }
}

