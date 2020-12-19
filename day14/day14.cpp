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

void add_value_help(string mask, string pos, unsigned long long value, map<long long, unsigned long long> &mems2)
{
    size_t X = pos.find("X");
    if (X == string::npos)
    {
        long long p = stoll(pos, nullptr, 2);
        mems2[p] = value;
        return;
    }

    string pos1 = pos;
    pos1[X] = '1';
    string pos0 = pos;
    pos0[X] = '0';

    add_value_help(mask, pos1, value, mems2);
    add_value_help(mask, pos0, value, mems2);
}

void add_value(string mask, long long pos, unsigned long long value, map<long long, unsigned long long> &mems2)
{
    std::bitset<36> b(pos);
    string pos_string = b.to_string();
    for (int i = 0; i < 36; i++)
    {
        if (mask.at(i) != '0')
        {
            pos_string[i] = mask.at(i);
        }
    }
    add_value_help(mask, pos_string, value, mems2);
}

int main()
{
    map<long long, unsigned long long> mems;
    map<long long, unsigned long long> mems2;
    string mask;
    for (string line : get_lines())
    {
        if (line.find("[") == string::npos)
        {
            mask = line.substr(line.find("=") + 2);
        }
        else
        {
            // Day 1 part
            line = line.substr(line.find("[") + 1);
            long long pos = stoll(line.substr(0, line.find("]")));
            line = line.substr(line.find("=") + 2);

            unsigned long long value = stoull(line);

            unsigned long long AND = stoull(regex_replace(mask, regex("X"), "1"), 0, 2);
            unsigned long long OR = stoull(regex_replace(mask, regex("X"), "0"), 0, 2);
            value = value & AND;
            value = value | OR;

            mems[pos] = value;

            // Day 2 part
            add_value(mask, pos, stoull(line), mems2);
        }
    }

    unsigned long long total = 0;
    for (map<long long, unsigned long long>::iterator it = mems.begin(); it != mems.end(); it++)
    {
        total += it->second;
    }
    cout << "Day 1: " << total << '\n';

    unsigned long long total2 = 0;
    for (auto it = mems2.begin(); it != mems2.end(); it++)
    {
        total2 += it->second;
    }
    cout << "Day 2: " << total2 << '\n';
    return 0;
}