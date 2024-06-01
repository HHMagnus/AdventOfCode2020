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

int main()
{
    // insert correct input
    int input = 123;
    string str = to_string(input);
    int length = str.length();
    vector<int> src;
    for (int i = 0; i < length; i++) {
        string s = str.substr(i, 1).c_str();
        int c = stoi(s);
        src.push_back(c);
    }

    int curr = src[0];

    for (int u = 0; u < 100; u++) {

        int idx = -1;
        for (int i = 0; i < length; i++) {
            if (src[i] == curr) {
                idx = i;
            }
        }
        int pick1 = src[(idx + 1) % length];
        int pick2 = src[(idx + 2) % length];
        int pick3 = src[(idx + 3) % length];

        int dest = curr -1;
        while (dest == 0 || dest == pick1 || dest == pick2 || dest == pick3) {
            dest--;
            if (dest <= 0) {
                dest = 9;
            }
        }

        vector<int> shuffle;

        for (auto x : src) {
            if (x == pick1 || x == pick2 || x == pick3) {
                continue;
            }
            shuffle.push_back(x);
            if (x == dest) {
                shuffle.push_back(pick1);
                shuffle.push_back(pick2);
                shuffle.push_back(pick3);
            }
        }

        src = shuffle;

        int n_idx = -1;
        for (int i = 0; i < length; i++) {
            if (src[i] == curr) {
                n_idx = i;
            }
        }

        curr = src[(n_idx+1) % length];
    }

    int start = -1;
    for (int i = 0; i < length; i++) {
        if (src[i] == 1) {
            start = i;
        }
    }

    string res;

    for (int i = 1; i < length; i++) {
        string x = to_string(src[(start + i) % length]);
        res += x;
    }

    cout << "Day 23 part 1: " << res << "\n";

    return 0;
}