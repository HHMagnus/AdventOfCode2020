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

pair<int, int> se(pair<int,int> curr) {
    return make_pair(curr.first-1, curr.second+1);
}

pair<int, int> sw(pair<int,int> curr) {
    return make_pair(curr.first, curr.second+1);
}

pair<int, int> ne(pair<int,int> curr) {
    return make_pair(curr.first, curr.second-1);
}

pair<int, int> nw(pair<int,int> curr) {
    return make_pair(curr.first+1, curr.second-1);
}

pair<int, int> e(pair<int,int> curr) {
    return make_pair(curr.first-1, curr.second);
}

pair<int, int> w(pair<int,int> curr) {
    return make_pair(curr.first+1, curr.second);
}

pair<int, int> coord(string line) {
    pair<int, int> curr = make_pair(0, 0);
    while (line.size() > 0) {
        if (line.rfind("se", 0) == 0) {
            line = line.substr(2, line.size()-2);
            curr = se(curr);
        }
        if (line.rfind("sw", 0) == 0) {
            line = line.substr(2, line.size()-2);
            curr = sw(curr);
        }
        if (line.rfind("ne", 0) == 0) {
            line = line.substr(2, line.size()-2);
            curr = ne(curr);
        }
        if (line.rfind("nw", 0) == 0) {
            line = line.substr(2, line.size()-2);
            curr = nw(curr);
        }
        if (line.rfind("e", 0) == 0) {
            line = line.substr(1, line.size()-1);
            curr = e(curr);
        }
        if (line.rfind("w", 0) == 0) {
            line = line.substr(1, line.size()-1);
            curr = w(curr);
        }
    }
    return curr;
}

int main()
{
    vector<string> input = get_lines();

    set<pair<int, int>> blacks;

    for (auto x : input) {
        pair<int, int> c = coord(x);
        if (blacks.find(c) != blacks.end()) {
            blacks.erase(c);
        }
        else {
            blacks.insert(c);
        }
    }

    cout << "Day 24 part 1: " << blacks.size() << "\n";

    for (int day = 0; day < 100; day++) {
        set<pair<int, int>> new_blacks;

        set<pair<int, int>> considered;
        for (auto x : blacks) {
            considered.insert(x);
            considered.insert(e(x));
            considered.insert(w(x));
            considered.insert(se(x));
            considered.insert(sw(x));
            considered.insert(ne(x));
            considered.insert(nw(x));
        }

        for (auto x : considered) {
            set<pair<int, int>> neigh;
            neigh.insert(e(x));
            neigh.insert(w(x));
            neigh.insert(se(x));
            neigh.insert(sw(x));
            neigh.insert(ne(x));
            neigh.insert(nw(x));

            int adjacent = 0;
            for (auto a : neigh) {
                if (blacks.find(a) != blacks.end())
                    adjacent++;
            }

            bool is_black = blacks.find(x) != blacks.end();

            if (is_black && adjacent != 0 && adjacent < 3) {
                new_blacks.insert(x);
            }

            if (!is_black && adjacent == 2) {
                new_blacks.insert(x);
            }
        }

        blacks = new_blacks;
    }

    cout << "Day 24 part 2: " << blacks.size() << "\n";

    return 0;
}