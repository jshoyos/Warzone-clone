#include "GameEngine.h"
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

const string GameStart::PATH = "Maps/";
Map GameStart::selectMap()
{
    for (auto& entry : fs::directory_iterator(PATH)) {

    }
    return Map();
}

vector<Player*> GameStart::createPlayers(int)
{
    return vector<Player*>();
}
