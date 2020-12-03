#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
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

int trees_hit(list<string> lines, int right, int down) {
    int x = 0;
    int y = 0;
    int trees = 0;
    list<string>::iterator iter = lines.begin();
    while(y < lines.size()) {
        string line = *iter;
        if(line.c_str()[x] == '#'){
            trees += 1;
        }

        x = (x + right) % line.length();
        y += down;
        for(int i = 0; i < down; i++){
            iter++;
        }
    }
    return trees;
}

int main()
{
    list<string> lines = get_lines();
    int trees11 = trees_hit(lines, 1, 1);
    int trees31 = trees_hit(lines, 3, 1);
    int trees51 = trees_hit(lines, 5, 1);
    int trees71 = trees_hit(lines, 7, 1);
    int trees12 = trees_hit(lines, 1, 2);

    long long day2 = (long long)trees11 * (long long)trees31 * (long long)trees51 * (long long)trees71 * (long long)trees12;
    cout << "Day 1: " << trees31 << '\n';
    cout << "Day 2: " << day2 << '\n';

    return 0;
}