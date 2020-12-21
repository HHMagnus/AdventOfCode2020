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

bool match_rule(pair<pair<int, int>, pair<int, int>> rule, int num)
{
    return (rule.first.first <= num && num <= rule.first.second) || (rule.second.first <= num && num <= rule.second.second);
}

int sum_errors(vector<pair<pair<int, int>, pair<int, int>>> rules, vector<int> numbers)
{
    int sum = 0;

    for (int num : numbers)
    {
        if (!any_of(rules.begin(), rules.end(), [&num](auto rule) { return match_rule(rule, num); }))
        {
            sum += num;
        }
    }

    return sum;
}

int main()
{
    vector<string> lines = get_lines();
    int i = 0;
    vector<pair<pair<int, int>, pair<int, int>>> rules;

    string line;
    while (!(line = lines.at(i++))._Equal(""))
    {
        line = line.substr(line.find(":") + 2);
        int f1 = stoi(line.substr(0, line.find("-")));
        line = line.substr(line.find("-") + 1);
        int f2 = stoi(line.substr(0, line.find(" ")));
        line = line.substr(line.find(" or ") + 4);

        int o1 = stoi(line.substr(0, line.find("-")));
        line = line.substr(line.find("-") + 1);
        int o2 = stoi(line);

        rules.push_back({{f1, f2}, {o1, o2}});
    }

    string my_ticket = lines.at(i + 1);
    vector<int> my_numbers;
    while (my_ticket.find(",") != string::npos)
    {
        my_numbers.push_back(stoi(my_ticket.substr(0, my_ticket.find(","))));
        my_ticket = my_ticket.substr(my_ticket.find(",") + 1);
    }
    my_numbers.push_back(stoi(my_ticket));

    i += 4;

    vector<vector<int>> input;

    while (i < lines.size())
    {
        line = lines.at(i++);
        vector<int> ff;
        while (line.find(",") != string::npos)
        {
            ff.push_back(stoi(line.substr(0, line.find(","))));
            line = line.substr(line.find(",") + 1);
        }
        ff.push_back(stoi(line));
        input.push_back(ff);
    }

    vector<vector<int>> valid_input;

    // Day 1

    int sum = 0;
    for (auto ff : input)
    {
        int se = sum_errors(rules, ff);
        sum += se;

        if (se == 0)
        {
            valid_input.push_back(ff);
        }
    }

    cout << "Day 1: " << sum << '\n';

    // Day 2

    // rule -> rows
    vector<vector<int>> matches;
    for (int i = 0; i < rules.size(); i++)
    {
        vector<int> rows;
        matches.push_back(rows);
    }

    for (int j = 0; j < rules.size(); j++)
    {
        auto rule = rules.at(j);
        for (int i = 0; i < rules.size(); i++)
        {
            if (all_of(valid_input.begin(), valid_input.end(), [rule, i](auto v) { return match_rule(rule, v.at(i)); }))
            {
                matches.at(j).push_back(i);
            }
        }
    }

    vector<pair<int, int>> rule_to_row;

    for (int j = 0; j < matches.size(); j++)
    {
        for (int i = 0; i < matches.size(); i++)
        {
            if (matches.at(i).size() == 1)
            {
                int row = matches.at(i).at(0);

                rule_to_row.push_back({i, row});

                for (auto &match : matches)
                {
                    if (find(match.begin(), match.end(), row) != match.end())
                    {
                        match.erase(find(match.begin(), match.end(), row));
                    }
                }
                break;
            }
        }
    }

    sort(rule_to_row.begin(), rule_to_row.end(), [](auto x1, auto x2) { return x1.first < x2.first; });

    long long day2 = 1;

    for (int i = 0; i < 6; i++)
    {
        day2 *= my_numbers.at(rule_to_row.at(i).second);
    }

    cout << "Day 2: " << day2 << '\n';

    return 0;
}