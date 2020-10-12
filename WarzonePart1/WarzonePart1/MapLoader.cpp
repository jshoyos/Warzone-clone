#include "MapLoader.h"
#include <iostream>
#include <sstream>

Map *MapLoader::createMap()
{

    // random size for now
    Map *map = new Map(40);

    fstream stream(_fileName);

    if (!stream)
    {
        cout << "File didnt work";

        stream.close();
        return NULL;
    }

    else
    {
        vector<Continent *> continents;
        vector<Territory *> territories;

        string tag_continents = "[continents]";
        string tag_countries = "[countries]";
        string tag_borders = "[borders]";
        string tag_files = "[files]";

        enum Mode
        {
            other,
            territory,
            continent,
            border,
            files
        };

        vector<bool> tags_read(4, false);

        Mode mode = other;

        vector<string> tokens;
        istringstream iss;
        string word;
        string line;

        Territory *current;
        Territory *newTerritory;
        int current_id;


        string name;
        int territory_id;
        int continent_id;

        int continent_count = 0;
        int territory_count = 0;

        while (getline(stream, line))
        {

            // check if line has a tag and then skip it
            if (line == tag_continents)
            {
                getline(stream, line);
                mode = continent;
            }

            else if (line == tag_countries)
            {
                getline(stream, line);
                mode = territory;
            }

            else if (line == tag_borders)
            {
                getline(stream, line);
                mode = border;
            }

            else if (line == tag_files)
            {
                getline(stream, line);
                mode = files;
            }

            // this should be done ONLY if tag was not read

            tokens = vector<string>();
            iss = istringstream(line);

            while (iss >> word)
                tokens.push_back(word);

            // skip newlines, skip possible duplicates of tags
            if (line.size() != 0 && line != tag_files && line != tag_continents
                && line != tag_countries && line != tag_countries)
            {

                // Map loader will not be happy if it gets a bad line in a tag
                // it will crash
                switch (mode)
                {

                case continent:

                    tags_read[0] = true;

                    continent_id = continent_count++;
                    name = tokens[0];

                    // If tokens[0] is not good, fail

                    continents.push_back(new Continent(continent_id, name));
                    cout << *continents.back() << endl;
                    break;

                case territory:

                    tags_read[1] = true;

                    // If tokens[0 & 2] is not good, fail

                    territory_id = territory_count++;
                    continent_id = stoi(tokens[2]) - 1;

                    name = tokens[1];

                    territories.push_back(new Territory(territory_id, name, continent_id));
                    current = territories.back();
                    cout << current->getId() << endl;
                    cout << *territories.back() << endl;
                    break;

                case border:

                    tags_read[2] = true;

                    // first number is the territory to add borders to
                    // 3 2 3 11 ---> 3 is current_id, [2, 3, 11] are borders
                    current_id = stoi(tokens[0]) - 1;
                    newTerritory = territories[current_id];

                    // the rest are borders
                    cout << "Here are some borders of " << newTerritory->getTerritoryName() << " " << current_id << endl;
                    cout << "------------------------" << endl;
                    tokens.erase(tokens.begin());
                    for (int i = 0; i < tokens.size(); ++i)
                    {

                        // If tokens[i] is not good, fail

                        int adjacent_id = stoi(tokens[i]) - 1;
                        newTerritory->addBorder(territories[adjacent_id]);
                        cout << territories[adjacent_id]->getTerritoryName() << endl;
                    }
                    break;
                
                case files:
                    tags_read[3] = true;
                    break;
                };
            }
        }

        for (bool tag : tags_read)
        {
            cout << tag;
            if (!tag)
            {
                for (auto territroy : territories) delete territroy;
                for (auto continent : continents) delete continent;
                delete map;

                cout << "Were all tags read?" << tags_read[0] << " " << tags_read[1] << " " << tags_read[2] << " " << tags_read[3];

                stream.close();
                return NULL;
            }
        }

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

// Add readline method that will leave if tag is read

MapLoader::MapLoader() : _fileName()
{
}

MapLoader::MapLoader(string fileName) : _fileName(fileName)
{
}

void MapLoader::setFileName(string fileName)
{
    _fileName = fileName;
}

MapLoader::MapLoader(const MapLoader &mapLoader)
{
    cout << "Copy constructor... This should never be called since its a service not an object" << endl;
    //only for correction purposes
    //this->_fileName = mapLoader._fileName;
}

MapLoader::~MapLoader()
{
    cout << "Destructor for MapLoader" << endl;
}

ostream &operator<<(ostream &os, const MapLoader &mapLoader)
{
    return os << "Loading map file: " << mapLoader._fileName << endl;
}
