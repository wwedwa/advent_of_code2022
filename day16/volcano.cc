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
#include<deque>
using std::deque;
#include<queue>
using std::queue;
#include<utility>
using std::pair;
using std::make_pair;
#include<set>
using std::set;
#include<climits>

struct Valve {
  int name;
  int pressure;

  bool operator<(const Valve &v) const {
    return (name < v.name);
  }
};

void DFS (int time_to, map<string, map<string, int>> &graph, int time, string v, set<deque<string>> &paths, deque<string> &path, map<string, bool> is_on) {
  if (time >= time_to) {
    paths.insert(path);
    return;
  }
  bool all_on = true;
  for (auto &valve : graph) {
    if (!is_on[valve.first] && valve.first != v) {
      all_on = false;
      break;
    }
  }
  int min_dist = 1000;
  for (auto child : graph[v]) {
    if (!is_on[child.first]) {
      min_dist = (min_dist < child.second) ? min_dist : child.second;
    }
  }
  if (!is_on[v] || (v == "AA" && time == 0)) {
    for (auto &child : graph[v]) {
      int curr_length = path.size();
      if (v != "AA" || time > 0) {
        ++time;
      }
      if (time >= time_to) {
        return;
      }
      path.push_back(v);
      if (all_on || (time + min_dist) >= time_to) {
        paths.insert(path);
        return;
      }
      is_on[v] = true;
      DFS(time_to, graph, time + child.second, child.first, paths, path, is_on);
      is_on[v] = false;
      if (v != "AA" || time > 0) {
        --time;
      }
      while (path.size() != curr_length) {
        path.pop_back();
      }
    }
  }
}

int CalculatePressure(map<string, map<string, int>> &graph, deque<string> &path, map<string, int> pressures, int time) {
  int sum = 0;
  string past_step = "START";
  for (string step : path) {
    if (past_step != "START") {
      time -= graph[past_step][step] + 1;
      if (time > 0) {
        sum += time * pressures[step];
      } else {
        return sum;
      }
    }
    past_step = step;
  }
  return sum;
}

void FWA(map<string, map<string, int>> &graph, set<string> &all_valves) {
  for (auto &valve : graph) {
    for (string name : all_valves) {
      if (!valve.second.count(name)) {
        valve.second.insert(pair<string, int>(name, 1000));
      }
    }
  }
  for (string name : all_valves) {
    graph[name][name] = 0;
  }
  for (string k : all_valves) {
    for (string i : all_valves) {
      for (string j : all_valves) {
        if (graph[i][j] > (graph[i][k] + graph[k][j])) {
          graph[i][j] = graph[i][k] + graph[k][j];
        }
      }
    }
  }
  for (auto &valve : graph) {
    valve.second.erase(valve.first);
  }
}

void TurnOnValves(map<string, bool> &is_on, deque<string> &path) {
  for (string step : path) {
    if (step != "AA") {
      is_on[step] = true;
    }
  }
}

void TurnOffValves(map<string, bool> &is_on, deque<string> &path) {
  for (string step : path) {
    if (step != "AA") {
      is_on[step] = false;
    }
  }
}

bool ContainsSameValves(deque<string> &path1, deque<string> &path2) {
  for (string step1 : path1) {
    for (string step2 : path2) {
      if (step1 == step2 && (step1 != "AA")) {
        return true;
      }
    }
  }
  return false;
}
int main() {
  cout << "starting" << endl;
  ifstream valves("valves.txt");
  string line;
  map<string, map<string, int>> graph;
  map<string, int> pressures;
  set<string> all_valves;
  map<string, bool> is_on;
  while (getline(valves, line)) {
    string name = line.substr(6, 2);
    all_valves.insert(name);
    line = line.substr(line.find("=") + 1);
    int pressure = stoi(line.substr(0, line.find(";")));
    bool on = (pressure > 0) ? false : true;
    is_on.insert(pair<string, int>(name, on));
    line = line.substr(line.find("valve") + 6);
    if (line[0] == ' ') {
      line = line.substr(1);
    }
    pressures.insert(pair<string, int>(name, pressure));
    map<string, int> connected_to;
    while (line != "") {
      string valve_to = line.substr(0, 2);
      connected_to.insert(pair<string, int>(valve_to, 1));
      if (line.find(",") != string::npos) {
        line.erase(0, line.find(",") + 2);
      } else {
        line = "";
      }
    }
    graph.insert(pair<string, map<string, int>>(name, connected_to));
  }
  cout << "Done Reading" << endl;
  FWA(graph, all_valves);
  for (string name : all_valves) {
    if (name != "AA" && pressures[name] == 0) {
      for (auto &v : graph) {
        if (v.second.count(name)) {
          v.second.erase(name);
        }
      }
      graph.erase(name);
    }
  }
  set<deque<string>> paths;
  deque<string> path;
  // Make all paths that start after "AA"
  DFS(30, graph, 0, "AA", paths, path, is_on);
  int max = 0;
  for (auto p : paths) {
    int temp = CalculatePressure(graph, p, pressures, 30);
    if (temp > max) {
      max = temp;
    }
  }
  cout << "Number of unique paths: " << paths.size() << endl;
  cout << "Answer to part 1: " << max << endl;
  // ----------------- PART 2 ------------------
  set<deque<string>> paths2s;
  deque<string> path2;
  deque<string> path2_max;
  deque<string> path2e_max;
  DFS(26, graph, 0, "AA", paths2s, path2, is_on);
  std::vector<deque<string>> paths2(paths2s.begin(), paths2s.end());
  int max2 = 0;
  int count = 0;
  int size = paths2.size();
  for (int i = 0; i < paths2.size() - 1; ++i) {
    if (count % 100 == 0)
      cout << "Looking at path " << count << " / " << size << endl;
    ++count;
    int h_pressure = CalculatePressure(graph, paths2[i], pressures, 26);
    for (int j = i + 1; j < paths2.size() - 1; ++j) {
      if (!ContainsSameValves(paths2[i], paths2[j]) && h_pressure > (max / 2)) {
        int temp = h_pressure + CalculatePressure(graph, paths2[j], pressures, 26);
        if (temp > max2) {
          max2 = temp;
          path2_max = paths2[i];
          path2e_max = paths2[j];
        }
      }
    }
  }
  cout << "Human path: ";
  for (string step : path2_max) {
    cout << step;
  }
  cout << endl;
  cout << "Elephant path: ";
  for (string step : path2e_max) {
    cout << step;
  }
  cout << endl;
  cout << "Answer to part 2: " << max2 << endl;
  return 0;
}
