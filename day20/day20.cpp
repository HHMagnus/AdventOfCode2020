#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>
#include <map>
#include <regex>
#include <bitset>
using namespace std;

vector<string> get_lines()
{
    string line;
    ifstream myfile("input.txt");
    vector<string> lines;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            lines.push_back(line);
        }
        myfile.close();
    }

    else
        cout << "Unable to open file";
    return lines;
}

class Tile
{
public:
    int id;
    vector<string> tiles;
    vector<string> sides;
};

vector<Tile> get_tiles(vector<string> lines)
{
    vector<Tile> tiles;
    for (int i = 0; i < lines.size() / 12; i++)
    {
        Tile tile;
        string id_line = lines.at(i * 12);
        tile.id = stoi(id_line.substr(id_line.find(" ") + 1, 4));
        for (int j = 1; j <= 10; j++)
        {
            string tile_line = lines.at(i * 12 + j);
            tile.tiles.push_back(tile_line);
        }
        string side1 = tile.tiles.at(0);
        string side2 = tile.tiles.at(9);
        string side3;
        for(int j = 0; j < 10; j++)
        {
            side3.append(tile.tiles.at(j).substr(0,1));
        }
        string side4;
        for(int j = 0; j < 10; j++)
        {
            side4.append(tile.tiles.at(j).substr(9,1));
        }

        tile.sides.push_back(side1);
        tile.sides.push_back(side2);
        tile.sides.push_back(side3);
        tile.sides.push_back(side4);

        string side1rev = side1;
        reverse(side1rev.begin(), side1rev.end());
        tile.sides.push_back(side1rev);

        string side2rev = side2;
        reverse(side2rev.begin(), side2rev.end());
        tile.sides.push_back(side2rev);

        string side3rev = side3;
        reverse(side3rev.begin(), side3rev.end());
        tile.sides.push_back(side3rev);

        string side4rev = side4;
        reverse(side4rev.begin(), side4rev.end());
        tile.sides.push_back(side4rev);

        tiles.push_back(tile);
    }
    return tiles;
}

void add_side(map<string, int> & unique_sides, string side)
{
    int x = 0;
    if(unique_sides.find(side) != unique_sides.end())
    {
        x = (*unique_sides.find(side)).second;
    }
    unique_sides[side] = x+1;
}

bool only_once(map<string,int> &unique_sides, string side)
{
    return (*unique_sides.find(side)).second == 1;
}

int main()
{
    vector<Tile> tiles = get_tiles(get_lines());

    map<string, int> unique_sides;

    for(Tile tile : tiles)
    {
        for(string side : tile.sides)
        {
            add_side(unique_sides, side);
        }
    }

    vector<int> corner_ids;

    for(Tile tile : tiles)
    {
        int uniques = 0;
        for(string side : tile.sides)
        {
            uniques += only_once(unique_sides, side);
        }
        if(uniques == 4)
        {
            corner_ids.push_back(tile.id);
        }
    }

    long long corner_product = 1;
    for(int corner_id : corner_ids)
    {
        corner_product *= corner_id;
    }
    cout << "Day 1: " << corner_product << '\n';

    return 0;
}