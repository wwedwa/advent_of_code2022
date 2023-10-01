// Copyright 2022 William Edwards

#include<string>
using std::string;
using std::stoi;
#include<iostream>
using std::cout;
using std::endl;
#include<fstream>
using std::ifstream;
#include<deque>
using std::deque;

int main() {
  ifstream buffer("buffer.txt");
  char c;
  int count = 0;
  deque<char> last_four;
  bool isMatch = true;
  while (buffer >> c) {
    ++count;
    last_four.push_back(c);
    if (last_four.size() > 14) {
      last_four.pop_front();
      isMatch = false;
      for (int i = 0; i < 13; ++i) {
        for (int j = i; j < 13; ++j) {
          if (last_four[i] == last_four[j + 1]) {
            isMatch = true;
          }
        }
      }
      if (!isMatch) {
        cout << count << endl;
        break;
      }
    }
  }
  return 0;
}