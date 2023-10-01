// Copyright 2022 William Edwards
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <fstream>
#include <deque>
#include <vector>
#include <map>
#include <utility>

bool Propose(std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> &new_locs,
             std::map<std::pair<int, int>, bool> &elf_locs,
             std::deque<char> dirs) {
  int count = 0;
  for (auto &elf : elf_locs) {
    int x = elf.first.first;
    int y = elf.first.second;
    bool move = elf_locs.count({x, y - 1}) || elf_locs.count({x, y + 1}) || elf_locs.count({x - 1, y}) || elf_locs.count({x + 1, y}) ||
                elf_locs.count({x - 1, y - 1}) || elf_locs.count({x - 1, y + 1}) || elf_locs.count({x + 1, y + 1}) || elf_locs.count({x + 1, y - 1});
    count += !move;
    for (char &dir : dirs) {
      if (dir == 'N' && !elf.second && move) {
        bool empty = !elf_locs.count(std::make_pair(x, y - 1)) && !elf_locs.count(std::make_pair(x - 1, y - 1)) && !elf_locs.count(std::make_pair(x + 1, y - 1));
        if (empty) {
          std::pair<int , int> new_loc(x, y - 1);
          elf_locs[elf.first] = 1;
          if (new_locs.count(new_loc)) {
            new_locs[new_loc].push_back(elf.first);
          } else {
            new_locs.emplace(new_loc, std::vector<std::pair<int, int>>{elf.first});
          }
        }
      }
      else if (dir == 'S' && !elf.second && move) {
        bool empty = !elf_locs.count(std::make_pair(x, y + 1)) && !elf_locs.count(std::make_pair(x - 1, y + 1)) && !elf_locs.count(std::make_pair(x + 1, y + 1));
        if (empty) {
          std::pair<int , int> new_loc(x, y + 1);
          elf_locs[elf.first] = 1;
          if (new_locs.count(new_loc)) {
            new_locs[new_loc].push_back(elf.first);
          } else {
            new_locs.emplace(new_loc, std::vector<std::pair<int, int>>{elf.first});
          }
        }
      }
      else if (dir == 'W' && !elf.second && move) {
        bool empty = !elf_locs.count(std::make_pair(x - 1, y)) && !elf_locs.count(std::make_pair(x - 1, y + 1)) && !elf_locs.count(std::make_pair(x - 1, y - 1));
        if (empty) {
          std::pair<int , int> new_loc(x - 1, y);
          elf_locs[elf.first] = 1;
          if (new_locs.count(new_loc)) {
            new_locs[new_loc].push_back(elf.first);
          } else {
            new_locs.emplace(new_loc, std::vector<std::pair<int, int>>{elf.first});
          }
        }
      }
      else if (dir == 'E' && !elf.second && move) {
        bool empty = !elf_locs.count(std::make_pair(x + 1, y)) && !elf_locs.count(std::make_pair(x + 1, y + 1)) && !elf_locs.count(std::make_pair(x + 1, y - 1));
        if (empty) {
          std::pair<int , int> new_loc(x + 1, y);
          elf_locs[elf.first] = 1;
          if (new_locs.count(new_loc)) {
            new_locs[new_loc].push_back(elf.first);
          } else {
            new_locs.emplace(new_loc, std::vector<std::pair<int, int>>{elf.first});
          }
        }
      }
    }
  }
  return count == elf_locs.size();
}

int main() {
  std::ifstream elves("elf_map.txt");
  string line;
  std::map<std::pair<int, int>, bool> elf_locs;
  int j = 0;
  while (elves >> line) {
    for (int i = 0; i < line.length(); ++i) {
      if (line[i] == '#') {
        elf_locs.emplace(std::make_pair(i, j), 0);
      }
    }
    ++j;
  }
  std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> new_locs;
  std::deque<char> dirs = {'N', 'S', 'W', 'E'};
  bool all_done = false;
  int count = 0;
  while (!all_done) {
    ++count;
    all_done = Propose(new_locs, elf_locs, dirs);
    for (auto &loc : new_locs) {
      if (new_locs[loc.first].size() == 1) {
        elf_locs.erase(loc.second.front());
        elf_locs.emplace(loc.first, 0);
      }
    }
    for (auto &elf : elf_locs) {
      elf.second = 0;
    }
    new_locs.clear();
    char temp = dirs.front();
    dirs.pop_front();
    dirs.push_back(temp);
  }
  int min_x, max_x, min_y, max_y;
  bool first = true;
  for (auto &elf : elf_locs) {
    int x = elf.first.first;
    int y = elf.first.second;
    if (first) {
      min_x = max_x = x;
      min_y = max_y = y;
      first = false;
    } else {
      min_x = (x < min_x) ? x : min_x;
      min_y = (y < min_y) ? y : min_y;
      max_x = (x > max_x) ? x : max_x;
      max_y = (y > max_y) ? y : max_y;
    }
  }

  for (int j = min_y; j <= max_y; ++j) {
    for (int i = min_x; i <= max_x; ++i) {
      if (elf_locs.count(std::make_pair(i, j))) {
        cout << '#';
      } else {
        cout << '.';
      }
    }
    cout << endl;
  }
  cout << "x range: " << min_x << " to " << max_x << endl;
  cout << "y range: " << min_y << " to " << max_y << endl;
  int size_of_rect = (max_x - min_x + 1) * (max_y - min_y + 1);
  cout << "Answer to part 2: " << count << endl;
  return 0;
}