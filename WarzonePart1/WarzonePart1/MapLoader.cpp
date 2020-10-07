#include "MapLoader.h"
#include <iostream>
#include <sstream>

Map *MapLoader::createMap()
{

    // random size for now
    Map *map = new Map(40);

    fstream stream(_fileName);

    vector<Continent *> continents;
    vector<Territory *> territories;

    string tag_continents = "[continents]";
    string tag_countries = "[countries]";
    string tag_borders = "[borders]";
    string tag_other = "[other]";

    enum Mode
    {
        other,
        territory,
        continent,
        border
    };

    Mode mode = other;

    vector<string> tokens;
    istringstream iss;
    string word;
    string line;

    Territory *current;

    string name;
    int territory_id;
    int continent_id;

    int continent_count = 0;

    while (getline(stream, line))
    {

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

        // this should be done ONLY if tag was not read

        tokens = vector<string>();
        iss = istringstream(line);

        while (iss >> word)
            tokens.push_back(word);

        // skip newlines
        if (line.size() != 0)
        {

            switch (mode)
            {

            case continent:

                continent_id = continent_count++;
                name = tokens[0];

                continents.push_back(new Continent(continent_id, name));
                cout << *continents.back() << endl;
                break;

            case territory:

                territory_id = stoi(tokens[0]) - 1;
                continent_id = stoi(tokens[2]) - 1;

                name = tokens[1];

                territories.push_back(new Territory(territory_id, name, continent_id));
                current = territories.back();
                cout << current->getId() << endl;
                cout << *territories.back() << endl;
                break;

            case border:

                // first number is the territory to add borders to
                // 3 2 3 11 ---> 3 is current_id, [2, 3, 11] are borders
                int current_id = stoi(tokens[0]) - 1;
                Territory *territory = territories[current_id];

                // the rest are borders
                cout << "Here are some borders of " << territory->getTerritoryName() << " " << current_id << endl;
                cout << "------------------------" << endl;
                tokens.erase(tokens.begin());
                for (int i = 0; i < tokens.size(); ++i)
                {
                    int adjacent_id = stoi(tokens[i]) - 1;
                    territory->addBorder(territories[adjacent_id]);
                    cout << territories[adjacent_id]->getTerritoryName() << endl;
                }
                break;
            };
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

    // Release memory if it fails?

    stream.close();
    return map;
}

// Add readline method that will leave if tag is read

MapLoader::MapLoader(string fileName) : _fileName(fileName)
{
}