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

list<string> get_lines()
{
    string line;
    ifstream myfile("input.txt");
    list<string> lines;
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

int main()
{
    list<string> lines = get_lines();
    int accumulator = 0;
    auto iter = lines.begin();
    set<int> prev;
    int line = 0;
    while (prev.find(line) == prev.end())
    {
        cout << line << '\n';
        prev.insert(line);
        string inst = *iter;
        string inst1 = inst.substr(0, inst.find(" "));
        if (inst1._Equal("nop"))
        {
            line++;
            ++iter;
            continue;
        }
        else if (inst1._Equal("acc"))
        {
            accumulator += stoi(inst.substr(inst.find(" ") + 1));
            line++;
            ++iter;
            continue;
        }
        else if (inst1._Equal("jmp"))
        {
            int change = stoi(inst.substr(inst.find(" ") + 1));
            line += change;
            while (change > 0)
            {
                ++iter;
                change--;
            }
            while (change < 0)
            {
                --iter;
                change++;
            }
        }
        else
        {
            cout << "ERROR" << '\n';
            exit(-1);
        }
    }

    cout << "Day 1: " << accumulator << '\n';

    return 0;
}