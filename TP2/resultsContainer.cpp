#include "resultsContainer.h"

#include <algorithm>
#include <iostream>

resultsContainer::resultsContainer() {}

void resultsContainer::add(const std::string& result) {
  std::lock_guard<std::mutex> lock(mutex);

  results.push_back(result);
}

void resultsContainer::show() {
  // sort results in alphabetical order
  std::sort(results.begin(), results.end());

  for (auto& result : results) {
    std::cout << result << std::endl;
  }
}

resultsContainer::~resultsContainer() {}
