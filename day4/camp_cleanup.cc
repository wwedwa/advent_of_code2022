// Copyright 2022 William Edwards
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include<fstream>
using std::ifstream;
#include<sstream>
using std::istringstream;

void ExtractNums(string pair, int to_change[]) {
    int len = pair.length();
    int dash_loc = pair.find("-");
    string first_num = pair.substr(0, dash_loc);
    string second_num = pair.substr(dash_loc + 1, len - first_num.length());
    to_change[0] = std::stoi(first_num);
    to_change[1] = std::stoi(second_num);
}

int main() {
  ifstream pairs("section_pairs.txt");
  string sect_pairs;
  int count;
  while (pairs >> sect_pairs) {
    int len = sect_pairs.length();
    int comma_loc = sect_pairs.find(",");
    string first_pair = sect_pairs.substr(0, comma_loc);
    string second_pair = sect_pairs.substr(comma_loc + 1, len - first_pair.length());
    int f_pair[2];
    ExtractNums(first_pair, f_pair);
    int s_pair[2];
    ExtractNums(second_pair, s_pair);
    if (f_pair[0] <= s_pair[0] && f_pair[1] >= s_pair[0])
      ++count;
    else if(s_pair[0] <= f_pair[0] && s_pair[1] >= f_pair[0]) {
      ++count;
    }
  }
  cout << "Total overlapping assignments: " << count << endl;
}