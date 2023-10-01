// Copyright 2022 William Edwards
#include<vector>
using std::vector;
#include<iostream>
using std::iostream;
using std::cout;
using std::endl;
#include<string>
using std::string;
using std::stoi;
#include<fstream>
using std::ifstream;
#include<sstream>
using std::istringstream;
#include<utility>
using std::pair;

void ResizeMap(int x_max, int y_max, vector<vector<char>> &map) {
  while (y_max >= map.size()) {
    map.emplace_back();
  }
  for (auto &v : map) {
    while (x_max >= v.size()) {
      v.push_back('.');
    }
  }
}

void Print(const vector<vector<char>> &map) {
  for (int i = 0; i < map.size(); ++i) {
    for (int j = 478; j < 540; ++j) {
      cout << map[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
  ifstream walls("walls.txt");
  vector<vector<char>> map;
  string line;
  string delim = " -> ";
  int x_max = 0;
  int y_max = 0;
  while (getline(walls, line)) {
    string sequence = line;
    vector<pair<int, int>> pairs;
    while (sequence != "") {
      string coords = sequence.substr(0, sequence.find(delim));
      if (sequence.find(delim) != string::npos) {
        sequence.erase(0, sequence.find(delim) + delim.length());
      } else {
        sequence = "";
      }
      cout << coords << endl;
      int x = stoi(coords.substr(0, coords.find(",")));
      int y = stoi(coords.substr(coords.find(",") + 1));
      pairs.emplace_back(x, y);
    }
    for (int i = 0; i < pairs.size() - 1; ++i) {
      pair<int, int> from = pairs[i];
      pair<int, int> to = pairs[i + 1];
      int local_x_max = (from.first > to.first) ? from.first : to.first;
      x_max = (local_x_max > x_max) ? local_x_max : x_max;
      int local_y_max = (from.second > to.second) ? from.second : to.second;
      y_max = (local_y_max > y_max) ? local_y_max : y_max;
      ResizeMap(x_max, y_max, map);
      if (from.first >= to.first && from.second >= to.second) {
        pair<int, int> temp = to;
        to = from;
        from = temp;
      }
      for (int i = from.first; i <= to.first; ++i) {
        for (int j = from.second; j <= to.second; ++j) {
          map[j][i] = '#';  // Reverse i and j because i is x (which col) and j is y (which row)
        }
      }
    }
  }
  pair<int, int> sand_loc(500, 0);
  bool is_abyss = false;
  int count = 0;
  while (!is_abyss) {
    if (sand_loc.second == (map.size() - 1)) {
      is_abyss = true;
    }
    else if (map[sand_loc.second + 1][sand_loc.first] == '.') {
      ++sand_loc.second;
    } else if (map[sand_loc.second + 1][sand_loc.first - 1] == '.') {
      ++sand_loc.second;
      --sand_loc.first;
    } else if (map[sand_loc.second + 1][sand_loc.first + 1] == '.') {
      ++sand_loc.second;
      ++sand_loc.first;
    } else {
      ++count;
      map[sand_loc.second][sand_loc.first] = 'o';
      sand_loc.first = 500;
      sand_loc.second = 0;
    }
  }
  Print(map);
  cout << "Part one answer is: " << count << endl;

  // PART 2 SOLUTION
  // Add floor
  ResizeMap(1000, 0, map);
  map.emplace_back();
  map.emplace_back();
  for (int i = 0; i < map[0].size(); ++i) {
    map.back().push_back('#');
    map[map.size() - 2].push_back('.');
  }
  sand_loc.first = 500;
  sand_loc.second = 0;
  bool is_full = false;
  while (!is_full) {
    if (map[0][500] == 'o') {
      is_full = true;
    }
    else if (map[sand_loc.second + 1][sand_loc.first] == '.') {
      ++sand_loc.second;
    } else if (map[sand_loc.second + 1][sand_loc.first - 1] == '.') {
      ++sand_loc.second;
      --sand_loc.first;
    } else if (map[sand_loc.second + 1][sand_loc.first + 1] == '.') {
      ++sand_loc.second;
      ++sand_loc.first;
    } else {
      ++count;
      map[sand_loc.second][sand_loc.first] = 'o';
      sand_loc.first = 500;
      sand_loc.second = 0;
    }
  }
  Print(map);
  cout << "Part two answer is: " << count << endl;
}