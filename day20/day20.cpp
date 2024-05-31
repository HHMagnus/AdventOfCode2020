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

class Side {
public:
    string normal;
    string rev;

    bool equal(Side &other) {
        return normal.compare(other.normal) == 0 || normal.compare(other.rev) == 0;
    }

    Side(string x) {
        normal = x;
        string revs = normal;
        reverse(revs.begin(), revs.end());
        rev = revs;
    }
};

class Tile
{
public:
    int id;
    vector<string> tiles;
    vector<Side> sides;

    Tile flip();
    Tile rotate();
    bool contains_side(Side &other) {
        for (Side &side : sides) {
            if (side.equal(other)) {
                return true;
            }
        }
        return false;
    }

    Tile(int idd, vector<string> tils) {
        id = idd;
        tiles = tils;

        string side1 = tiles.at(0);
        string side2 = tiles.at(9);
        string side3;
        for(int j = 0; j < 10; j++)
        {
            side3.append(tiles.at(j).substr(0,1));
        }
        string side4;
        for(int j = 0; j < 10; j++)
        {
            side4.append(tiles.at(j).substr(9,1));
        }

        sides.push_back(Side(side1));
        sides.push_back(Side(side2));
        sides.push_back(Side(side3));
        sides.push_back(Side(side4));
    }
};

vector<Tile> get_tiles(vector<string> lines)
{
    vector<Tile> tiles;
    for (int i = 0; i < lines.size() / 12; i++)
    {
        string id_line = lines.at(i * 12);
        int id = stoi(id_line.substr(id_line.find(" ") + 1, 4));
        vector<string> tils;
        for (int j = 1; j <= 10; j++)
        {
            string tile_line = lines.at(i * 12 + j);
            tils.push_back(tile_line);
        }

        tiles.push_back(Tile(id, tils));
    }
    return tiles;
}

int main()
{
    vector<Tile> tiles = get_tiles(get_lines());

    vector<int> corner_ids;

    for(Tile &tile : tiles)
    {
        int uniques = 0;
        for(Side& side : tile.sides)
        {
            bool unique = true;
            for (Tile &other : tiles) {
                if (other.id == tile.id) continue;
                if (!other.contains_side(side)) continue;
                unique = false;
            }
            if (unique) uniques++;
        }
        cout << uniques << "\n";
        if(uniques == 2)
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