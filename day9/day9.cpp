#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <list>
#include <algorithm>
#include <set>
#include <iterator>
#include <map>
using namespace std;

list<long long> get_lines()
{
    string line;
    ifstream myfile("input.txt");
    list<long long> lines;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            lines.push_back(stoll(line));
        }
        myfile.close();
    }

    else
        cout << "Unable to open file";
    return lines;
}

bool preamble(long long number, list<long long>::iterator iter)
{
    set<long long> prev;
    for (int i = 0; i < 25; i++)
    {
        long long current = *iter;
        long long needed = number - current;
        if (prev.find(needed) != prev.end())
        {
            return true;
        }
        prev.insert(current);
        ++iter;
    }
    return false;
}

int main()
{
    list<long long> lines = get_lines();
    list<long long>::iterator current = lines.begin();
    for (int i = 0; i < 25; i++)
    {
        ++current;
    }
    list<long long>::iterator preambe_start = lines.begin();
    while(preamble(*current, preambe_start))
    {
        ++current;
        ++preambe_start;
    }
    long long invalid = *current;
    cout << "Day 1: " << *current << '\n';
    
    list<long long>::iterator start = lines.begin();
    list<long long>::iterator end = lines.begin();

    long long total = *end;
    ++end;
    total += *end;

    while(total != invalid)
    {
        if(total < invalid) {
            ++end;
            total += *end;
        }else {
            total -= *start;
            ++start;
        }
    }
    long long min = *start;
    long long max = *end;
    while(start != end)
    {
        long long x = *start;
        if(x < min) min = x;
        if(x > max) max = x;
        ++start;
    }
    cout << "Day 2: " << min+max << '\n';

    return 0;
}