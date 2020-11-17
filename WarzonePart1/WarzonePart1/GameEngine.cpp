#include "GameEngine.h"
#include<iostream>
#include<filesystem>
#include<string>
#include <vector>
#include <random>

using namespace std;
namespace fs = std::filesystem;

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
