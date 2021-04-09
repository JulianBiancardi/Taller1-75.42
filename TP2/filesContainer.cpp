
#include "filesContainer.h"

#include <iostream>

filesContainer::filesContainer() {}

void filesContainer::add(const std::string& file_name) {
  files_names.push(file_name);
}

std::string filesContainer::getfilename() {
  std::lock_guard<std::mutex> lock(mutex);

  std::string file_name;
  if (!files_names.empty()) {
    file_name = files_names.front();
    files_names.pop();
  }
  return file_name;
}

filesContainer::~filesContainer() {}
