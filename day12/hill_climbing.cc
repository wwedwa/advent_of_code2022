// Copyright 2022 William Edwards
#include<queue>
using std::queue;
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
#include<unordered_map>
using std::unordered_map;
#include<utility>
using std::pair;
#include<set>
using std::set;

void MakeGraph(const vector<vector<char>> &hill_map, unordered_map<int, vector<int>> &graph, pair<int, int> loc) {
  int row = loc.first;
  int col = loc.second;
  int key = row * hill_map[0].size() + col;
  int elev = hill_map[row][col];
  vector<int> can_go;
  if (col - 1 >= 0 && col - 1 < hill_map[0].size() && (hill_map[row][col - 1] - elev) <= 1) {
    can_go.push_back(row * hill_map[0].size() + (col - 1));
  }
  if (col + 1 >= 0 && col + 1 < hill_map[0].size() && (hill_map[row][col + 1] - elev) <= 1) {
    can_go.push_back(row * hill_map[0].size() + (col + 1));
  }
  if (row - 1 >= 0 && row - 1 < hill_map.size() && (hill_map[row - 1][col] - elev) <= 1) {
    can_go.push_back((row - 1) * hill_map[0].size() + col);
  }
  if (row + 1 >= 0 && row + 1 < hill_map.size() && (hill_map[row + 1][col] - elev) <= 1) {
    can_go.push_back((row + 1) * hill_map[0].size() + col);
  }
  pair <int, vector<int>> to_add(key, can_go);
  graph.insert(to_add);
  for (int i = 0; i < can_go.size(); ++i) {
    pair<int, int> new_loc(can_go[i] / hill_map[0].size(), can_go[i] % hill_map[0].size());
    if (!graph.count(can_go[i])) {
      MakeGraph(hill_map, graph, new_loc);
    }
  }
  return;
}

pair<int, int> FindStart(const vector<vector<char>> &hill_map) {
  for (int i = 0; i < hill_map.size(); ++i) {
    for (int j = 0; j < hill_map[i].size(); ++j) {
      if (hill_map[i][j] == 'S') {
        return pair<int, int>(i , j);
      }
    }
  }
  return pair<int, int>(-1, -1);
}

pair<int, int> FindEnd(const vector<vector<char>> &hill_map) {
  for (int i = 0; i < hill_map.size(); ++i) {
    for (int j = 0; j < hill_map[i].size(); ++j) {
      if (hill_map[i][j] == 'E') {
        return pair<int, int>(i , j);
      }
    }
  }
  return pair<int, int>(-1, -1);
}

// NOTE: If we wanted to return number of steps when we immediately reach the end instead of 
// finishing analyzing the map and then compute steps, we can. We simply need to make to_analyze
// a queue which stores the node AND the layer it is in (starting at 0 with s_key). Then, when we add
// a child to to_analyze, we set its layer to one more than the current node being analyzed.
// Once a child equals e_key, we just return the layer that the node being analyzed is in, + 1
int BFS(unordered_map<int, vector<int>> &graph, int s_key, int e_key) {
  queue<int> to_analyze;
  unordered_map<int, int> visited;
  to_analyze.push(s_key);
  visited.emplace(s_key, s_key);
  while (!to_analyze.empty()) {
    int analyzing = to_analyze.front();
    to_analyze.pop();
    vector<int> children = graph[analyzing];
    for (int child : children) {
      if (!visited.count(child)) {
        visited.emplace(child, analyzing);
        to_analyze.push(child);
      }
    }
  }
  int steps = 0;
  if (visited.count(e_key)) {
    int curr_node = e_key;
    while (curr_node != s_key) {
      ++steps;
      curr_node = visited[curr_node];
    }
  }
  return steps;
}

int main() {
  ifstream hill("hill.txt");
  string elevations;
  vector<vector<char>> hill_map;

  while (hill >> elevations) {
    vector<char> line;
    for (char c : elevations) {
      line.push_back(c);
    }
    hill_map.push_back(line);
  }
  unordered_map<int, vector<int>> graph;
  int start_x;
  int start_y;
  pair<int, int> s_loc = FindStart(hill_map);
  hill_map[s_loc.first][s_loc.second] = 'a';
  int start_key = s_loc.first * hill_map[0].size() + s_loc.second;
  pair<int, int> e_loc = FindEnd(hill_map);
  hill_map[e_loc.first][e_loc.second] = 'z';
  int end_key = e_loc.first * hill_map[0].size() + e_loc.second;
  // First Part:
  MakeGraph(hill_map, graph, s_loc);
  cout << "It took " << BFS(graph, start_key, end_key) << " steps from the start to reach the end." << endl;
  // Second Part:
  unsigned int min_len = -1;
  for (int i = 0; i < hill_map.size(); ++i) {
    for (int j = 0; j < hill_map[i].size(); ++j) {
      if (hill_map[i][j] == 'a') {
        int key = i * hill_map[i].size() + j;
        int path_to_a = BFS(graph, key, end_key);
        if (path_to_a) {
          min_len = (min_len > path_to_a) ? path_to_a : min_len;
        }
      }
    }
  }
  cout << "Length of minimum path from end to lowest point is " << min_len << " steps." << endl;
  return 0;
}