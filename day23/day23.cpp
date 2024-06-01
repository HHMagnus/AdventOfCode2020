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

void part1(vector<int> src) {
    int length = src.size();
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
}

class Cub {
public:
    int cub;
    shared_ptr<Cub> next_cub;

    Cub(int c) {
        cub = c;
    }
};

void part2(vector<int> src) {
    int curr = src[0];

    for (int i = 10; i <= 1000000; i++) {
        src.push_back(i);
    }

    map<int, shared_ptr<Cub>> map;

    shared_ptr<Cub> last_cub;

    for (auto x : src) {
        shared_ptr<Cub> cub = shared_ptr<Cub>(new Cub(x));
        map[x] = cub;
        if (last_cub != nullptr)
            last_cub->next_cub = cub;
        last_cub = cub;
    }

    last_cub->next_cub = map[src[0]];

    for (int u = 0; u < 10000000; u++) {
        shared_ptr<Cub> cub = map[curr];
        int pick1 = cub->next_cub->cub;
        int pick2 = cub->next_cub->next_cub->cub;
        int pick3 = cub->next_cub->next_cub->next_cub->cub;

        int dest = curr - 1;
        while (dest == 0 || dest == pick1 || dest == pick2 || dest == pick3) {
            dest--;
            if (dest <= 0) {
                dest = 1000000;
            }
        }

        shared_ptr<Cub> dcub = map[dest];
        shared_ptr<Cub> dnext = dcub->next_cub;

        dcub->next_cub = cub->next_cub;

        shared_ptr<Cub> after = cub->next_cub->next_cub->next_cub->next_cub;

        cub->next_cub->next_cub->next_cub->next_cub = dnext;
        cub->next_cub = after;

        curr = cub->next_cub->cub;
    }

    shared_ptr<Cub> one = map[1];
    long long next = one->next_cub->cub;
    long long again = one->next_cub->next_cub->cub;

    string res = to_string(next * again);

    cout << "Day 23 part 2: " << res << "\n";
}

int main()
{
    int input = ;
    string str = to_string(input);
    int length = str.length();
    vector<int> src;
    for (int i = 0; i < length; i++) {
        string s = str.substr(i, 1).c_str();
        int c = stoi(s);
        src.push_back(c);
    }

    part1(src);
    part2(src);

    return 0;
}