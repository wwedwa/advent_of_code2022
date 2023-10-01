// Copyright 2022 William Edwards

#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<memory>
using std::unique_ptr;

struct FileSystem {
  // Constructor
  explicit FileSystem(string name, int size = 0, FileSystem *parent_dir = nullptr);
  FileSystem(const FileSystem&) = delete;
  FileSystem& operator=(const FileSystem&) = delete;
  // Calculate total size of the file system
  int CalcSize();
  // Add a file/directory
  void Add(unique_ptr<FileSystem> f);
  // Print out sub directories and files
  void Print(int indent = 0) const;
  /// Find if something is in directory
  bool IsIn(string name) const;
  // Find an element of same name and return a pointer to it
  FileSystem* GetElement(string name) const;
  // Calculate puzzle answer
  void CalculateAnswer() const;
  // Struct members
  string name_;
  int size_;
  int contains_;
  FileSystem *parent_dir_;
  vector<unique_ptr<FileSystem>> content_;
};
#endif  // _FILESYSTEM_H_