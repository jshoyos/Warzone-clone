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

	// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class GameStartup{
public:
		static void randomPlayerOrder();
		static void assignTerritories();
		static void initializeArmies();
		static void startupPhase();
};

class MainGameLoop {
private:
	static Publisher phasePublisher;
	static PhaseObserver* phaseObserver;
public:
	static void runMainloop();
	static void reinforcementPhase(Player*);
	static void issueOrderPhase(Player*);
	static void orderExecutionPhase(Player*);
	
#pragma region helperMethods
	static bool checkOwnedContinent(Player*, Continent*);
	static bool priorityOrderList(Player*);

#pragma endregion

};