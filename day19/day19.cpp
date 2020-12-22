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
#include <variant>
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

    while(rem.find(" ") != string::npos)
    {
        int num = stoi(rem.substr(0, rem.find(" ")));
        refs.push_back(num);
        rem = rem.substr(rem.find(" ")+1);
    }
    refs.push_back(stoi(rem));

    return refs;
}

pair<int, Rule> get_rule(string line)
{
    int pos = stoi(line.substr(0, line.find(":")));

    // Character match rule
    if(line.find("\"") != string::npos)
    {
        line = line.substr(line.find("\"")+1);
        Rule ruleC;
        ruleC.type = 'C';
        ruleC.c = line.c_str()[0];
        return {pos, ruleC};
    }
    // Double rule sequence
    else if(line.find("|") != string::npos)
    {
        line = line.substr(line.find(":")+2);
        string before = line.substr(0, line.find("|")-1);
        string after = line.substr(line.find("|")+2);
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
        line = line.substr(line.find(":")+2);
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
    for(string line : lines)
    {
        if(line._Equal("")) break;
        rules.insert(get_rule(line));
    }
    return rules;
}

pair<int, bool> match_rule(int rule_id, map<int, Rule> & rules, string text, int pos)
{
    Rule rule = (*rules.find(rule_id)).second;
    // Single character
    if(rule.type == 'C')
    {
        bool match = text.at(pos++) == rule.c;
        return {pos, match};
    }
    // Single sequence
    else if(rule.type == 'S')
    {
        for(int rid : rule.rs)
        {
            auto match = match_rule(rid, rules, text, pos);
            pos = match.first;
            if(!match.second) return {pos, false};
        }
        return {pos, true};
    }
    // Double sequence
    else
    {
        return {pos,false};
    }
}

bool match_rule(int rule_id, map<int, Rule> & rules, string text)
{
    auto match = match_rule(rule_id, rules, text, 0);
    return match.first == text.size() && match.second;
}

string to_regex(int rule_id, map<int, Rule> & rules)
{
    Rule rule = (*rules.find(rule_id)).second;
    if(rule.type == 'C')
    {
        string s;
        s+=rule.c;
        return s;
    }
    else if (rule.type == 'S')
    {
        string s = "";
        for(int x : rule.rs)
        {
            s.append(to_regex(x, rules));
        }
        return s;
    }
    else if (rule.type == 'S')
    {
        string s = "";
        for(int x : rule.rs1)
        {
            s.append(to_regex(x, rules));
        }
        for(int x : rule.rs2)
        {
            s.append(to_regex(x, rules));
        }
        return s;
    }
    return "";
}

int main()
{
    vector<string> lines = get_lines();
    map<int, Rule> rules = get_rules(lines);

    int start = 0;
    while(!lines.at(start++)._Equal("")){}

    cout << to_regex(0, rules) << '\n';

    /*int matches = 0;
    for(int i = start; i < lines.size(); i++)
    {
        string line = lines.at(i);
        matches += match_rule(0, rules, line);
    }
    cout << "Day 1: " << matches << '\n';*/
    return 0;
}