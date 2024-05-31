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

    bool exact(Side &other) {
        return normal.compare(other.normal) == 0;
    }

    Side(string x) {
        normal = x;
        string revs = normal;
        reverse(revs.begin(), revs.end());
        rev = revs;
    }
};

vector<string> str_rotate(vector<string> input) {
    int length = input.size();
    vector<string> nn;
    for (int x = 0; x < length; x++) {
        string s;
        for (int y = 0; y < length; y++) {
            s += input.at(y).at(length-1-x);
        }
        nn.push_back(s);
    }
    return nn;
}

vector<string> str_flip_horizontal(vector<string> input) {
    vector<string> nt;
    for (int i = input.size()-1; i >= 0; i--) {
        nt.push_back(input.at(i));
    }
    return nt;
}

vector<string> str_flip_vertical(vector<string> input) {
    vector<string> nt;
    for (string s : input) {
        string c = s;
        reverse(c.begin(), c.end());
        nt.push_back(c);
    }
    return nt;
}

class Tile
{
public:
    int id;
    vector<string> tiles;
    vector<Side> sides;
    int unique_sides;

    bool contains_side(Side &other) {
        for (Side &side : sides) {
            if (side.equal(other)) {
                return true;
            }
        }
        return false;
    }

    bool contains_exact(Side &other) {
        for (Side &side : sides) {
            if (side.exact(other)) {
                return true;
            }
        }
        return false;
    }

    Side& top() {
        return sides.at(0);
    }

    Side& bottom() {
        return sides.at(1);
    }

    Side& left() {
        return sides.at(2);
    }

    Side& right() {
        return sides.at(3);
    }

    Tile fix_top_left_corner() {
        if (top().unique && left().unique) {
            return copy();
        }
        if (top().unique && right().unique) {
            return rotate();
        }
        if (right().unique && bottom().unique) {
            return rotate().rotate();
        }
        if (bottom().unique && left().unique) {
            return rotate().rotate().rotate();
        }
        cout << "Could not find side\n";
        exit(-1);
    }

    Tile fix_to_right(Tile& right) {
        Tile rr = rotate_to_right(right);
        if (right.contains_exact(rr.left())) {
            return rr;
        }
        return rr.flip_horizontal();
    }

    Tile rotate_to_right(Tile &right) {
        if (right.contains_side(top())) {
            return rotate();
        }
        if (right.contains_side(this->right())) {
            return rotate().rotate();
        }
        if (right.contains_side(bottom())) {
            return rotate().rotate().rotate();
        }
        return copy();
    }

    Tile fix_to_top(Tile& top) {
        Tile tt = rotate_to_top(top);
        if (top.contains_exact(tt.top())) {
            return tt;
        }
        return tt.flip_vertical();
    }

    Tile rotate_to_top(Tile &top) {
        if (top.contains_side(right())) {
            return rotate();
        }
        if (top.contains_side(bottom())) {
            return rotate().rotate();
        }
        if (top.contains_side(left())) {
            return rotate().rotate().rotate();
        }
        return copy();
    }

    Tile rotate() {
        return Tile(id, str_rotate(tiles));
    }

    Tile flip_horizontal() {
        return Tile(id, str_flip_horizontal(tiles));
    }

    Tile flip_vertical() {
        return Tile(id, str_flip_vertical(tiles));
    }

    Tile copy() {
        return Tile(id, tiles);
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

set<pair<int, int>> sea_monster(int y, int x) {
    set<pair<int, int>> monster;
    //Top row
    monster.insert(make_pair(y+0, x+18));
    // Middle row
    monster.insert(make_pair(y+1, x+0));
    monster.insert(make_pair(y+1, x+5));
    monster.insert(make_pair(y+1, x+6));
    monster.insert(make_pair(y+1, x+11));
    monster.insert(make_pair(y+1, x+12));
    monster.insert(make_pair(y+1, x+17));
    monster.insert(make_pair(y+1, x+18));
    monster.insert(make_pair(y+1, x+19));
    // Bottom row
    monster.insert(make_pair(y+2, x+1));
    monster.insert(make_pair(y+2, x+4));
    monster.insert(make_pair(y+2, x+7));
    monster.insert(make_pair(y+2, x+10));
    monster.insert(make_pair(y+2, x+13));
    monster.insert(make_pair(y+2, x+16));
    return monster;
}

set<pair<int, int>> total(vector<string> combined) {
    set<pair<int,int>> contained;
    for (int i = 0; i < combined.size(); i++) {
        for (int j = 0; j < combined.size(); j++) {
            if (combined.at(i).at(j) == '#') {
                contained.insert(make_pair(i, j));
            }
        }
    }
    return contained;
}

set<pair<int, int>> without_monsters(set<pair<int, int>> contained, int size) {
    set<pair<int, int>> monsters;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            set<pair<int, int>> monster = sea_monster(y, x);
            bool fully_contained = true;
            for (pair<int,int> p : monster) {
                if (contained.find(p) == contained.end()) {
                    fully_contained = false;
                }
            }
            if (fully_contained) {
                monsters.insert(monster.begin(), monster.end());
            }
        }
    }
    return monsters;
}

int count_without_monsters(vector<string> combined) {
    set<pair<int,int>> contained = total(combined);
    set<pair<int,int>> without = without_monsters(contained, combined.size());
    return contained.size() - without.size();
}

int day2_res(vector<string> combined) {
    vector<int> scores;
    scores.push_back(count_without_monsters(combined));
    scores.push_back(count_without_monsters(str_flip_horizontal(combined)));
    scores.push_back(count_without_monsters(str_flip_vertical(combined)));
    vector<string> r1 = str_rotate(combined);
    scores.push_back(count_without_monsters(r1));
    scores.push_back(count_without_monsters(str_flip_horizontal(r1)));
    scores.push_back(count_without_monsters(str_flip_vertical(r1)));
    vector<string> r2 = str_rotate(r1);
    scores.push_back(count_without_monsters(r2));
    scores.push_back(count_without_monsters(str_flip_horizontal(r2)));
    scores.push_back(count_without_monsters(str_flip_vertical(r2)));
    vector<string> r3 = str_rotate(r2);
    scores.push_back(count_without_monsters(r3));
    scores.push_back(count_without_monsters(str_flip_horizontal(r3)));
    scores.push_back(count_without_monsters(str_flip_vertical(r3)));
    return *std::min_element(scores.begin(), scores.end());
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

    vector<vector<Tile>> matched;

    vector<Tile> first;
    first.push_back(get_id(tiles, pos[0][0]).fix_top_left_corner());

    for (int i = 1; i < length; i++) {
        Tile cc = get_id(tiles, pos[0][i]);
        first.push_back(cc.fix_to_right(first.at(i-1)));
    }

    matched.push_back(first);

    for (int j = 1; j < length; j++) {
        vector<Tile> next;
        for (int i = 0; i < length; i++) {
            Tile cc = get_id(tiles, pos[j][i]);
            next.push_back(cc.fix_to_top(matched.at(j-1).at(i)));
        }
        matched.push_back(next);
    }

    for (vector<Tile>& p : matched) {
        for (int i = 0; i < 10; i++) {
            for (Tile& t : p) {
                cout << t.tiles.at(i) << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    vector<string> combined;

    for (vector<Tile>& p : matched) {
        for (int i = 1; i < 9; i++) {
            string s;
            for (Tile& t: p) {
                s += t.tiles.at(i).substr(1, 8);
            }
            combined.push_back(s);
        }
    }

    for (string s : combined) {
        cout << s << "\n";
    }

    int res = day2_res(combined);

    cout << "Day 1: " << res << '\n';

    return 0;
}