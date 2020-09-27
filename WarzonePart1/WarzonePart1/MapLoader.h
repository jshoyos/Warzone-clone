#include "Map.h"
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class MapLoader 
{
    string _fileName;
    bool isFileValid();

public:
    MapLoader(string);
    Map* createMap();
    bool setFileName();

};