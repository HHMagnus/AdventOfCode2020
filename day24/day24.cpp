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

pair<int, int> coord(string line) {
    pair<int, int> curr = make_pair(0, 0);
    while (line.size() > 0) {
        if (line.rfind("se", 0) == 0) {
            line = line.substr(2, line.size()-2);
            curr = make_pair(curr.first-1, curr.second+1);
        }
        if (line.rfind("sw", 0) == 0) {
            line = line.substr(2, line.size()-2);
            curr = make_pair(curr.first, curr.second+1);
        }
        if (line.rfind("ne", 0) == 0) {
            line = line.substr(2, line.size()-2);
            curr = make_pair(curr.first, curr.second-1);
        }
        if (line.rfind("nw", 0) == 0) {
            line = line.substr(2, line.size()-2);
            curr = make_pair(curr.first+1, curr.second-1);
        }
        if (line.rfind("e", 0) == 0) {
            curr = make_pair(curr.first-1, curr.second);
            line = line.substr(1, line.size()-1);
        }
        if (line.rfind("w", 0) == 0) {
            line = line.substr(1, line.size()-1);
            curr = make_pair(curr.first+1, curr.second);
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

    return 0;
}