// Copyright 2022 William Edwards

#include<iostream>
using std::cout;
using std::endl;
#include<string>
using std::string;
using std::stoi;
#include<fstream>
using std::ifstream;
using std::getline;
#include<vector>
using std::vector;
#include<sstream>
using std::istringstream;
#include<memory>
using std::unique_ptr;
using std::make_unique;
#include<filesystem.h>

int main() {
  ifstream terminal("system_browse.txt");
  string line;
  unique_ptr<FileSystem> file_sys = make_unique<FileSystem>("/");
  auto curr_dir = file_sys.get();
  while (getline(terminal, line)) {
    istringstream output(line);
    string symbol;
    output >> symbol;
    if (symbol == "$") {  // Line is a command
      string command;
      output >> command;
      if (command == "cd") {  // Line is cd command
        string go_to;
        output >> go_to;
        if (go_to == "..") {  // Move back
          cout << "Moving back to " << (curr_dir->parent_dir_)->name_ << endl;
          curr_dir = curr_dir->parent_dir_;
        } else if (go_to == "/") {  // Move to root
          cout << "Moving to root (" << file_sys->name_ << ")" << endl;
          curr_dir = file_sys.get();
        } else {  // Move to given directory
          cout << "Move to " << go_to << endl;
          if (curr_dir->IsIn(go_to)) {
            curr_dir = curr_dir->GetElement(go_to);
          }
        }
      }
    } else {  // Line is not a command and instead a file/dir to add
      if (symbol == "dir") {  // Line describes a directory
        string dir_name;
        output >> dir_name;
        cout << "Adding directory " << dir_name << " to " << curr_dir->name_ << endl;
        curr_dir->Add(make_unique<FileSystem>(dir_name, 0, curr_dir));
      } else {  // Line describes a file
        int size = stoi(symbol);
        string file_name;
        output >> file_name;
        cout << "Adding file " << file_name << " to " << curr_dir->name_ << endl;
        curr_dir->Add(make_unique<FileSystem>(file_name, size, curr_dir));
      }
    }
  }
  file_sys->CalcSize();
  file_sys->Print();
  return 0;
}