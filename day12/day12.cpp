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

int main()
{
    vector<string> lines = get_lines();

    int x = 0;
    int y = 0;

    int dx = 1;
    int dy = 0;

    for (int i = 0; i < lines.size(); i++)
    {
        string s = lines.at(i);
        char d = s.at(0);
        int v = stoi(s.substr(1));

        if (d == 'N')
        {
            y += v;
        }
        else if (d == 'E')
        {
            x += v;
        }
        else if (d == 'S')
        {
            y -= v;
        }
        else if (d == 'W')
        {
            x -= v;
        }
        else if (d == 'F')
        {
            x += dx * v;
            y += dy * v;
        }
        else if ((d == 'R' && v == 90) || (d == 'L' && v == 270))
        {
            if (dx == 1)
            {
                dx = 0;
                dy = -1;
            }
            else if (dx == -1)
            {
                dx = 0;
                dy = 1;
            }
            else if (dy == 1)
            {
                dx = 1;
                dy = 0;
            }
            else
            {
                dx = -1;
                dy = 0;
            }
        }
        else if ((d == 'L' || d == 'R') && v == 180)
        {
            dx = -dx;
            dy = -dy;
        }
        else if ((d == 'R' && v == 270) || (d == 'L' && v == 90))
        {
            if (dx == 1)
            {
                dx = 0;
                dy = 1;
            }
            else if (dx == -1)
            {
                dx = 0;
                dy = -1;
            }
            else if (dy == 1)
            {
                dx = -1;
                dy = 0;
            }
            else
            {
                dx = 1;
                dy = 0;
            }
        }
        else
        {
            cout << "ERROR" << '\n';
            cout << s << '\n';
            return 0;
        }
    }

    cout << "Day 1: " << abs(x) + abs(y) << '\n';

    x = 10;
    y = 1;

    int ax = 0;
    int ay = 0;

    for (int i = 0; i < lines.size(); i++)
    {
        string s = lines.at(i);
        char d = s.at(0);
        int v = stoi(s.substr(1));

        if (d == 'N')
        {
            y += v;
        }
        else if (d == 'E')
        {
            x += v;
        }
        else if (d == 'S')
        {
            y -= v;
        }
        else if (d == 'W')
        {
            x -= v;
        }
        else if (d == 'F')
        {
            ax += x * v;
            ay += y * v;
        }
        else if ((d == 'R' && v == 90) || (d == 'L' && v == 270))
        {
            int temp_y = y;
            y = -x;
            x = temp_y;
        }
        else if ((d == 'L' || d == 'R') && v == 180)
        {
            x = -x;
            y = -y;
        }
        else if ((d == 'R' && v == 270) || (d == 'L' && v == 90))
        {
            int temp_y = y;
            y = x;
            x = -temp_y;
        }
        else
        {
            cout << "ERROR" << '\n';
            cout << s << '\n';
            return 0;
        }
    }
    
    cout << "Day 2: " << abs(ax) + abs(ay) << '\n';
    return 0;
}