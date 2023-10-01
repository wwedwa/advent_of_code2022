// Copyright 2022 William Edwards

#include<string>
using std::string;
using std::stoi;
#include<iostream>
using std::cout;
using std::endl;
#include<fstream>
using std::ifstream;
#include<vector>
using std::vector;

int main() {
  ifstream crate_mov("crate_movement.txt");
  vector<char> stack1{'N', 'D', 'M', 'Q', 'B', 'P', 'Z'};
  vector<char> stack2{'C', 'L', 'Z', 'Q', 'M', 'D', 'H', 'V'};
  vector<char> stack3{'Q', 'H', 'R', 'D', 'V', 'F', 'Z', 'G'};
  vector<char> stack4{'H', 'G', 'D', 'F', 'N'};
  vector<char> stack5{'N', 'F', 'Q'};
  vector<char> stack6{'D', 'Q', 'V', 'Z', 'F', 'B', 'T'};
  vector<char> stack7{'Q', 'M', 'T', 'Z', 'D', 'V', 'S', 'H'};
  vector<char> stack8{'M', 'G', 'F', 'P', 'N', 'Q'};
  vector<char> stack9{'B', 'W', 'R', 'M'};
  vector<char> stacks[] = {stack1, stack2, stack3, stack4, stack5, stack6, stack7, stack8, stack9};
  string pattern;
  while (getline(crate_mov, pattern)) {
    int move_index = pattern.find("move");
    int from_index = pattern.find("from");
    int to_index = pattern.find("to");
    int num = stoi(pattern.substr(move_index + 5, from_index - move_index - 6));
    int from = stoi(pattern.substr(from_index + 5, 1));
    int to = stoi(pattern.substr(to_index + 3, 1));
    vector<char> temp;
    for (int i = 0; i < num; ++i) {
      temp.push_back(stacks[from - 1].back());
      stacks[from - 1].pop_back();
    }
    for (int i = 0; i < num; ++i) {
      stacks[to - 1].push_back(temp.back());
      temp.pop_back();
    }

  }
  for (int i = 0; i < 9; ++i) {
    cout << stacks[i].back();
  }
  cout << endl;
}