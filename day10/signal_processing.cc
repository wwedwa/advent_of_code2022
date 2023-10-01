// Copyright 2022 William Edwards
#include<vector>
using std::vector;
#include<iostream>
using std::iostream;
using std::cout;
using std::endl;
#include<string>
using std::string;
#include<fstream>
using std::ifstream;

int main() {
  int cycle = 0;
  int x = 1;
  int strength_sum = 0;
  string line;
  ifstream commands("commands.txt");
  while (commands >> line) {
    ++cycle;
    if (((cycle - 20) % 40) == 0) {
      strength_sum += cycle * x;
    }
    if (line == "addx") {
      ++cycle;
      if (((cycle - 20) % 40) == 0) {
        strength_sum += cycle * x;
      }
      int to_add;
      commands >> to_add;
      x += to_add;
    }
  }
  cout << "Total of strength signals: " << strength_sum << endl;
  return 0;
}