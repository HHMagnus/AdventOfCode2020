#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <deque>
#include <algorithm>
#include <set>
#include <iterator>
#include <map>
#include <regex>
#include <bitset>
using namespace std;

int score(deque<int> winner)
{
    int score = 0;

    int i = winner.size();
    auto iter = winner.begin();
    while (iter != winner.end())
    {
        int x = *iter;
        score += (i * x);
        iter++;
        i--;
    }
    return score;
}

int combat(deque<int> player1, deque<int> player2)
{

    while (player1.size() > 1 && player1.size() < 50)
    {
        int p1 = player1.front();
        player1.pop_front();
        int p2 = player2.front();
        player2.pop_front();

        if (p1 > p2)
        {
            player1.push_back(p1);
            player1.push_back(p2);
        }
        else
        {
            player2.push_back(p2);
            player2.push_back(p1);
        }
    }

    long long day1 = 0;
    if (player1.size() == 50)
    {
        // Player 1 won
        day1 = score(player1);
    }
    else
    {
        // Player 2 won
        day1 = score(player2);
    }

    return day1;
}

int hashPlayers(deque<int> player1, deque<int> player2)
{
    int seed = player1.size() + player2.size();
    for (auto i : player1)
    {
        // borrowed from https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
        // has to be different from the one below to prevent errors
        seed ^= i + 0x9e3761b9 + (seed << 6) + (seed >> 2);
    }

    for (auto i : player2)
    {
        // borrowed from https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
        seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    return seed;
}

pair<bool, deque<int>> recursive_combat(deque<int> player1, deque<int> player2)
{
    set<int> prevs;

    while (player1.size() > 0 && player2.size() > 0)
    {
        int hist = hashPlayers(player1, player2);
        if(prevs.find(hist) != prevs.end())
        {
            return {1, player1};
        }
        prevs.insert(hist);

        int p1 = player1.front();
        player1.pop_front();
        int p2 = player2.front();
        player2.pop_front();

        bool won = p1 > p2;

        if(p1 <= player1.size() && p2 <= player2.size())
        {
            deque<int> player1copy(p1), player2copy(p2);

            copy_n(player1.begin(), p1, player1copy.begin());
            copy_n(player2.begin(), p2, player2copy.begin());

            auto check = recursive_combat(player1copy, player2copy);
            won = check.first;
        }

        if(won)
        {
            player1.push_back(p1);
            player1.push_back(p2);
        }
        else
        {
            player2.push_back(p2);
            player2.push_back(p1);
        }
    }

    if (player1.size() == 0)
    {
        return {0, player2};
    }
    else
    {
        return {1, player1};
    }
}

int main()
{
    // manual input
    deque<int> player1{12, 40, 50, 4, 24, 15, 22, 43, 18, 21, 2, 42, 27, 36, 6, 31, 35, 20, 32, 1, 41, 14, 9, 44, 8};
    deque<int> player2{30, 10, 47, 29, 13, 11, 49, 7, 25, 37, 33, 48, 16, 5, 45, 19, 17, 26, 46, 23, 34, 39, 28, 3, 38};

    cout << "Day 1: " << combat(player1, player2) << '\n';

    auto day2 = recursive_combat(player1, player2);
    cout << "Day 2: " << score(day2.second) << '\n';

    return 0;
}