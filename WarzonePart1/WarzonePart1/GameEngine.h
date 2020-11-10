#include "MapLoader.h"
#include <vector>
#include <string.h>

#pragma once
class GameStart {
private:
	const static string PATH;
	static vector<string> maps;
	static int selectedOption;
	static MapLoader* mapLoader;
	static vector<Player*> players;

#pragma region helperMethods
	static void displayMapOptions();
	static int numberOfPlayersSelection();
#pragma endregion
public:
#pragma region methods
	static Map* selectMap();
	static void createPlayers();
#pragma endregion
};

