#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;

set<int> get_lines()
{
  string line;
  ifstream myfile("input.txt");
  set<int> lines;
  if (myfile.is_open())
  {
    while (getline(myfile, line))
    {
      lines.insert(stoi(line));
    }
    myfile.close();
  }

  else
    cout << "Unable to open file";
  return lines;
}

#define YEAR 2020

int main()
{
  set<int> lines = get_lines();

  // Day 1
  for (int x : lines)
  {
    int rev = YEAR - x;

    if (lines.find(rev) != lines.end())
    {
      cout << rev << ',' << x << '\n';
      break;
    }
  }

  // Day 2
  set<int>::iterator it1;
  set<int>::iterator it2;
  for (it1 = lines.begin(); it1 != lines.end(); ++it1)
  {
    for (it2 = it1; it2 != lines.end(); ++it2)
    {
      int x1 = *it1;
      int x2 = *it2;
      int rev = YEAR - x1 - x2;
      if (lines.find(rev) != lines.end())
      {
        cout << x1 << ',' << x2 << ',' << rev << '\n';
        return 0;
      }
    }
  }
  return 0;
}
