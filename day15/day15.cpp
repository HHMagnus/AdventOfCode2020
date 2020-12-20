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

int number_th(int target)
{
    map<int, int> prevs;
    prevs.insert({0, 1});
    prevs.insert({13, 2});
    prevs.insert({1, 3});
    prevs.insert({16, 4});
    prevs.insert({6, 5});
    int turn = 7;
    int last_number = 17;
    while (turn <= target)
    {
        int new_num = 0;
        if (prevs.find(last_number) != prevs.end())
        {
            new_num = turn - prevs.find(last_number)->second - 1;
        }
        prevs[last_number] = turn - 1;

        last_number = new_num;
        turn++;
    }
    return last_number;
}

int main()
{
    cout << "Day 1: " << number_th(2020) << '\n';
    cout << "Day 2: " << number_th(30000000) << '\n';
    return 0;
}