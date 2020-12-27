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

class Rule
{
public:
    char type;
    // Single character
    char c;
    // Single sequence
    vector<int> rs;
    // Double sequence
    vector<int> rs1;
    vector<int> rs2;
};

vector<int> get_refs(string rem)
{
    vector<int> refs;

    while (rem.find(" ") != string::npos)
    {
        int num = stoi(rem.substr(0, rem.find(" ")));
        refs.push_back(num);
        rem = rem.substr(rem.find(" ") + 1);
    }
    refs.push_back(stoi(rem));

    return refs;
}

pair<int, Rule> get_rule(string line)
{
    int pos = stoi(line.substr(0, line.find(":")));

    // Character match rule
    if (line.find("\"") != string::npos)
    {
        line = line.substr(line.find("\"") + 1);
        Rule ruleC;
        ruleC.type = 'C';
        ruleC.c = line.c_str()[0];
        return {pos, ruleC};
    }
    // Double rule sequence
    else if (line.find("|") != string::npos)
    {
        line = line.substr(line.find(":") + 2);
        string before = line.substr(0, line.find("|") - 1);
        string after = line.substr(line.find("|") + 2);
        auto rs1 = get_refs(before);
        auto rs2 = get_refs(after);
        Rule ruleD;
        ruleD.type = 'D';
        ruleD.rs1 = rs1;
        ruleD.rs2 = rs2;
        return {pos, ruleD};
    }
    // Single rule sequence
    else
    {
        line = line.substr(line.find(":") + 2);
        auto rs = get_refs(line);
        Rule ruleS;
        ruleS.type = 'S';
        ruleS.rs = rs;
        return {pos, ruleS};
    }
}

map<int, Rule> get_rules(vector<string> lines)
{
    map<int, Rule> rules;
    for (string line : lines)
    {
        if (line._Equal(""))
            break;
        rules.insert(get_rule(line));
    }
    return rules;
}

pair<int, bool> match_rule(int rule_id, map<int, Rule> &rules, string text, int pos)
{
    Rule rule = (*rules.find(rule_id)).second;
    // Single character
    if (rule.type == 'C')
    {
        bool match = text.at(pos++) == rule.c;
        return {pos, match};
    }
    // Single sequence
    else if (rule.type == 'S')
    {
        for (int rid : rule.rs)
        {
            auto match = match_rule(rid, rules, text, pos);
            pos = match.first;
            if (!match.second)
                return {pos, false};
        }
        return {pos, true};
    }
    // Double sequence
    else
    {
        return {pos, false};
    }
}

bool match_rule(int rule_id, map<int, Rule> &rules, string text)
{
    auto match = match_rule(rule_id, rules, text, 0);
    return match.first == text.size() && match.second;
}

string to_regex(int rule_id, map<int, Rule> &rules)
{
    Rule rule = (*rules.find(rule_id)).second;
    if (rule.type == 'C')
    {
        string s;
        s += rule.c;
        return s;
    }
    else if (rule.type == 'S')
    {
        string s = "";
        for (int x : rule.rs)
        {
            s.append(to_regex(x, rules));
        }
        return s;
    }
    else if (rule.type == 'D')
    {
        string s = "(";
        for (int x : rule.rs1)
        {
            s.append(to_regex(x, rules));
        }
        s.append("|");
        for (int x : rule.rs2)
        {
            s.append(to_regex(x, rules));
        }
        s.append(")");
        return s;
    }
    return "";
}

int matches(regex ex, vector<string> lines)
{
    int matches = 0;
    for (string line : lines)
    {
        smatch match;
        matches += regex_match(line, match, ex);
    }
    return matches;
}

int main()
{
    vector<string> lines = get_lines();
    map<int, Rule> rules1 = get_rules(lines);

    int maxx = 0;
    for (pair<int, Rule> rule : rules1)
    {
        maxx = rule.first > maxx ? rule.first : maxx;
    }

    lines = get_lines();

    int pos_of_rule_8 = 124;
    int pos_of_rule_11 = 125;
    int end = 131;

    lines[pos_of_rule_8] = "8: 42 | " + to_string(maxx + 1);
    lines.insert(lines.begin() + end, "" + to_string(maxx + 1) + ": 42 42 | " + to_string(maxx + 2));
    lines.insert(lines.begin() + end + 1, "" + to_string(maxx + 2) + ": 42 42 42 | " + to_string(maxx + 3));
    lines.insert(lines.begin() + end + 2, "" + to_string(maxx + 3) + ": 42 42 42 42 | " + to_string(maxx + 4));
    lines.insert(lines.begin() + end + 3, "" + to_string(maxx + 4) + ": 42 42 42 42 42");
    lines[pos_of_rule_11] = "11: 42 31 | " + to_string(maxx + 5);
    lines.insert(lines.begin() + end + 4, "" + to_string(maxx + 5) + ": 42 42 31 31 | " + to_string(maxx + 6));
    lines.insert(lines.begin() + end + 5, "" + to_string(maxx + 6) + ": 42 42 42 31 31 31 | " + to_string(maxx + 7));
    lines.insert(lines.begin() + end + 6, "" + to_string(maxx + 7) + ": 42 42 42 42 31 31 31 31 | " + to_string(maxx + 8));
    lines.insert(lines.begin() + end + 7, "" + to_string(maxx + 8) + ": 42 42 42 42 42 31 31 31 31 31");
    map<int, Rule> rules2 = get_rules(lines);

    int start = 0;
    while (!lines.at(start++)._Equal(""))
    {
    }

    string ex1 = to_regex(0, rules1);
    string ex2 = to_regex(0, rules2);

    cout << "Day 1: " << matches(regex(ex1), lines) << '\n';
    cout << "Day 2: " << matches(regex(ex2), lines) << '\n';
    return 0;
}