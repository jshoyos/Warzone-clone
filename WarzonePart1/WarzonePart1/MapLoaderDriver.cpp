//#include "MapLoader.h"
//
//int main()
//
//{   
//    // test good file
//    MapLoader loader = MapLoader("sw_baltic.map");
//    /*Map* map1 = loader.createMap();*/
//    //map1->validate();
//
//     //// Test bad file (extension wrong)
//     //loader.setFileName("");
//     //Map* mapWrong1 = loader.createMap();
//
//     // // test another bad file (invalid file)
//     loader.setFileName(".map");
//     Map* mapWrong2 = loader.createMap();
//
//    // test bad file (not all tokens)
//    loader.setFileName("sw_baltic_bad.map");
//    Map* mapWrong3 = loader.createMap();
//}