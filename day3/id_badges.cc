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

int search_rucksack(string items, char item) {
  for (int i = 0; i < items.length(); ++i) {
    if (items[i] == item)
      return get_priority(item);
  }
  return 0;
}

int main() {
  ifstream rucksacks("rucksack_items.txt");
  int priority_sum = 0;
  string ruck1, ruck2, ruck3;
  while (rucksacks >> ruck1) {
    rucksacks >> ruck2;
    rucksacks >> ruck3;
    // Iterate through every object in first rucksack
    for (int i = 0; i < ruck1.length(); ++i) {
      // If we find this item in both rucksacks, add priority to the priority count
      if (search_rucksack(ruck2, ruck1[i]) && search_rucksack(ruck3, ruck1[i])) {
        priority_sum += get_priority(ruck1[i]);
        break;  // Necessary to break since for some reason an elf can be carrying two IDs
      }
    }
  }
  cout << "Priority score: " << priority_sum << endl;
}
