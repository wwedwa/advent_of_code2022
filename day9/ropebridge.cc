// Copyright 2022 William Edwards
#include<iostream>
using std::cout;
using std::endl;
#include<vector>
using std::vector;
#include<string>
using std::string;
using std::stoi;
#include<fstream>
using std::ifstream;
#include<set>
using std::set;
#include<utility>
using std::pair;
#include<cmath>
using std::abs;

bool IsTouching(pair<int, int> hloc, pair<int, int> tloc) {
  return (abs(hloc.first - tloc.first) <= 1) && (abs(hloc.second - tloc.second) <= 1);
}

void CalculateMove(pair<int, int> hloc, pair<int, int> &tloc) {
  if (!IsTouching(hloc, tloc)) {
    if (hloc.first != tloc.first) {
      int x_diff = hloc.first - tloc.first;
      tloc.first += x_diff / abs(x_diff);
    } if (hloc.second != tloc.second) {
      int y_diff = hloc.second - tloc.second;
      tloc.second += y_diff / abs(y_diff);
    }
  }
}

int main() {
  ifstream moves("movements.txt");
  char dir;
  int steps;
  pair<int, int> knots[10];
  for (int i = 0; i < 10; ++i) {
    knots[i] = pair<int, int>(0, 0);
  }
  set<pair<int, int>> tail_locs;
  while (moves >> dir) {
    string str_steps;
    moves >> str_steps;
    steps = stoi(str_steps);
    for (int i = 0; i < steps; ++i) {
      if (dir == 'U') {
        ++knots[0].second;
      } else if (dir == 'D') {
        --knots[0].second;
      } else if (dir == 'L') {
        ++knots[0].first;
      } else {
        --knots[0].first;
      }
      for (int j = 1; j < 10; ++j) {
        CalculateMove(knots[j - 1], knots[j]);
      }
      tail_locs.insert(knots[9]);
    }
  }

  cout << "Number of unique tail positions: " << tail_locs.size() << endl;
  return 0;
}