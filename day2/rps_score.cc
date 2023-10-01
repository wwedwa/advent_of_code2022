// Copyright 2022 William Edwards
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include<fstream>
using std::ifstream;

int main() {
  // Use ASCII values of the chars since the distance between them is predictable
  // This then can be used to decide a win loss or tie
  ifstream games("strat_guide.txt");
  char elf_mv;
  char player_mv;
  int score = 0;
  while (games >> elf_mv) {
    games >> player_mv;
    // X = 88, Y = 89, Z = 90 so subtracting 87 from them would give the corresponding
    // points for choosing rock, paper, or scissors
    score += player_mv - 87;
    int diff = player_mv - elf_mv;
    // If the chars are different by 23, they are the same object so its a tie
    if (diff == 23) {
      score += 3;
    }
    // Else if the difference is either 24 or 21, this is a win for us
    else if ( diff == 24 || diff == 21) {
      score += 6;
    }
  }
  cout << score << endl;
  return 0;
}