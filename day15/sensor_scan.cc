// Copyright 2022 William Edwards
#include<set>
using std::set;
#include<vector>
using std::vector;
#include<iostream>
using std::iostream;
using std::cout;
using std::endl;
#include<string>
using std::string;
using std::stoi;
#include<fstream>
using std::ifstream;
#include<utility>
using std::pair;
using std::make_pair;
#include<cmath>
using std::abs;
#include<climits>

const int ROW = 2000000;
const int MAX = 4000000;

struct Sensor {
  pair<int, int> loc;
  pair<int, int> beacon;
  Sensor (int s_x, int s_y, int b_x, int b_y) {
    loc.first = s_x;
    loc.second = s_y;
    beacon.first = b_x;
    beacon.second = b_y;
  }
  bool operator <(const Sensor &s) const {
    return (loc < s.loc);
  }

  bool operator <(const pair<int, int> &p) const {
    return (loc < p);
  }

  void Print() const {
    cout << "Sensor at x=" << loc.first << ", y=" << loc.second;
    cout << ": closest beacon is at x=" << beacon.first << ", y=" << beacon.second << endl;
  }
};

bool IsIn(vector<Sensor> &v, pair<int, int> &p) {
  for (Sensor s : v) {
    if (s.loc == p) {
      return true;
    }
  }
  for (Sensor s : v) {
    if (s.beacon == p) {
      return true;
    }
  }
  return false;
}

int NumOfTools(vector<Sensor> &sensors, int row) {
  set<pair<int, int>> beacons;
  int count = 0;
  for (Sensor s : sensors) {
    beacons.insert(s.beacon);
    if (s.loc.second == row) {
      ++count;
    }
  }
  for (pair<int, int> b : beacons) {
    if (b.second == row) {
      ++count;
    }
  }
  return count;
}

pair<int, int> FindRangeInRow(Sensor &s, int row, int x_min = INT_MIN, int x_max = INT_MAX) {
  int r = abs(s.loc.first - s.beacon.first) + abs(s.loc.second - s.beacon.second);
  int max_range = s.loc.second + r;
  int min_range = s.loc.second - r;
  if (max_range < row || min_range > row) {
    return pair<int, int>(0, 0);
  }
  int dist = row - s.loc.second;  // Distance in y dir of sensor from 20,000
  int range = abs(dist);
  int start = s.loc.first - r + range;
  int end = s.loc.first + r - range + 1;
  start = (start < x_min) ? x_min : start;
  end = (end > x_max) ? x_max : end;
  return pair<int, int>(start, end);
}

int main() {
  ifstream data("sensors.txt");
  vector<Sensor> sensors;
  string line;
  string delim = ": ";
  while (getline(data, line)) {
    string s_coords = line.substr(10, line.find(delim) - 10);
    int s_x = stoi(s_coords.substr(2, s_coords.find(',') - 2));
    int s_y = stoi(s_coords.substr(s_coords.find(',') + 4));
    string b_coords = line.substr(line.find("is") + 6);
    int b_x = stoi(b_coords.substr(2, b_coords.find(',') - 2));
    int b_y = stoi(b_coords.substr(b_coords.find(',') + 4));
    sensors.emplace_back(s_x, s_y, b_x, b_y);
  }
  set<int> points;
  for (Sensor s : sensors) {
    pair<int, int> range(FindRangeInRow(s, ROW));
    for (int i = range.first; i < range.second; ++i) {
      points.insert(i);
    }
  }
  cout << "Answer to part 1 is: " << points.size() - NumOfTools(sensors, ROW) << endl;

  for (int i = 0; i <= MAX; ++i) {
    vector<pair<int, int>> row;
    int total_range = 0;
    for (Sensor s : sensors) {
      pair<int, int> range(FindRangeInRow(s, i, 0, MAX));
      for (pair<int, int> &p : row) {
        if (range.first >= p.first && range.first < p.second && range.second > p.second) {
          range.first = p.second;
        } else if (range.first < p.first && range.second > p.first && range.second <= p.second) {
          range.second = p.first;
        } else if (range.first >= p.first && range.second <= p.second) {
          range.first = 0;
          range.second = 0;
          break;
        } else if (range.first < p.first && range.second > p.second) {
            total_range -= p.second - p.first; 
            p.first = 0;
            p.second = 0;
        }
      }
      total_range += range.second - range.first;
      if (range.second != range.first) {
        row.push_back(range);
      }
    }
    if (total_range < MAX) {
      set<int> all_points;
      for (pair<int, int> &p : row) {
        for (int j = p.first; j < p.second; ++j) {
          all_points.insert(j);
        }
      }
      for (int j = 0; j < MAX; ++j) {
        if (!all_points.count(j)) {
          long long int solution = static_cast<long long int>(j) * 4000000 + static_cast<long long int>(i);
          cout << "Answer to part 2 is: " << solution << endl;
          return 0;
        }
      }
    }
  }
  cout << "No solution found for part 2" << endl;
  return 0;
}