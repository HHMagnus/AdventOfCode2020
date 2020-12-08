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

class Change
{
public:
    list<string>::iterator iter;
    int line;
    int accumulator;
};

Change do_instruction(string inst, int acc_change, list<string>::iterator iter, int line, int accumulator)
{

    if (inst._Equal("nop"))
    {
        line++;
        ++iter;
    }
    else if (inst._Equal("acc"))
    {
        accumulator += acc_change;
        line++;
        ++iter;
    }
    else if (inst._Equal("jmp"))
    {
        int change = acc_change;
        line += change;
        while (change > 0)
        {
            ++iter;
            change--;
        }
        while (change < 0)
        {
            --iter;
            change++;
        }
    }
    else
    {
        cout << "ERROR" << '\n';
        exit(-1);
    }

    Change change;
    change.accumulator = accumulator;
    change.line = line;
    change.iter = iter;
    return change;
}

pair<int, int> get_lines_accumulator(list<string> &lines, list<string>::iterator iter, int accumulator, set<int> prev, int line, bool changed)
{
    if (prev.find(line) != prev.end() || line == lines.size())
    {
        return {line, accumulator};
    }
    prev.insert(line);
    string inst = *iter;
    string inst1 = inst.substr(0, inst.find(" "));
    int inst2 = stoi(inst.substr(inst.find(" ") + 1));

    if (!changed && (inst1._Equal("jmp") || inst1._Equal("nop")))
    {
        string alt_inst1 = inst1._Equal("jmp") ? "nop" : "jmp";

        auto change = do_instruction(alt_inst1, inst2, iter, line, accumulator);
        auto result = get_lines_accumulator(lines, change.iter, change.accumulator, prev, change.line, true);
        if (result.first == lines.size())
        {
            return result;
        }
        
    }

    auto change = do_instruction(inst1, inst2, iter, line, accumulator);
    return get_lines_accumulator(lines, change.iter, change.accumulator, prev, change.line, changed);
}

int main()
{
    list<string> lines = get_lines();
    set<int> prev;
    cout << "Day 1: " << get_lines_accumulator(lines, lines.begin(), 0, prev, 0, true).second << '\n';
    cout << "Day 2: " << get_lines_accumulator(lines, lines.begin(), 0, prev, 0, false).second << '\n';

    return 0;
}