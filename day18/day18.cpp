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
#include <tuple>
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

long long evaluate1(string &line);

long long next_num1(string &line)
{
    char c = line.at(0);
    line.erase(line.begin());
    if (c == '(')
        return evaluate1(line);
    else if (c == ' ')
        return next_num1(line);
    else
        return c-'0';
}

char next_op(string &line)
{
    char c = line.at(0);
    line.erase(line.begin());
    if (c == ' ')
        return next_op(line);
    return c;
}

long long evaluate1(string &line)
{
    long long x = next_num1(line);
    while (line.size() > 0)
    {
        char op = next_op(line);
        if(op == ')') return x;
        long long y = next_num1(line);

        //cout << x << op << y << '\n';
        x = op == '+' ? x + y : x * y;
    }
    return x;
}

long long evaluate2(string &line, bool par);

long long next_num2(string &line)
{
    char c = line.at(0);
    line.erase(line.begin());
    if (c == '(')
        return evaluate2(line, true);
    else if (c == ' ')
        return next_num2(line);
    else
        return c-'0';
}

long long evaluate2(string & line, bool par)
{
    long long x = next_num2(line);
    while(line.size() > 0)
    {
        string copy = line;
        char op = next_op(copy);
        if(!par && (op == ')' || op == '*')) return x;

        next_op(line);
        if(op == ')') return x;
        long long y = op == '+' ? next_num2(line) : evaluate2(line, false);

        //cout << x << op << y << '\n';

        x = op == '+' ? x+y : x*y;
    }
    return x;
}

int main()
{
    long long day1 = 0;
    for (auto line : get_lines())
    {
        day1 += evaluate1(line);
    }
    cout << "Day 1: " << day1 << '\n';

    long long day2 = 0;
    for(auto line : get_lines())
    {
        day2 += evaluate2(line, true);
    }
    cout << "Day 2: " << day2 << '\n';
    return 0;
}