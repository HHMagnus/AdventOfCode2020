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
    long long start = stoll(lines.at(0));
    string line2 = lines.at(1);

    vector<string> busses;
    while (line2.find(",") != string::npos)
    {
        int split = line2.find(",");
        busses.push_back(line2.substr(0, split));
        line2 = line2.substr(split + 1);
    }
    busses.push_back(line2);

    vector<int> num_busses;
    for (string numb : busses)
    {
        if (!numb._Equal("x"))
        {
            num_busses.push_back(stoi(numb));
        }
    }

    long long run = start;
    int num;
    while ((num = [&] {
               for (int num : num_busses)
               {
                   if (run % num == 0)
                   {
                       return num;
                   }
               }
               run++;
               return -1;
           }()) == -1)
    {
    }
    cout << "Day 1: " << num * (run-start) << '\n';

    long long day2 = 100000000000000;
    long long jump = 1;

    for (int i = 0; i < busses.size(); i++)
    {
        string num = busses.at(i);
        if (num == "x")
        {
            continue;
        }
        while((day2 + i) % stoi(num) != 0)
        {
            day2 += jump;
        }
        jump *= stoi(num);
    }

    cout << "Day 2: " << day2 << '\n';

    return 0;
}