#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <list>
#include <algorithm>
#include <set>
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

list<list<pair<string, string>>> get_cards(list<string> lines)
{
    list<list<pair<string, string>>> all_lists;

    list<pair<string, string>> clist;
    for (string line : lines)
    {
        if (line == "")
        {
            all_lists.push_back(clist);
            list<pair<string, string>> new_list;
            clist = new_list;
        }

        while (line.length() > 0)
        {
            string x = line.substr(0, line.find(':'));
            string y = line.substr(line.find(':') + 1);
            y = y.substr(0, y.find(' '));
            clist.push_back({x, y});
            size_t next = line.find(' ');
            if (next == string::npos)
            {
                break;
            }
            line = line.substr(next + 1);
        }
    }
    all_lists.push_back(clist);

    return all_lists;
}

bool contains_field(string field, list<pair<string, string>> passport)
{
    for (pair<string, string> pfield : passport)
    {
        if (pfield.first._Equal(field))
        {
            return true;
        }
    }
    return false;
}

bool contains_fields(list<string> required_fields, list<pair<string, string>> passport)
{
    for (string required_field : required_fields)
    {
        if (!contains_field(required_field, passport))
        {
            return false;
        }
    }
    return true;
}

bool field_valid(pair<string, string> field)
{
    if (field.first._Equal("byr"))
    {
        int x = stoi(field.second);
        return 1920 <= x && x <= 2002;
    }
    else if (field.first._Equal("iyr"))
    {
        int x = stoi(field.second);
        return 2010 <= x && x <= 2020;
    }
    else if (field.first._Equal("eyr"))
    {
        int x = stoi(field.second);
        return 2020 <= x && x <= 2030;
    }
    else if (field.first._Equal("hgt"))
    {
        if (field.second.find("cm") != string::npos)
        {
            int x = stoi(field.second.substr(0, field.second.size() - 2));
            return 150 <= x && x <= 193;
        }
        else if (field.second.find('in') != string::npos)
        {
            int x = stoi(field.second.substr(0, field.second.size() - 2));
            return 59 <= x && x <= 76;
        }
        else
        {
            return false;
        }
    }
    else if (field.first._Equal("hcl"))
    {
        if (field.second.c_str()[0] != '#')
        {
            return false;
        }
        try
        {
            stoi(field.second.substr(1), nullptr, 16);
        }
        catch (exception &err)
        {
            return false;
        }
    }
    else if (field.first._Equal("ecl"))
    {
        string ecl = field.second;
        return ecl._Equal("amb") ||
            ecl._Equal("blu") ||
            ecl._Equal("brn") ||
            ecl._Equal("gry") ||
            ecl._Equal("grn") ||
            ecl._Equal("hzl") ||
            ecl._Equal("oth");
    }
    else if (field.first._Equal("pid"))
    {
        return field.second.size() == 9 && 
            field.second.find_first_not_of("0123456789") == string::npos;
    }
    else if (field.first._Equal("cid"))
    {
        return true;
    }
    else
    {
        return false;
    }
    return true;
}

bool fields_valid(list<pair<string, string>> fields)
{
    for (pair<string, string> field : fields)
    {
        if (!field_valid(field))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    list<string> lines = get_lines();
    list<string> required_fields = {
        "byr",
        "iyr",
        "eyr",
        "hgt",
        "hcl",
        "ecl",
        "pid"
        //"cid"
    };
    int passportsFieldsExists = 0;
    int passportsFieldsValid = 0;

    list<list<pair<string, string>>> cards = get_cards(lines);
    for (list<pair<string, string>> passport : cards)
    {
        // Day 1
        if (contains_fields(required_fields, passport))
        {
            passportsFieldsExists += 1;
        }
        else
        {
            // Not valid for day 2
            continue;
        }

        // Day 2
        if (fields_valid(passport))
        {
            passportsFieldsValid += 1;
        }
    }
    cout << "Day 1: " << passportsFieldsExists << '\n';
    cout << "Day 2: " << passportsFieldsValid << '\n';

    return 0;
}