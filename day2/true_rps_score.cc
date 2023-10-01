// Copyright 2022 William Edwards
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include<fstream>
using std::ifstream;
/*
A (Rock) = 65     X (Loss) = 88
B (Paper) = 66    Y (Tie) = 89
C (Scissors) = 67  Z (Win) = 90
*/
int main() {
  // Use ASCII values of the chars since the distance between them is predictable
  // This then can be used to decide a win loss or tie
  ifstream games("strat_guide.txt");
  char elf_mv;
  char ending;
  int score = 0;
  int win_return[3] = {2, 3, 1};
  int loss_return[3] = {3, 1, 2};
  while (games >> elf_mv) {
    games >> ending;
    // X = 88 so if we need to lose, score doesn't change,
    // If tie score increases by 3
    // If win score increases by 6
    score += (ending - 88) * 3;
    // If loss, grab score from loss_return array
    if (ending == 'X')
      score += loss_return[elf_mv - 65];
    // If tie, score is the same score as the elf move
    else if (ending == 'Y')
      score += elf_mv - 64;
    // If win, grab score from the win_return array
    else if (ending == 'Z')
      score += win_return[elf_mv - 65];
  }
  cout << score << endl;
  return 0;
}