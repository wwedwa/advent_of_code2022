// Copyright 2022 William Edwards
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <utility>

std::pair<int, int> GetStart(std::vector<string> &graph) {
  string start_line = graph[0];
  for (int i = 0; i < start_line.length(); ++i) {
    if (start_line[i] != ' ') {
      return std::make_pair(0, i);
    }
  }
  return std::make_pair(-1, -1);
}
// 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT
int GetNextDir(int curr_dir, int turn) {
  int next_dir = curr_dir + turn;
  return (next_dir % 4 + 4) % 4;
}

void PrintMap(std::vector<string> &graph, std::pair<int, int> curr_pos) {
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph[i].length(); ++j) {
      if (curr_pos.first == i && curr_pos.second == j) {
        cout << '*';
      } else {
        cout << graph[i][j];
      }
    }
    cout << '\n';
  }
}

std::pair<int, int> GetWrappedCoord(std::pair<int, int> curr_pos, int dir, std::vector<string> &graph) {
  int row = curr_pos.first;
  int col = curr_pos.second;
  if (dir == 0) {
    while (row + 1 < graph.size() && graph[row + 1].length() > col && graph[row + 1][col] != ' ') {
      ++row;
    }
  } else if (dir == 1) {
    while (col - 1 >= 0 && graph[row][col - 1] != ' ') {
      --col;
    }
  } else if (dir == 2) {
    while (row - 1 >= 0 && graph[row - 1].length() > col && graph[row - 1][col] != ' ') {
      --row;
    }
  } else if (dir == 3) {
    while (col + 1 < graph[row].length() && graph[row][col + 1] != ' ') {
      ++col;
    }
  }
  return std::make_pair(row, col);
}

void MakeMove(std::pair<int, int> &curr_pos, std::pair<int, int> move, std::vector<string> &graph) {
  int dir = move.first;
  int length = move.second;
  int &row = curr_pos.first;
  int &col = curr_pos.second;
  if (dir == 0) {
    for (int i = 0; i < length; ++i) {
      if ((row - 1) < 0 || graph[row - 1].length() <= col || graph[row - 1][col] == ' ') {
        std::pair<int, int> wrapped_pos = GetWrappedCoord(curr_pos, dir, graph);
        if (graph[wrapped_pos.first][wrapped_pos.second] == '.') {
          row = wrapped_pos.first;
          col = wrapped_pos.second;
        } else {
          return;
        }
      } else if (graph[row - 1][col] == '.') {
        --row;
      } else if (graph[row - 1][col] == '#') {
        return;
      }
    }
  } else if (dir == 1) {
    for (int i = 0; i < length; ++i) {
      if ((col + 1) >= graph[row].length() || graph[row][col + 1] == ' ') {
        std::pair<int, int> wrapped_pos = GetWrappedCoord(curr_pos, dir, graph);
        if (graph[wrapped_pos.first][wrapped_pos.second] == '.') {
          row = wrapped_pos.first;
          col = wrapped_pos.second;
        } else {
          return;
        }
      } else if (graph[row][col + 1] == '.') {
        ++col;
      } else if (graph[row][col + 1] == '#') {
        return;
      }
    }
  } else if (dir == 2) {
    for (int i = 0; i < length; ++i) {
      if ((row + 1) >= graph.size() || graph[row + 1].length() <= col || graph[row + 1][col] == ' ') {
        std::pair<int, int> wrapped_pos = GetWrappedCoord(curr_pos, dir, graph);
        if (graph[wrapped_pos.first][wrapped_pos.second] == '.') {
          row = wrapped_pos.first;
          col = wrapped_pos.second;
        } else {
          return;
        }
      } else if (graph[row + 1][col] == '.') {
        ++row;
      } else if (graph[row + 1][col] == '#') {
        return;
      }
    }
  } else if (dir == 3) {
    for (int i = 0; i < length; ++i) {
      if ((col - 1) < 0 || graph[row][col - 1] == ' ') {
        std::pair<int, int> wrapped_pos = GetWrappedCoord(curr_pos, dir, graph);
        if (graph[wrapped_pos.first][wrapped_pos.second] == '.') {
          row = wrapped_pos.first;
          col = wrapped_pos.second;
        } else {
          return;
        }
      } else if (graph[row][col - 1] == '.') {
        --col;
      } else if (graph[row][col - 1] == '#') {
        return;
      }
    }
  }
}

int main() {
  std::ifstream input("map.txt");
  string line;
  std::vector<string> graph;
  while (std::getline(input, line)) {
    if (line != "") {
      graph.push_back(line);
    } else {
      input >> line;
      break;
    }
  }
  std::vector<int> dirs;
  std::vector<int> lengths;
  for (int i = 0; i < line.length(); ++i) {
    if (line[i] == 'R' || line[i] == 'L') {
      int move = (line[i] == 'R') ? 1 : -1;
      dirs.push_back(move);
      line[i] = ' ';
    }
  }
  std::istringstream nums(line);
  int length;
  while (nums >> length) {
    lengths.push_back(length);
  }
  std::vector<std::pair<int, int>> steps;
  int curr_dir = 1;
  steps.emplace_back(1, lengths[0]);
  for (int i = 0; i < dirs.size(); ++i) {
    curr_dir = GetNextDir(curr_dir, dirs[i]);
    steps.emplace_back(curr_dir, lengths[i + 1]);
  }
  std::pair<int, int> curr_pos = GetStart(graph);
  int count = 0;
  for (auto &move : steps) {
    if (count < 10) {
      PrintMap(graph, curr_pos);
      cout << "Moving " << move.second << " in direction " << move.first << "\n";
    }
    ++count;
    MakeMove(curr_pos, move, graph);
  }
  PrintMap(graph, curr_pos);
  int last_dir = 0;
  for (int dir : dirs) {
    last_dir += dir;
  }
  last_dir = (last_dir % 4 + 4) % 4;
  int password = 1000 * (curr_pos.first + 1) + 4 * (curr_pos.second + 1) + last_dir;
  cout << "Answer for part 1: " << password << endl;
  return 0;
}