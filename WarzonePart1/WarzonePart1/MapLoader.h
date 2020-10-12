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
    MapLoader();
    MapLoader(string);
    MapLoader(const MapLoader&);
    ~MapLoader();
    Map* createMap();
    bool setFileName();
    MapLoader& operator=(const MapLoader&);
    friend ostream& operator<<(ostream&, const MapLoader&);
};
ostream& operator<<(ostream&, const MapLoader&);