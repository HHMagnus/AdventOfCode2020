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

int half (string input, int low, int high, char lower, char higher) {
    string::iterator iter = input.begin();
    while(iter != input.end()){
        char x = *iter;
        double h = (high - low)/2.0;
        
        if(x == lower){
            high = high - ceil(h);
        }else if(x == higher){
            low = low + ceil(h);
        }
        iter++;
    }
    return low;
}

int seat_id(string input) {
    int row = half(input.substr(0,7), 0, 127, 'F', 'B');
    int column = half(input.substr(7,3), 0, 7, 'L', 'R');
    return row * 8 + column;
}

int main()
{
    set<int> seats;
    int max = 0;
    for(string input : get_lines()){
        int seat = seat_id(input);
        if(seat > max){
            max = seat;
        }
        seats.insert(seat);
    }
    cout << "Day 1: " << max << '\n'; 

    for(int i = 0; i < max; i++){
        if(seats.find(i-1) != seats.end() &&
            seats.find(i) == seats.end() &&
            seats.find(i+1) != seats.end()){
            cout << "Day 2: " << i << '\n';
            return 0;
        }
    }
    return -1;
}