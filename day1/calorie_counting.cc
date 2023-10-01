// Copyright 2022 William Edwards
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
using std::to_string;
#include<fstream>
using std::ifstream;
using std::getline;
#include <sstream>
using std::istringstream;

int main() {
  // Create ifstream to get lines from the file
  ifstream calories("calorie_counts.txt");
  int max = 0;
  int curr_count = 0;
  string str;
  // As long as we can get lines, iterate through file
  while (getline(calories, str)) {
    // If line is empty, compare current max with prev elf calorie count
    // If prev elf calorie count is greater than max, update max
    if (str.empty()) {
      if (curr_count > max) {
        cout << to_string(curr_count) + " is greater than " + to_string(max) << endl;
        cout << "Setting max to " + to_string(curr_count) << endl << endl;
        max = curr_count;
      }
      curr_count = 0;
    // If line is not empty, keep a running total of the calories for the current elf
    } else {
      istringstream temp(str);
      int num;
      temp >> num;
      curr_count += num;
    }
  }
  cout << "Max calories across all elves is " + to_string(max) << endl;
  return 0;
}
