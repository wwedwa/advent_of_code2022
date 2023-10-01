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
  int max1, max2, max3 = 0;
  int curr_count = 0;
  string str;
  // As long as we can get lines, iterate through file
  while (getline(calories, str)) {
    // If line is empty, compare current maxes with prev elf calorie count
    // If prev elf calorie count is greater than ones of the maxes, replace
    // that max and shift the rest down
    if (str.empty()) {
      if (curr_count > max1) {
        max3 = max2;
        max2 = max1;
        max1 = curr_count;
      } else if (curr_count > max2) {
        max3 = max2;
        max2 = curr_count;
      } else if (curr_count > max3) {
        max3 = curr_count;
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
  cout << "Top three calorie counts is " + to_string(max1) +
          ", " + to_string(max2) + ", " + to_string(max3)<< endl;
  int total_cals = max1 + max2 + max3;
  cout << "Combined top 3 calorie counts: " + to_string(total_cals) << endl;
  return 0;
}
