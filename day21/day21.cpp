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

class Item
{
public:
    vector<string> ingredients;
    vector<string> allergens;
};

vector<string> parse_spaces(string line)
{
    vector<string> words;
    while (line.find(" ") != string::npos)
    {
        string word = line.substr(0, line.find(" "));
        word.erase(std::remove(word.begin(), word.end(), ','), word.end());
        words.push_back(word);

        line = line.substr(line.find(" ") + 1);
    }
    words.push_back(line);
    return words;
}

Item parse_item(string line)
{
    Item item;

    string ingredients = line.substr(0, line.find("(") - 1);
    item.ingredients = parse_spaces(ingredients);

    string allergens = line.substr(line.find("(") + 1);
    allergens = allergens.substr(0, allergens.size() - 1);
    item.allergens = parse_spaces(allergens);
    item.allergens.erase(item.allergens.begin());

    return item;
}

vector<Item> parse_items(vector<string> lines)
{
    vector<Item> items;
    for (string line : lines)
    {
        Item item = parse_item(line);
        items.push_back(item);
    }
    return items;
}

int main()
{
    vector<Item> items = parse_items(get_lines());

    map<string, vector<string>> allergens_to_ingrediense;
    for (Item item : items)
    {
        for (string allergen : item.allergens)
        {
            if (allergens_to_ingrediense.find(allergen) == allergens_to_ingrediense.end())
            {
                allergens_to_ingrediense[allergen] = item.ingredients;
                continue;
            }
            vector<string> prev_ingrediense = allergens_to_ingrediense.find(allergen)->second;
            vector<string> new_ingrediense = item.ingredients;

            vector<string> combination;
            for (string prev : prev_ingrediense)
            {
                if (count(new_ingrediense.begin(), new_ingrediense.end(), prev))
                {
                    combination.push_back(prev);
                }
            }

            allergens_to_ingrediense[allergen] = combination;
        }
    }

    int matches = 0;
    for (Item item : items)
    {
        for (string ingrediense : item.ingredients)
        {
            bool maybe = false;
            for (auto ai : allergens_to_ingrediense)
            {
                if (count(ai.second.begin(), ai.second.end(), ingrediense))
                {
                    maybe = true;
                }
            }

            if (!maybe)
            {
                matches += 1;
            }
        }
    }

    cout << "Day 1: " << matches << '\n';

    vector<pair<string, string>> allergen_ingredient;
    while(allergens_to_ingrediense.size() > 0)
    {
        for(auto ai : allergens_to_ingrediense)
        {
            if(ai.second.size() != 1) continue;

            string ingredient = ai.second.at(0);
            allergen_ingredient.push_back({ai.first, ingredient});
            for(auto ai2 : allergens_to_ingrediense)
            {
                vector<string> se = ai2.second;
                se.erase(remove(se.begin(), se.end(), ingredient), se.end());
                allergens_to_ingrediense[ai2.first] = se;
            }
            allergens_to_ingrediense.erase(allergens_to_ingrediense.find(ai.first));
            break;
        }
    }

    sort(allergen_ingredient.begin(), allergen_ingredient.end(), [](auto x, auto y){return (x.first < y.first);});

    string day2;
    for(auto al : allergen_ingredient)
    {
        day2.append(al.second);
        day2.append(",");
    }

    cout << "Day 2: " << day2.substr(0, day2.size()-1) << '\n';
    return 0;
}