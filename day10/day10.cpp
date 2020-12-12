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

    int total1 = 0;

    iter = lines.begin();
    list<int> changes;
    x = 0;
    while (iter != lines.end())
    {
        int y = *iter;
        changes.push_back(y - x);

        x = y;
        ++iter;
    }
    changes.push_back(3);

    int t1 = 0;
    long long t = 1;
    for (list<int>::iterator it = changes.begin(); it != changes.end(); ++it)
    {
        int x = *it;

        if (x == 1)
        {
            t1++;
        }
        else if (x == 3)
        {
            if (t1 == 2)
            {
                t *= 2;
            }
            else if (t1 == 3)
            {
                t *= 4;
            }
            else if (t1 == 4)
            {
                t *= 7;
            }
            t1 = 0;
        }
    }

    cout << "Day 2: " << t << '\n';

    return 0;
}