// Copyright 2022 William Edwards
#include<iostream>
using std::iostream;
using std::cout;
using std::endl;
#include<string>
using std::string;
using std::getline;
using std::stoi;
#include<fstream>
using std::ifstream;
#include<map>
using std::map;
#include<set>
using std::set;
#include<utility>
using std::pair;
#include<vector>
using std::vector;
#include<queue>
using std::queue;
#include<sstream>
using std::istringstream;
#include<cmath>
using std::abs;

void MakeGraph(map<vector<int>, vector<vector<int>>> &graph, vector<int> start, vector<int> min, vector<int> max) {
  vector<vector<int>> connect_to;
  if (start[0] - 1 >= min[0]) {
    vector<int> to_add{start[0] - 1, start[1], start[2]};
    connect_to.push_back(to_add);
  }
  if (start[0] + 1 <= max[0]) {
    vector<int> to_add{start[0] + 1, start[1], start[2]};
    connect_to.push_back(to_add);
  }
  if (start[1] - 1 >= min[1]) {
    vector<int> to_add{start[0], start[1] - 1, start[2]};
    connect_to.push_back(to_add);
  }
  if (start[1] + 1 <= max[1]) {
    vector<int> to_add{start[0], start[1] + 1, start[2]};
    connect_to.push_back(to_add);
  }
  if (start[2] - 1 >= min[2]) {
    vector<int> to_add{start[0], start[1], start[2] - 1};
    connect_to.push_back(to_add);
  }
  if (start[2] + 1 <= max[2]) {
    vector<int> to_add{start[0], start[1], start[2] + 1};
    connect_to.push_back(to_add);
  }
  graph.insert(pair<vector<int>, vector<vector<int>>>(start, connect_to));
  for (vector<int> coord : connect_to) {
    if (!graph.count(coord)) {
      MakeGraph(graph, coord, min, max);
    }
  }
}

bool IsTouching(vector<int> rock1, vector<int> rock2) {
  int dist = abs(rock1[0] - rock2[0]) + abs(rock1[1] - rock2[1]) + abs(rock1[2] - rock2[2]);
  return (dist == 1);
}

set<vector<int>> BFS(map<vector<int>, vector<vector<int>>> &graph, vector<int> start) {
  queue<vector<int>> to_analyze;
  set<vector<int>> visited;
  to_analyze.push(start);
  visited.insert(start);
  while (!to_analyze.empty()) {
    vector<int> analyzing = to_analyze.front();
    to_analyze.pop();
    vector<vector<int>> children = graph[analyzing];
    for (auto child : children) {
      if (!visited.count(child) && graph.count(child)) {
        visited.insert(child);
        to_analyze.push(child);
      }
    }
  }
  return visited;
}

int main() {
  ifstream rock_coords("rocks.txt");
  map<vector<int>, int> rock_sides;
  vector<vector<int>> rocks;
  string coords;
  while (getline(rock_coords, coords)) {
    istringstream loc(coords);
    string coord;
    vector<int> rock_loc;
    while (getline(loc, coord, ',')) {
      rock_loc.push_back(stoi(coord));
    }
    rock_sides.insert(pair<vector<int>, int>(rock_loc, 6));
    rocks.push_back(rock_loc);
  }
  for (int i = 0; i < rocks.size() - 1; ++i) {
    if (rock_sides[rocks[i]] > 0) {
      for (int j = i + 1; j < rocks.size(); ++j) {
        if (IsTouching(rocks[i], rocks[j])) {
          rock_sides[rocks[i]] -= 1;
          rock_sides[rocks[i]] -= 1;
        }
      }
    }
  }
  int total_sides = 0;
  for (auto &rock : rock_sides) {
    total_sides += rock.second;
  }
  cout << "Answer to part 1 is: " << total_sides << endl;
  // ------------------------ PART 2 ----------------------------
  vector<int> max_p = {0,0,0};
  vector<int> min_p = {1000, 1000, 1000};
  for (auto rock : rocks) {
    max_p[0] = (rock[0] + 1 > max_p[0]) ? rock[0] + 1 : max_p[0];
    min_p[0] = (rock[0] - 1 < min_p[0]) ? rock[0] - 1: min_p[0];

    max_p[1] = (rock[1] + 1 > max_p[1]) ? rock[1] + 1: max_p[1];
    min_p[1] = (rock[1] - 1 < min_p[1]) ? rock[1] - 1: min_p[1];

    max_p[2] = (rock[2] + 1 > max_p[2]) ? rock[2] + 1: max_p[2];
    min_p[2] = (rock[2] - 1 < min_p[2]) ? rock[2] - 1: min_p[2];
  }
  map<vector<int>, vector<vector<int>>> graph;
  MakeGraph(graph, min_p, min_p, max_p);
  for (auto rock : rocks) {
    graph.erase(rock);
  }
  set<vector<int>> accessible = BFS(graph, min_p);
  for (auto space : accessible) {
    graph.erase(space);
  }
  int inaccessible = 0;
  for (vector<int> rock : rocks) {
    for (auto space : graph) {
      if (IsTouching(rock, space.first)) {
        ++inaccessible;
      }
    }
  }
  cout << "Answer to part 2 is " << total_sides - inaccessible << endl;
  return 0;
}
