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
#include <cmath>
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

long long crack_loop_size(long long public_key, long long subject_number, long long magic) {
    int i = 0;
    long long value = 1;
    while(value != public_key) {
        value *= subject_number;
        value %= magic;
        i++;
    }
    return i;
}

long long crack_encryption(long long public_key, long long loop_size, long long magic) {
    long long value = 1;
    for (int i = 0; i < loop_size; i++) {
        value *= public_key;
        value %= magic;
    }
    return value;
}

int main() {
    vector <string> input = get_lines();

    long long card = stoll(input[0]);
    long long door = stoll(input[1]);
    long long magic = 20201227;

    long long subject_number = 7;

    long long card_loop_size = crack_loop_size(card, subject_number, magic);
    long long door_loop_size = crack_loop_size(door, subject_number, magic);

    long long card_encryption = crack_encryption(door, card_loop_size, magic);
    long long door_encryption = crack_encryption(card, door_loop_size, magic);

    cout << "Day 25 part 1: " << card_encryption << " = " << door_encryption << "\n";

    return 0;
}