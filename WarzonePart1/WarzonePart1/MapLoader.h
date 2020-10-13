#include "Map.h"
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class MapLoader 
{
    string _fileName;
    bool intToken(string intToken);
    bool strToken(string strToken);

public:
    MapLoader();
    MapLoader(string);
    MapLoader(const MapLoader&);
    ~MapLoader();
    Map* createMap();
    void setFileName(string fileName);
    MapLoader& operator=(const MapLoader&);
    friend ostream& operator<<(ostream&, const MapLoader&);
};
ostream& operator<<(ostream&, const MapLoader&);