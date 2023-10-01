// Copyright 2022 William Edwards
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include<fstream>
using std::ifstream;


int get_priority(char item) {
  if (item >= 97)
    return item - 96;
  else
    return item - 38;
}

int search_rucksack(string items) {
  int len = items.length() / 2;
  for (int i = 0; i < len; ++i) {
    char to_compare = items[i];
    for (int j = len; j < len * 2; ++j) {
      if (to_compare == items[j]) {
        return get_priority(to_compare);
      }
    }
  }
  return -1;
}

int main() {
  ifstream rucksacks("rucksack_items.txt");
  string items;
  int priority_sum = 0;
  while (rucksacks >> items) {
    int priority_val = search_rucksack(items);
    if (priority_val != -1)
      priority_sum += priority_val;
  }
  cout << priority_sum << endl;
}
