#ifndef __FILESCONTAINER_H__
#define __FILESCONTAINER_H__

#include <mutex>
#include <queue>
#include <string>

class filesContainer {
 private:
  std::queue<std::string> files_names;
  std::mutex mutex;

 public:
  filesContainer();

  void add(const std::string& file_name);
  std::string getfilename();

  ~filesContainer();
};

#endif  // __FILESCONTAINER_H__
