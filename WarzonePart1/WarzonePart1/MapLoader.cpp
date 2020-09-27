#include "MapLoader.h"
#include <iostream>
#include <sstream>

Map *MapLoader::createMap()
{

    // random size for now
    Map *map = new Map(5);

    fstream stream(_fileName);

    vector<Continent *> continents;
    vector<Territory *> territories;

    string tag_continents = "[continents]";
    string tag_countries = "[countries]";
    string tag_borders = "[borders]";

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

        tokens = vector<string>();
        iss = istringstream(line);

        while (iss >> word)
            tokens.push_back(word);

        // consume newlines

        if (&tokens[0] == NULL)
        {
            cout << "this is a newline" << endl;
            mode = other;
        }

        switch (mode)
        {

        case continent:
            // first arg is its name
            continents.push_back(new Continent(tokens[0]));
            cout << *continents.back() << endl;
            break;

        case territory:

            // first argument to constructor is its name, third is its Continent Id (which is an index)

            territories.push_back(new Territory(tokens[1], stoi(tokens[2]) - 1));
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

    // Release memory if it fails?

    stream.close();
    return map;
}

MapLoader::MapLoader(string fileName):_fileName(fileName)
{
}