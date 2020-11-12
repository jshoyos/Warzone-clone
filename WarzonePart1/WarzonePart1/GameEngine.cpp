#include "GameEngine.h"
#include<iostream>
#include<filesystem>
#include<string>

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
	GameStart::start();
	


}

void MainGameLoop::reinforcementPhase()
{
}

void MainGameLoop::issueOrderPhase()
{
}

void MainGameLoop::orderExecutionPhase()
{
}

