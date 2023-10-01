// Copyright 2022 William Edwards
#include<iostream>
using std::cout;
using std::endl;
#include<string>
using std::string;
#include<fstream>
#include<map>
#include<vector>

struct Number {
  long int pos;
  long int data;

  Number(long int p, long int d) {
    pos = p;
    data = d;
  }
};

long int mod(long int a, long int b) {
  return (a % b + b) % b;
}

long int FindZero(std::vector<Number> nums) {
  for (auto& num : nums) {
    if (num.data == 0) {
      return num.pos;
    }
  }
  return -1;
}

void MoveNumber(long int index, std::vector<long int> &indeces, std::vector<Number> &nums) {
  long int size = nums.size();
  long int data = nums[index].data;
  long int to_move = nums[index].data % (size - 1);
  long int old_pos = nums[index].pos;
  long int dir = (to_move > 0) ? 1 : -1;
  long int end = index + to_move;
  for (long int i = index; i != end; i += dir) {
    nums[mod(i, size)] = nums[mod((i + dir), size)];
    indeces[nums[mod(i, size)].pos] = mod((indeces[nums[mod(i, size)].pos] - dir), size);
  }
  nums[mod((to_move + index), size)].data = data;
  nums[mod((to_move + index), size)].pos = old_pos;
  indeces[old_pos] = mod(indeces[old_pos] + to_move, size);
}

int main() {
  std::ifstream data("data.txt");
  long int num;
  long int key = 811589153;
  std::vector<Number> nums;
  std::vector<long int> indeces;
  long int count  = 0;
  while (data >> num) {
    nums.emplace_back(count, num * key);
    indeces.push_back(count);
    ++count;
  }
  for (int i = 0; i < 10; ++i) {
    cout << "Mix: " << i << endl;
    for (long int &index : indeces) {
      MoveNumber(index, indeces, nums);
    }
  }

  long int zero_index = FindZero(nums);
  long int start = indeces[zero_index];
  long int size = nums.size();
  long int x = nums[(start + 1000) % size].data;
  long int y = nums[(start + 2000) % size].data;
  long int z = nums[(start + 3000) % size].data;
  cout << "The answer to part 1 is: " << x << " + " << y << " + " << z << " = " << x+y+z << endl;
  return 0;
}