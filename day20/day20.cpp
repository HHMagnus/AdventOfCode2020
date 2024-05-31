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
#include <cmath>
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
    bool unique;

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
    int unique_sides;

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

    bool fits_border(Tile& other) {
        return unique_sides == 1 && fits(other);
    }

    bool fits_center(Tile& other1, Tile& other2) {
        return unique_sides == 0 && fits(other1) && fits(other2);
    }

    bool fits(Tile& other) {
        for (Side &side: sides) {
            if (other.contains_side(side)) return true;
        }
        return false;
    }

    bool is_corner() {
        return unique_sides == 2;
    }

    bool is_border() {
        return unique_sides == 1;
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

    void print() {
        for (string t : tiles) {
            cout << t << "\n";
        }
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
            side.unique = unique;
            if (unique) uniques++;
        }
        tile.unique_sides = uniques;
    }

    return tiles;
}

Tile& get_id(vector<Tile>& tiles, int id) {
    for (Tile& t : tiles) {
        if (t.id == id) {
            return t;
        }
    }
    cout << "Cannot find id: " << id << "\n";
    exit( -1);
}

int main()
{
    vector<Tile> tiles = get_tiles(get_lines());

    vector<int> corner_ids;

    for(Tile &tile : tiles)
    {
        if (tile.is_corner())
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

    int length = sqrt(tiles.size());

    set<int> placed;

    int pos[length][length];
    pos[0][0] = corner_ids[0];
    placed.insert(corner_ids[0]);

    for (int i = 1; i < length; i++) {
        Tile& right = get_id(tiles, pos[0][i-1]);
        for (Tile& tile : tiles) {
            if (tile.id == right.id) continue;
            if (placed.find(tile.id) != placed.end()) continue;
            bool bc = (i < length-1 && tile.is_border()) || (i == length - 1 && tile.is_corner());
            if (bc && tile.fits(right)) {
                pos[0][i] = tile.id;
                placed.insert(tile.id);
                break;
            }
        }
    }

    for (int j = 1; j < length-1; j++) {
        for (int i = 0; i < length; i++) {
            bool flag = false;
            for (Tile& tile : tiles) {
                if (placed.find(tile.id) != placed.end()) continue;
                Tile& top = get_id(tiles, pos[j-1][i]);
                bool fit = tile.fits(top);
                if (i > 0) {
                    Tile& right = get_id(tiles, pos[j][i-1]);
                    fit = fit && tile.fits(right);
                }
                if (i == 0 || i == length-1) {
                    fit = fit && tile.is_border();
                }

                if (fit) {
                    pos[j][i] = tile.id;
                    placed.insert(tile.id);
                    flag = true;
                }
            }
            if (!flag) {
                cout << i << "," << j << ": Something went wrong!\n";
            }
        }
    }


    for (int i = 0; i < length; i++) {
        for (Tile& tile : tiles) {
            if (placed.find(tile.id) != placed.end()) continue;
            Tile& top = get_id(tiles, pos[length-2][i]);
            bool fit = tile.fits(top);
            if (i > 0) {
                Tile& right = get_id(tiles, pos[length-1][i-1]);
                fit = fit && tile.fits(right);
            }
            if (i > 0 && i != length-1) {
                fit = fit && tile.is_border();
            }
            if (i == 0 || i == length-1) {
                fit = fit && tile.is_corner();
            }

            if (fit) {
                pos[length-1][i] = tile.id;
                placed.insert(tile.id);
            }
        }
    }



    return 0;
}