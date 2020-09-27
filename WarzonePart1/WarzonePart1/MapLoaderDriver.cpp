#include "MapLoader.h"

int main()

{   MapLoader loader = MapLoader("sw_baltic.map");
    Map* map = loader.createMap();
    delete map;
}