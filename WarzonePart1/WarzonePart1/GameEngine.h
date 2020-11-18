#include "MapLoader.h"
#include "GameObservers.h"

#pragma once
/// <summary>
/// Static class that provides the start service for the game
/// This class is used to setup the game such as loading the map, creating the deck and creating the players
/// </summary>
class GameStart {
private:
	const static string PATH; //root path for the maps folder containing all the maps files
	static vector<string> maps; //vector with all the maps in the directory name
	static int selectedOption; //The index of the map the player selects
	static MapLoader* mapLoader; //maploader that will load the selected map
#pragma region helperMethods
	static void displayMapOptions(); // helper method to display the map options from the files in the directory
	static int numberOfPlayersSelection(); //helper method to prompt the user for the number of players
	static void generateDeck();// helper method to generate a deck with a user selected size
#pragma endregion

public:
	static vector<Player*> players; //list of all created players
	static Map* map; //created map from the user selection
	static Deck* deck; //created deck
#pragma region methods
	static void toggleObserverOnOff(Publisher*, IObservable*, bool); //method used to toggle on or off the observer, this method uses the subscribe and unsubscribe method from the publisher
	static Map* selectMap(); //this method uses the displayMapOptions method to display the maps and prompt the user for a map and loads and generates the map
	static void createPlayers(); //method used to create the players
	static void start(); //this method wraps all the other methods to create the start service
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
	static Publisher statsPublisher;
	static PhaseObserver* phaseObserver;
	static GameStatisticsObserver* statsObserver;
	static int turn;
	static int deployOrderLeft;

public:
	static void runMainloop();
	static void reinforcementPhase(Player*);
	static void issueOrderPhase(Player*);
	static void orderExecutionPhase(Player*);
	
#pragma region helperMethods
	static bool checkOwnedContinent(Player*, Continent*);
	static void priorityOrderList(Player*);

#pragma endregion

};