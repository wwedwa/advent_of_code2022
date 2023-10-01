// Copyright 2022 William Edwards

#include<string>
using std::string;
#include<vector>
using std::vector;
#include<iostream>
using std::cout;
using std::endl;
#include<memory>
using std::unique_ptr;
#include<filesystem.h>

FileSystem::FileSystem(string name, int size, FileSystem *parent_dir) {
  name_ = name;
  size_ = size;
  contains_ = 0;
  parent_dir_ = parent_dir;
}

int FileSystem::CalcSize() {
  for (int i = 0; i < contains_; ++i) {
    size_ += content_[i]->CalcSize();
  }
  return size_;
}

void FileSystem::Add(unique_ptr<FileSystem> f) {
  ++contains_;
  content_.push_back(std::move(f));
}

void FileSystem::Print(int indent) const {
  for (int j = 0; j < indent; ++j) {
    cout << "  ";
  }
  cout << name_ << ": " << size_ << endl;
  for (const unique_ptr<FileSystem> &v : content_) {
    if (v->contains_ > 0) {
      v->Print(indent + 1);
    } else {
      for (int j = 0; j < indent + 1; ++j) {
        cout << "  ";
      }
      cout << v->name_ << ": " << v->size_ << endl;
    }
  }
}

bool FileSystem::IsIn(string name) const {
  for (const unique_ptr<FileSystem> &v : content_) {
    if (v->name_ == name) {
      return true;
    }
  }
  return false;
}

FileSystem* FileSystem::GetElement(string name) const {
  for (const unique_ptr<FileSystem> &v : content_) {
    if (v->name_ == name) {
      return v.get();
    }
  }
  return nullptr;
}

void FileSystem::CalculateAnswer() const {
  
}
