// Copyright 2022 Wiintiam Edwards
#include<deque>
using std::deque;
#include<vector>
using std::vector;
#include<iostream>
using std::iostream;
using std::cout;
using std::endl;
#include<string>
using std::string;
using std::stoi;
using std::stoll;
using std::getline;
#include<fstream>
using std::ifstream;
#include<functional>
using std::function;
using std::plus;
using std::multiplies;
#include<sstream>
using std::istringstream;
#include<cmath>
using std::abs;

using ll = long long;
struct Monkey {
  deque<ll> items;
  function<ll(ll, ll)> worry_op;
  int test_with;
  string increase_by;
  int t_monkey;
  int f_monkey;
  int inspected;

  void IncreaseWorry() {
    if (increase_by == "old") {
      items[0] = worry_op(items.front(), items.front());
    } else {
      items[0] = worry_op(items.front(), stoll(increase_by));
    }
  }

  void DecreaseWorry(ll lcm) {
    items[0] %= lcm;
  }

  ll ThrowTo() {
    if (items.front() % test_with == 0) {
      return t_monkey;
    }
    return f_monkey;
  }

  ll ThrowItem() {
    ll temp = items[0];
    items.pop_front();
    return temp;
  }

  void Print() {
    cout << "Holding " << items.size() << " items: ";
    for (ll item : items) {
      cout << item << ", ";
    }
    cout << "\nMust be divisible by " << test_with << endl;
    cout << "Has inspected " << inspected << " items" << endl;
    cout << "Increase worry by " << increase_by << endl;
    cout << "If true, pass to Monkey " << t_monkey << endl;
    cout << "If false, pass to Monkey " << f_monkey << endl;
  }
};

void TakeTurn(Monkey &monkey, Monkey monkeys[], ll lcm) {
  monkey.inspected += monkey.items.size();
  while (!monkey.items.empty()) {
    monkey.IncreaseWorry();
    monkey.DecreaseWorry(lcm);
    Monkey &throw_to = monkeys[monkey.ThrowTo()];
    throw_to.items.push_back(monkey.ThrowItem());
  }
}

int main() {
  const int MONKEY_NUM = 8;
  ifstream monkey_info("monkey_info.txt");
  Monkey monkeys[MONKEY_NUM];
  for (int i = 0; i < MONKEY_NUM; ++i) {
    monkeys[i] = {};
  }
  string line;
  int curr_monkey = 0;
  while (getline(monkey_info, line, ':')) {
    if (line.find("Monkey ") != string::npos) {
      curr_monkey = line[line.length() - 1] - '0';
    }
    if (line.find("Starting items") != string::npos) {
      getline(monkey_info, line);
      istringstream info(line);
      string item;
      while (info >> item) {
        ll worry_lvl = stoll(item.substr(0, item.find(",")));
        monkeys[curr_monkey].items.push_back(worry_lvl);
      }
    } else if (line.find("Operation") != string::npos) {
      getline(monkey_info, line);
      char op = line[11];
      string right_operand = line.substr(13);
      monkeys[curr_monkey].increase_by = right_operand;
      if (op == '+') {
        monkeys[curr_monkey].worry_op = plus<ll>();
      } else {
        monkeys[curr_monkey].worry_op = multiplies<ll>();
      }
    } else if (line.find("Test") != string::npos) {
      getline(monkey_info, line);
      int divisible_by = stoi(line.substr(14));
      monkeys[curr_monkey].test_with = divisible_by;
      getline(monkey_info, line);
      monkeys[curr_monkey].t_monkey = line[line.length() - 1] - '0';
      getline(monkey_info, line);
      monkeys[curr_monkey].f_monkey = line[line.length() - 1] - '0';
    }
  }

  ll lcm = 1;
  for (int i = 0; i < MONKEY_NUM; ++i) {
    lcm *= monkeys[i].test_with;
  }
  cout << lcm << endl;
  for (int i = 0; i < 10000; ++i) {
    for (int j = 0; j < MONKEY_NUM; ++j) {
      TakeTurn(monkeys[j], monkeys, lcm);
    }
  }
  for (int i = 0; i < MONKEY_NUM; ++i) {
    cout << monkeys[i].inspected << endl;
  }
  return 0;
}
