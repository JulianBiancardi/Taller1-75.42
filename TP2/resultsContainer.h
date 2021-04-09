#ifndef __RESULTSCONTAINER_H__
#define __RESULTSCONTAINER_H__

#include <mutex>
#include <string>
#include <vector>

class resultsContainer {
 private:
  std::vector<std::string> results;
  std::mutex mutex;

  // bool resultsContainer::has(const std::string& result) const;

 public:
  resultsContainer();

  void add(const std::string& result);
  void show();

  ~resultsContainer();
};

#endif  // __FILESCONTAINER_H__
