#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
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

int main()
{
    list<string> lines = get_lines();
    int wrong1 = 0, right2 = 0, total = 0;
    for (auto line : lines)
    {
        size_t dash = line.find("-");
        size_t colon = line.find(":");

        int min = stoi(line.substr(0, dash));
        int max = stoi(line.substr(dash + 1, colon - 4));

        char letter = line.substr(colon - 1, 1).c_str()[0];

        string word = line.substr(colon + 2);

        // Part 1
        size_t letter_count = std::count(word.begin(), word.end(), letter);
        if (min > letter_count || letter_count > max)
        {
            wrong1 += 1;
        }

        // Part 2
        if ((word.c_str()[min - 1] == letter) ^ (word.c_str()[max - 1] == letter))
        {
            right2 += 1;
        }

        total += 1;
    }

    cout << "Part 1: " << (total - wrong1) << '\n';
    cout << "Part 2: " << right2 << '\n';

    return 0;
}
