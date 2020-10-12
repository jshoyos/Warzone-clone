#include "MapLoader.h"

int main()

{   MapLoader loader = MapLoader("sw_baltic.map");
    Map* map1 = loader.createMap();
    map1->validate();
    delete map1;

    // test good file

    loader = MapLoader("sw_baltic.map");
    Map* map2 = loader.createMap();
    map2->validate();

    // test bad file (doesnt have all tags)

    loader = MapLoader("sw_baltic.map");
    Map* map3 = loader.createMap();

    // test another good file

    // test another bad file (invalid file)


}