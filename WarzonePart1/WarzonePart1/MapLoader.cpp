#include "MapLoader.h"
#include <iostream>
#include <sstream>

// This will create a map
// If any issues occur, returns a null pointer
Map *MapLoader::createMap()
{

    
    Map *map = new Map();

    fstream stream(_fileName);

    // Test if the extension is right
    if (_fileName.find(".map") == string::npos)
    {
        cout << "Extension is wrong" << endl;
        return NULL;
    }

    // Test if stream is open, if not (ie: file not found) map cannot be created
    if (!stream.is_open())
    {
        cout << ">>> Map_Loader_Error: File not found. \n\n>>> System will now exit." << endl;
        exit(1);
        stream.close();
        return NULL;
    }

    else
    {
        vector<Continent *> continents;
        vector<Territory *> territories;

        // Tags will set the read mode, so it knows
        // where to get info in lines
        string tag_continents = "[continents]";
        string tag_countries = "[countries]";
        string tag_borders = "[borders]";
        string tag_files = "[files]";

        enum class Mode
        {
            other,
            territory,
            continent,
            border,
            files
        };

        vector<bool> tags_read(4, false);

        Mode mode = Mode::other;

        // For handling each token of every line
        vector<string> tokens;
        istringstream iss;
        string word;
        string line;

        // Not really needed, just to print a value
        Territory *current;

        // For assigning borders
        Territory *newTerritory;
        int current_id;

        // Values that will be used for object fields
        string name;
        int territory_id;
        int continent_id;
        int continent_count = 0;
        int territory_count = 0;


        // All of the functionality is in a single loop
        while (getline(stream, line))
        {

            // Set mode to handle different tags and start creating
            // members of map
            if (line == tag_continents)
            {
                getline(stream, line);
                mode = Mode::continent;
            }

            else if (line == tag_countries)
            {
                getline(stream, line);
                mode = Mode::territory;
            }

            else if (line == tag_borders)
            {
                getline(stream, line);
                mode = Mode::border;
            }

            else if (line == tag_files)
            {
                getline(stream, line);
                mode = Mode::files;
            }

            tokens = vector<string>();
            iss = istringstream(line);

            while (iss >> word)
                tokens.push_back(word);

            // skip newlines, skip possible duplicates of tags
            if (line.size() != 0 && line != tag_files && line != tag_continents
                && line != tag_countries && line != tag_borders)
            {

                switch (mode)
                {
                
                // Change mode to handle continents
                // Give each territory a continent id
                // Test if there are at least 1 tokens in each line
                case Mode::continent:

                    // test if line has enough tokens
                    if (tokens.size() == 0)
                    {
                        cout << ">>> Map_Loader_Error: Error with one continent in the file. \n>>> Map will be deleted and system will exit." << endl;
                        delete map;
                        exit(1);
                        return NULL;
                        
                    }

                    tags_read[0] = true;

                    continent_id = continent_count++;

                    name = tokens[0];

                    continents.push_back(new Continent(continent_id, name));
                    cout << *continents.back() << endl;
                    break;

                // Change mode to handle territories
                // Give each territory a continent id
                // Test if there are at least 3 tokens in each line
                case Mode::territory:

                    if (tokens.size() < 3)
                    {
                        cout << ">>> Map_Loader_Error: Error with one territory in the file.\n>>> Map will be deleted and system will exit." << endl;
                        delete map;
                        exit(1);
                        return NULL;
                    }

                    tags_read[1] = true;

                    territory_id = territory_count++;

                    continent_id = stoi(tokens[2]) - 1;
                    name = tokens[1];

                    // Does the continent id make sense?
                    if (continent_id >= continents.size()) {
                        cout << "\n>>> Map_Loader_Error: An invalid continent_id has been detected.\n>>> Map will be deleted and system will exit." << endl;
                        delete map;
                        exit(1);
                        return NULL;
                    }


                    territories.push_back(new Territory(territory_id, name, continent_id));
                    current = territories.back();
                    //cout << current->getId() << endl;
                    //cout << *territories.back() << endl;
                    break;

                // Change mode to handle borders
                // Give each territory a continent id
                // Test if there are more than 1 token in each line
                // Must be read LAST to work
                case Mode::border:

                    // Check whether territories were defined earlier
                    if (territories.size() == 0) {
                        cout << ">>> Map_Loader_Error: Territories and continents should be defined before borders.\n>>> Map will be deleted and system will exit." << endl;
                        delete map;
                        exit(1);
                        return NULL;
                    }

                    // Check if there are enough tokens 
                    else if (tokens.size() == 0)
                    {
                        cout << ">>> Map_Loader_Error: Error with one border in the file. \n>>> Map will be deleted and system will exit." << endl;
                        delete map;
                        exit(1);
                        return NULL;
                    }

                    // Check whether each border makes sense
                    for (string token : tokens) {
                        int id = stoi(token) - 1;
                        if (id >= territories.size() || id < 0)
                        {
                            cout << ">>> Map_Loader_Error: A border in the map is invalid.\n>>> Map will be deleted and system will exit." << endl;
                            delete map;
                            exit(1);
                            return NULL;
                        }
                            
                    }

                    tags_read[2] = true;


                    // first number is the territory to add borders to
                    // 3 2 3 11 ---> 3 is current_id, [2, 3, 11] are borders
                    current_id = stoi(tokens[0]) - 1;

                    newTerritory = territories[current_id];

                    // the rest are borders
                    cout << "\n>>> Linking " << newTerritory->getTerritoryName() << " to its neighbouring territories:"<< endl;
                    tokens.erase(tokens.begin());
                    for (int i = 0; i < tokens.size(); ++i)
                    {

                        // If tokens[i] is not good, fail

                        int adjacent_id = stoi(tokens[i]) - 1;
                        newTerritory->addBorder(territories[adjacent_id]);
                        //cout << territories[adjacent_id]->getTerritoryName() << endl;
                    }
                    break;
                
                // Check for a files tag (it must be present)
                // Doesnt really matter, here for completeness
                case Mode::files:
                    tags_read[3] = true;
                    break;
                };
            }
        }

        for (bool tag : tags_read)
        {
            //cout << tag;
            if (!tag)
            {
                for (auto territroy : territories) delete territroy;
                for (auto continent : continents) delete continent;
                delete map;

                //cout << "Were all tags read?" << tags_read[0] << " " << tags_read[1] << " " << tags_read[2] << " " << tags_read[3];

                stream.close();
                return NULL;
            }
        }


        // Add collected data to the map
        for (auto c : continents)
        {
            map->addContinent(c);
        }

        for (auto t : territories)
        {
            map->addTerritory(t);
        }

        stream.close();
        return map;
    }
}

MapLoader &MapLoader::operator=(const MapLoader &maploader)
{
    return *(new MapLoader(maploader));
}

// Default (empty string name)
MapLoader::MapLoader() : _fileName("")
{
}

// Parametrized constructor
MapLoader::MapLoader(string fileName) : _fileName(fileName)
{
}

// Set name for file
void MapLoader::setFileName(string fileName)
{
    _fileName = fileName;
}

// This should never be called since its a service not an object
MapLoader::MapLoader(const MapLoader &mapLoader)
{
    cout << "MapLoader Copy constructor" << endl;  
    //only for correction purposes
    //this->_fileName = mapLoader._fileName;
}

MapLoader::~MapLoader()
{
    cout << "MapLoader Destructor " << endl;
}

ostream &operator<<(ostream &os, const MapLoader &mapLoader)
{
    return os << "Loading map file: " << mapLoader._fileName << endl;
}
