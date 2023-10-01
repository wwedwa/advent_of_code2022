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

bool FromTop(int row, int col, const vector<vector<int>> &trees) {
  int val = trees[row][col];
  for (int i = 0; i < row; ++i) {
    if (trees[i][col] >= val) {
      return false;
    }
  }
  return true;
}

bool FromBottom(int row, int col, const vector<vector<int>> &trees) {
  int val = trees[row][col];
  for (int i = trees.size() - 1; i > row; --i) {
    if (trees[i][col] >= val) {
      return false;
    }
  }
  return true;
}

bool FromLeft(int row, int col, const vector<vector<int>> &trees) {
  int val = trees[row][col];
  for (int i = 0; i < col; ++i) {
    if (trees[row][i] >= val) {
      return false;
    }
  }
  return true;
}

bool FromRight(int row, int col, const vector<vector<int>> &trees) {
  int val = trees[row][col];
  for (int i = trees[row].size() - 1; i > col; --i) {
    if (trees[row][i] >= val) {
      return false;
    }
  }
  return true;
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

  int count = 0;
  for (int i = 0; i < trees.size(); ++i) {
    for (int j = 0; j < trees[i].size(); ++j) {
      if (FromTop(i, j, trees)) {
        ++count;
      } else if (FromBottom(i, j, trees)) {
        ++count;
      } else if (FromLeft(i, j, trees)) {
        ++count;
      } else if (FromRight(i, j, trees)) {
        ++count;
      }
    }
  }
  cout << "Total number of trees: " << (trees.size() * trees[0].size()) << endl;
  cout << "Number of visible trees from outside the grove: " << count << endl;
  return 0;
}