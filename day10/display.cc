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
#include<utility>
using std::pair;
#include<cmath>
using std::abs;

int DuringCycle(int &cursor, int &sprite, int cycle, int x, char screen[]) {
  sprite = x;
  cout << "Cycle " << cycle << endl;
  cout << "   Cursor Position: " << cursor << endl;
  cout << "   Sprite Position: " << sprite << endl;
  if (abs((cursor % 40) - sprite) <= 1) {
    screen[cursor] = '#';
  } else {
    screen[cursor] = '.';
  }
  ++cursor;
  if (((cycle - 20) % 40) == 0) {
    return cycle * x;
  }
  return 0;
}
int main() {
  int cycle = 0;
  int x = 1;
  int strength_sum = 0;
  int sprite = 0;
  int cursor = 0;
  char screen[240];
  for (int i = 0; i < 240; ++i) {
    screen[i] = '.';
  }
  string line;
  ifstream commands("commands.txt");
  while (commands >> line) {
    ++cycle;
    strength_sum += DuringCycle(cursor, sprite, cycle, x, screen);
    if (line == "addx") {
      ++cycle;
      strength_sum += DuringCycle(cursor, sprite, cycle, x, screen);
      int to_add;
      commands >> to_add;
      x += to_add;
    }
  }
  for (int i = 0; i < 240; ++i) {
    if (i % 40 == 0) {
      cout << endl;
    }
    cout << screen[i];
  }
  cout << endl;
  return 0;
}