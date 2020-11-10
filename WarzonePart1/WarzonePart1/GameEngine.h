#include "MapLoader.h"

#pragma once
class GameStart {
private:
	const static string PATH;
	static vector<string> maps;
	static int selectedOption;
	static Deck *deck;
	static MapLoader* mapLoader;
	static vector<Player*> players;

#pragma region helperMethods
	static void displayMapOptions();
	static int numberOfPlayersSelection();
	static void generateDeck();
#pragma endregion
public:
#pragma region methods
	static Map* selectMap();
	static void createPlayers();
	static void start();
#pragma endregion
};

