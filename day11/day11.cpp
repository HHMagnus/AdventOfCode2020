#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>
#include <map>
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

bool occupied(vector<string> lines, int x, int y)
{
    if (x < 0)
        return false;
    if (x >= lines.size())
        return false;
    if (y < 0)
        return false;
    if (y >= lines.at(0).size())
        return false;

    return lines.at(x).at(y) == '#';
}

vector<string> stabilize(vector<string> lines)
{
    vector<string> turned = lines;
    bool changed = false;

    int x = 0;
    int y = 0;

    for (int x = 0; x < lines.size(); x++)
    {
        for (int y = 0; y < lines.at(x).size(); y++)
        {
            char c = lines.at(x).at(y);
            if (c == 'L')
            {
                if (!occupied(lines, x - 1, y) 
                    && !occupied(lines, x, y - 1) 
                    && !occupied(lines, x + 1, y) 
                    && !occupied(lines, x, y + 1) 
                    && !occupied(lines, x - 1, y - 1) 
                    && !occupied(lines, x + 1, y - 1) 
                    && !occupied(lines, x + 1, y + 1) 
                    && !occupied(lines, x - 1, y + 1))
                {
                    turned.at(x)[y] = '#';
                    changed = true;
                }
            }
            else if (c == '#')
            {
                int adj_oc = occupied(lines, x - 1, y) 
                    + occupied(lines, x, y - 1) 
                    + occupied(lines, x + 1, y) 
                    + occupied(lines, x, y + 1) 
                    + occupied(lines, x - 1, y - 1) 
                    + occupied(lines, x + 1, y - 1) 
                    + occupied(lines, x + 1, y + 1) 
                    + occupied(lines, x - 1, y + 1);
                if (adj_oc >= 4)
                {
                    turned.at(x)[y] = 'L';
                    changed = true;
                }
            }
        }
    }

    if (changed)
    {
        return stabilize(turned);
    }
    return turned;
}

bool occupied2(vector<string> lines, int x, int y, int xdir, int ydir)
{
    if (x < 0)
        return false;
    if (x >= lines.size())
        return false;
    if (y < 0)
        return false;
    if (y >= lines.at(0).size())
        return false;

    if (lines.at(x).at(y) == '.')
    {
        return occupied2(lines, x + xdir, y + ydir, xdir, ydir);
    }

    return lines.at(x).at(y) == '#';
}

vector<string> stabilize2(vector<string> lines)
{
    vector<string> turned = lines;
    bool changed = false;

    int x = 0;
    int y = 0;

    for (int x = 0; x < lines.size(); x++)
    {
        for (int y = 0; y < lines.at(x).size(); y++)
        {
            char c = lines.at(x).at(y);
            if (c == 'L')
            {
                if (!occupied2(lines, x - 1, y, -1, 0) 
                    && !occupied2(lines, x, y - 1, 0, -1) 
                    && !occupied2(lines, x + 1, y, 1, 0) 
                    && !occupied2(lines, x, y + 1, 0, 1) 
                    && !occupied2(lines, x - 1, y - 1, -1, -1) 
                    && !occupied2(lines, x + 1, y - 1, 1, -1) 
                    && !occupied2(lines, x + 1, y + 1, 1, 1) 
                    && !occupied2(lines, x - 1, y + 1, -1, 1))
                {
                    turned.at(x)[y] = '#';
                    changed = true;
                }
            }
            else if (c == '#')
            {
                int adj_oc = occupied2(lines, x - 1, y, -1, 0) 
                    + occupied2(lines, x, y - 1, 0, -1) 
                    + occupied2(lines, x + 1, y, 1, 0) 
                    + occupied2(lines, x, y + 1, 0, 1) 
                    + occupied2(lines, x - 1, y - 1, -1, -1) 
                    + occupied2(lines, x + 1, y - 1, 1, -1) 
                    + occupied2(lines, x + 1, y + 1, 1, 1) 
                    + occupied2(lines, x - 1, y + 1, -1, 1);
                if (adj_oc >= 5)
                {
                    turned.at(x)[y] = 'L';
                    changed = true;
                }
            }
        }
    }

    if (changed)
    {
        return stabilize2(turned);
    }
    return turned;
}

int occupied_seats(vector<string> &lines)
{
    int occupied_seats = 0;
    for (int x = 0; x < lines.size(); x++)
    {
        for (int y = 0; y < lines.at(x).size(); y++)
        {
            char c = lines.at(x).at(y);
            occupied_seats += c == '#';
        }
    }
    return occupied_seats;
}

int main()
{
    vector<string> lines = get_lines();

    // Slow runtime for both these
    vector<string> stab1 = stabilize(lines);

    cout << "Day 1: " << occupied_seats(stab1) << '\n';

    vector<string> stab2 = stabilize2(lines);
    cout << "Day 2: " << occupied_seats(stab2) << '\n';

    return 0;
}