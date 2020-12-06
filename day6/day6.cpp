#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <list>
#include <algorithm>
#include <set>
#include <iterator>
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

int everyone_yes(list<string> group)
{
    int everybody;
    set<char> yes;
    list<string>::iterator iter = group.begin();
    string first = *iter;
    for (char &c : first)
    {
        yes.insert(c);
    }
    iter++;
    while (iter != group.end())
    {
        string next = *iter;
        set<char> additional_yes;
        for (char &c : next)
        {
            additional_yes.insert(c);
        }
        set<char> intersect;
        set_intersection(yes.begin(),yes.end(),additional_yes.begin(),additional_yes.end(), inserter(intersect, intersect.begin()));

        yes.clear();
        for(char i : intersect){
            yes.insert(i);
        }
        iter++;
    }
    return yes.size();
}

int main()
{
    list<string> lines = get_lines();
    // Day 1
    int count = 0;
    set<char> anyone_yes;
    for (string line : lines)
    {
        if (line._Equal(""))
        {
            count += anyone_yes.size(),
                anyone_yes.clear();
            continue;
        }
        for (char &c : line)
        {
            anyone_yes.insert(c);
        }
    }
    count += anyone_yes.size();
    cout << "Day 1: " << count << '\n';

    // Day 2
    count = 0;
    list<string> group;
    for (string line : lines)
    {
        if (line._Equal(""))
        {
            count += everyone_yes(group);
            group.clear();
            continue;
        }
        group.push_back(line);
    }
    count += everyone_yes(group);
    cout << "Day 2: " << count << '\n';
    return 0;
}