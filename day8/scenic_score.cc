// Copyright 2022 William Edwards
#include<iostream>
using std::cout;
using std::endl;
#include<vector>
using std::vector;
#include<string>
using std::string;
using std::stoi;
using std::getline;
#include<fstream>
using std::ifstream;

int GetScore(int row, int col, const vector<vector<int>> &trees) {
  int left_view = 0;
  int right_view = 0;
  int up_view = 0;
  int down_view = 0;
  int val = trees[row][col];
  // Score looking up
  for (int i = row - 1; i >= 0; --i) {
    ++up_view;
    if (trees[i][col] >= val) break;
  }
  // Score looking down
  for (int i = row + 1; i < trees.size(); ++i) {
    ++down_view;
    if (trees[i][col] >= val) break;
  }
  // Score looking left
  for (int i = col - 1; i >= 0; --i) {
    ++left_view;
    if (trees[row][i] >= val) break;
  }
  // Score looking right
  for (int i = col + 1; i < trees[row].size(); ++i) {
    ++right_view;
    if (trees[row][i] >= val) break;
  }
  cout << up_view << ", " << down_view << ", " << left_view << ", " << right_view << endl;
  return up_view * down_view * left_view * right_view;
}

int main() {
  ifstream tree_grid("tree_heights.txt");
  string tree_line;
  vector<vector<int>> trees;
  int row = 0;
  while (getline(tree_grid, tree_line)) {
    vector<int> tree_row;
    for (int i = 0; i < tree_line.length(); ++i) {
      tree_row.push_back(tree_line[i] - '0');
    }
    trees.push_back(tree_row);
    ++row;
  }

  int curr_score = 0;
  int max_score = -1;
  for (int i = 0; i < trees.size(); ++i) {
    for (int j = 0; j < trees[i].size(); ++j) {
      curr_score = GetScore(i, j, trees);
      max_score = (curr_score > max_score) ? curr_score : max_score;
    }
  }
  cout << "Max scenic score: " << max_score << endl;
  return 0;
}