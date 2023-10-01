// Copyright 2022 William Edwards
#include<iostream>
using std::cout;
using std::endl;
#include<string>
using std::string;
#include<fstream>
#include<unordered_map>
#include<functional>

struct Monkey {
  long int num;
  string name;
  string monkey1;
  string monkey2;
  std::function<long int(long int, long int)> operation;
  char op_symbol;
  std::function<long int(long int, long int)> inv;

  long int GetNum(std::unordered_map<string, Monkey> &graph) {
    if (num == 0)
      num = operation(graph[monkey1].GetNum(graph), graph[monkey2].GetNum(graph));
    return num;
  }
};

void ResetMonkeys(std::unordered_map<string, Monkey> &graph) {
  for (auto& monkey : graph) {
    if (monkey.second.monkey1 != "empty") {
      monkey.second.num = 0;
    }
  }
}

bool ContainsHumn(std::unordered_map<string, Monkey> &graph, Monkey &m) {

  if (m.name == "humn" || m.name == "humn") {
    return true;
  } else {
    if (m.monkey1 != "empty") {
      if (ContainsHumn(graph, graph[m.monkey1])) {
        return true;
      }
    }
    if (m.monkey2 != "empty") {
      if (ContainsHumn(graph, graph[m.monkey2])) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  std::ifstream monkeys("monkeys.txt");
  string line;
  std::unordered_map<string, Monkey> graph;
  while (std::getline(monkeys, line)) {
    string name = line.substr(0, 4);
    Monkey m;
    m.name = name;
    line.erase(0, 6);
    std::function<long int(long int,long int)> op;
    if (line.length() == 11) {
      m.num = 0;
      m.monkey1 = line.substr(0, 4);
      m.monkey2 = line.substr(7, 4);
      m.op_symbol = line[5];
      if (line[5] == '/') {
        m.operation = std::divides<long int>();
        m.inv = std::multiplies<long int>();
      } else if (line[5] == '-') {
        m.operation = std::minus<long int>();
        m.inv = std::plus<long int>();
      } else if (line[5] == '*') {
        m.operation = std::multiplies<long int>();
        m.inv = std::divides<long int>();
      } else if (line[5] == '+') {
        m.operation = std::plus<long int>();
        m.inv = std::minus<long int>();
      }
    } else {
      m.num = std::stoi(line);
      m.monkey1 = "empty";
      m.monkey2 = "empty";
    }
    graph.emplace(name, m);
  }
  // ------------------- PART 1 ---------------------
  Monkey &root = graph["root"];
  cout << "Answer to part 1: " << root.GetNum(graph) << endl;
  ResetMonkeys(graph);
  // ------------------- PART 2 ---------------------
  root.operation = std::equal_to<long int>();
  Monkey curr = root;
  Monkey no_humn;
  Monkey contains_humn;
  long int desired_val;
  while (curr.name != "humn") {
    cout << "Looking at " << curr.name << endl;
    if (ContainsHumn(graph, graph[curr.monkey1])) {
      no_humn = graph[curr.monkey2];
      contains_humn = graph[curr.monkey1];
    } else {
      no_humn = graph[curr.monkey1];
      contains_humn = graph[curr.monkey2];
    }
    if (curr.name == "root") {
      desired_val = no_humn.GetNum(graph);
    }
    // desired_val = contains_humn.monkey1 OPERATOR contains_humn.monkey2
    // IF MONKEY1 CONTAINS HUMN: contains_humn.monkey1 = desired_val INV_OP contains_humn.monkey2
    // IF MONKEY2 CONTAINS HUMN: contains.monkey2 = contains_humn.monkey1 OPERATOR desired_val
    if (contains_humn.name != "humn") {
      if (ContainsHumn(graph, graph[contains_humn.monkey1])) {
        desired_val = contains_humn.inv(desired_val, graph[contains_humn.monkey2].GetNum(graph));
      } else {
        if (contains_humn.op_symbol == '+' || contains_humn.op_symbol == '*') {
          desired_val = contains_humn.inv(desired_val, graph[contains_humn.monkey1].GetNum(graph));
        } else {
          desired_val = contains_humn.operation(graph[contains_humn.monkey1].GetNum(graph), desired_val);
        }
      }
    }
    curr = contains_humn;
  }
  graph["humn"].num = desired_val;
  cout << "Answer to part 2: " << desired_val << endl;
  return 0;
}