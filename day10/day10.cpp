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

list<int> get_lines()
{
    string line;
    ifstream myfile("input.txt");
    list<int> lines;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            lines.push_back(stoi(line));
        }
        myfile.close();
    }

    else
        cout << "Unable to open file";
    return lines;
}

int main()
{
    list<int> lines = get_lines();
    lines.sort();
    list<int>::iterator iter = lines.begin();
    int x = 0;
    int dif1 = 0;
    int dif3 = 1; // Starts at 1 for the last adapter
    while (iter != lines.end())
    {
        int y = *iter;
        if (y - x == 1)
        {
            dif1++;
        }
        else if (y - x == 3)
        {
            dif3++;
        }

        x = y;
        ++iter;
    }
    cout << "Day 1: " << dif1 * dif3 << '\n';
    return 0;
}