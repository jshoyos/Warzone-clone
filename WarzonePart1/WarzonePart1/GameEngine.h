#include "MapLoader.h"
#include <vector>
#include <string.h>

#pragma once
class GameStart {
private:
	const static string PATH;
	static vector<string> maps;
	static int selectedOption;
	static void displayMapOptions();

public:
#pragma region methods
	static Map selectMap();
	static vector<Player*> createPlayers(int);
#pragma endregion
};

