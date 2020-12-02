#include "GameEngine.h"
using namespace std;
namespace fs = std::filesystem;


// Driver to test the functionality of any "domination map" or "conquest map"
// Result: success in running both type of files using an Adapter strategy. 

int main() {

	// First, the method asks to select a map from a list of maps contained in a folder "Maps" 
	// Then the method checks what type of file it is (ie: either a domination or conquest map).
	// And based on that, we will either create a MapLoader or a ConquestFileReaderAdapter object  
	// in order to execute the method createmap()... 
	// This method will create continents, territories and borders. And finally, we validate the Map.

	GameStart::selectMap();

}


