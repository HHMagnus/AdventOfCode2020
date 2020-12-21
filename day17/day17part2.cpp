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

set<tuple<int, int, int, int>> start_cubes(vector<string> lines)
{
    set<tuple<int, int, int, int>> cubes;

    for (int i = 0; i < lines.size(); i++)
    {
        string line = lines.at(i);
        for (int j = 0; j < line.size(); j++)
        {
            if (line.at(j) == '#')
            {
                cubes.insert({i, j, 0, 0});
            }
        }
    }
    return cubes;
}

vector<tuple<int, int, int>> get_neighbours3d(tuple<int, int, int> cube)
{
    vector<tuple<int, int, int>> neighbours;
    // X +1
    neighbours.push_back({get<0>(cube) + 1, get<1>(cube), get<2>(cube)});
    neighbours.push_back({get<0>(cube) + 1, get<1>(cube) + 1, get<2>(cube)});
    neighbours.push_back({get<0>(cube) + 1, get<1>(cube) + 1, get<2>(cube) + 1});
    neighbours.push_back({get<0>(cube) + 1, get<1>(cube) - 1, get<2>(cube)});
    neighbours.push_back({get<0>(cube) + 1, get<1>(cube) - 1, get<2>(cube) - 1});
    neighbours.push_back({get<0>(cube) + 1, get<1>(cube), get<2>(cube) - 1});
    neighbours.push_back({get<0>(cube) + 1, get<1>(cube), get<2>(cube) + 1});
    neighbours.push_back({get<0>(cube) + 1, get<1>(cube) + 1, get<2>(cube) - 1});
    neighbours.push_back({get<0>(cube) + 1, get<1>(cube) - 1, get<2>(cube) + 1});

    // X -1
    neighbours.push_back({get<0>(cube) - 1, get<1>(cube), get<2>(cube)});
    neighbours.push_back({get<0>(cube) - 1, get<1>(cube) + 1, get<2>(cube)});
    neighbours.push_back({get<0>(cube) - 1, get<1>(cube) + 1, get<2>(cube) + 1});
    neighbours.push_back({get<0>(cube) - 1, get<1>(cube) - 1, get<2>(cube)});
    neighbours.push_back({get<0>(cube) - 1, get<1>(cube) - 1, get<2>(cube) - 1});
    neighbours.push_back({get<0>(cube) - 1, get<1>(cube), get<2>(cube) - 1});
    neighbours.push_back({get<0>(cube) - 1, get<1>(cube), get<2>(cube) + 1});
    neighbours.push_back({get<0>(cube) - 1, get<1>(cube) + 1, get<2>(cube) - 1});
    neighbours.push_back({get<0>(cube) - 1, get<1>(cube) - 1, get<2>(cube) + 1});

    // X Same
    neighbours.push_back({get<0>(cube), get<1>(cube) + 1, get<2>(cube)});
    neighbours.push_back({get<0>(cube), get<1>(cube) + 1, get<2>(cube) + 1});
    neighbours.push_back({get<0>(cube), get<1>(cube) - 1, get<2>(cube)});
    neighbours.push_back({get<0>(cube), get<1>(cube) - 1, get<2>(cube) - 1});
    neighbours.push_back({get<0>(cube), get<1>(cube), get<2>(cube) - 1});
    neighbours.push_back({get<0>(cube), get<1>(cube), get<2>(cube) + 1});
    neighbours.push_back({get<0>(cube), get<1>(cube) + 1, get<2>(cube) - 1});
    neighbours.push_back({get<0>(cube), get<1>(cube) - 1, get<2>(cube) + 1});

    return neighbours;
}

vector<tuple<int, int, int, int>> get_neighbours(tuple<int, int, int, int> cube)
{
    vector<tuple<int, int, int, int>> neighbours;

    vector<tuple<int, int, int>> neighbours3d = get_neighbours3d({get<0>(cube), get<1>(cube), get<2>(cube)});

    for_each(neighbours3d.begin(), neighbours3d.end(), [&neighbours, &cube](auto neighbour3d) {
        neighbours.push_back({get<0>(neighbour3d), get<1>(neighbour3d), get<2>(neighbour3d), get<3>(cube)});
    });

    for_each(neighbours3d.begin(), neighbours3d.end(), [&neighbours, &cube](auto neighbour3d) {
        neighbours.push_back({get<0>(neighbour3d), get<1>(neighbour3d), get<2>(neighbour3d), get<3>(cube) + 1});
    });

    for_each(neighbours3d.begin(), neighbours3d.end(), [&neighbours, &cube](auto neighbour3d) {
        neighbours.push_back({get<0>(neighbour3d), get<1>(neighbour3d), get<2>(neighbour3d), get<3>(cube) - 1});
    });

    neighbours.push_back({get<0>(cube), get<1>(cube), get<2>(cube), get<3>(cube) + 1});
    neighbours.push_back({get<0>(cube), get<1>(cube), get<2>(cube), get<3>(cube) - 1});

    return neighbours;
}

bool check_neighbour(tuple<int, int, int, int> neighbour, set<tuple<int, int, int, int>> &active_cubes, map<tuple<int, int, int, int>, int> &candidates)
{
    if (active_cubes.find(neighbour) != active_cubes.end())
    {
        return true;
    }

    int candidate = 0;
    if (candidates.find(neighbour) != candidates.end())
    {
        candidate = (*candidates.find(neighbour)).second;
    }

    candidates[neighbour] = candidate + 1;
    return false;
}

void simulate(set<tuple<int, int, int, int>> &active_cubes)
{
    map<tuple<int, int, int, int>, int> candidates;
    set<tuple<int, int, int, int>> deactivated;

    for (auto cube : active_cubes)
    {
        auto neighbours = get_neighbours(cube);
        int active_neighbours = 0;
        for (auto neighbour : neighbours)
        {
            if (check_neighbour(neighbour, active_cubes, candidates))
            {
                active_neighbours += 1;
            }
        }

        if (active_neighbours != 2 && active_neighbours != 3)
        {
            deactivated.insert(cube);
        }
    }

    for (auto candidate : candidates)
    {
        if (candidate.second == 3)
        {
            active_cubes.insert(candidate.first);
        }
    }

    for (auto deactivate : deactivated)
    {
        active_cubes.erase(active_cubes.find(deactivate));
    }
}

void simulate(set<tuple<int, int, int, int>> &active_cubes, int turns)
{
    for (int i = 0; i < turns; i++)
    {
        simulate(active_cubes);
    }
}

int main()
{
    set<tuple<int, int, int, int>> active_cubes = start_cubes(get_lines());

    simulate(active_cubes, 6);

    cout << "Day 2: " << active_cubes.size() << '\n';

    return 0;
}