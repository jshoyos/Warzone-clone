#include "MapLoader.h"
#include "GameObservers.h"

#pragma once
class GameStart {
private:
	const static string PATH;
	static vector<string> maps;
	static int selectedOption;
	static MapLoader* mapLoader;
#pragma region helperMethods
	static void displayMapOptions();
	static int numberOfPlayersSelection();
	static void generateDeck();
#pragma endregion
public:
	static vector<Player*> players;
	static Map* map;
	static Deck* deck;
#pragma region methods
	static void toggleObserverOnOff(Publisher*, IObservable*, bool);
	static Map* selectMap();
	static void createPlayers();
	static void start();
#pragma endregion
};

class MainGameLoop {
private:
	//GameStart gs;
public:
	void runMainloop();
	void reinforcementPhase(Player*);
	void issueOrderPhase(Player*);
	void orderExecutionPhase(Player*);
	
#pragma region helperMethods
	bool checkOwnedContinent(Player* player, Continent* cont);

#pragma endregion

};