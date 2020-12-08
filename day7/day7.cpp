#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <list>
#include <algorithm>
#include <set>
#include <iterator>
#include <map>
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

class ExtraBag
{
public:
    int number;
    string name;
};

ExtraBag to_extra_bag(string extra_bag)
{
    size_t space = extra_bag.find(" ");
    string number = extra_bag.substr(0, space);
    string name = extra_bag.substr(space + 1);
    name = name.substr(0, name.find(" bag"));

    ExtraBag extra;
    extra.name = name;
    extra.number = stoi(number);
    return extra;
}

class Bag
{
public:
    string name;
    list<ExtraBag> bags;
};

map<string, Bag> get_bags()
{
    list<string> lines = get_lines();
    map<string, Bag> bags;

    for (string line : lines)
    {
        Bag bag;

        size_t split1 = line.find(" bags contain");
        string main_bag = line.substr(0, split1);

        bag.name = main_bag;

        size_t last = split1 + 14;
        line = line.substr(last, line.size() - last);

        while (line.find(",") != string::npos)
        {
            size_t comma = line.find(",");
            string extra_bag = line.substr(0, comma);
            line = line.substr(comma + 2);
            bag.bags.push_back(to_extra_bag(extra_bag));
        }
        string last_bag = line.substr(0, line.find("."));
        if (!last_bag._Equal("no other bags"))
        {
            bag.bags.push_back(to_extra_bag(last_bag));
        }

        bags.insert({main_bag, bag});
    }

    return bags;
}

bool has_gold(map<string, Bag> &bags, Bag bag)
{
    for (list<ExtraBag>::iterator it = bag.bags.begin(); it != bag.bags.end(); ++it)
    {
        ExtraBag extra_bag = *it;
        if (extra_bag.name._Equal("shiny gold"))
        {
            return true;
        }
        Bag bag = bags.find(extra_bag.name)->second;
        if (has_gold(bags, bag))
        {
            return true;
        }
    }
    return false;
}

int bags_inside(map<string, Bag> &bags, string bag_name)
{
    Bag bag = bags.find(bag_name)->second;
    int total = 0;
    for (list<ExtraBag>::iterator it = bag.bags.begin(); it != bag.bags.end(); ++it)
    {
        ExtraBag extra_bag = *it;
        total += extra_bag.number;
        total += extra_bag.number * bags_inside(bags, extra_bag.name);
    }
    return total;
}

int main()
{
    map<string, Bag> bags = get_bags();
    int total = 0;
    for (map<string, Bag>::iterator it = bags.begin(); it != bags.end(); ++it)
    {
        Bag bag = it->second;
        total += has_gold(bags, bag);
    }
    cout << "Day 1: " << total << '\n';

    cout << "Day 2: " << bags_inside(bags, "shiny gold") << '\n';
    return 0;
}