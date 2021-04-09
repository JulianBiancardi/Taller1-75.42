
#include <iostream>
#include <string>
#include <thread>

#include "ebpfVerifier.h"
#include "filesContainer.h"
#include "resultsContainer.h"

#define GOOD 0
#define FAIL -1

#define ARGS_MIN 2
#define FIRST_FILE 2
#define ARGV_THREAD 1

static void scans_files(filesContainer* icontainer,
                        resultsContainer* ocontainer) {
  while (true) {
    int status = GOOD;
    std::string file_name;
    file_name = icontainer->getfilename();
    if (file_name.empty()) {
      break;
    }
    ebpfVerifier verifier(file_name);
    if (verifier.isCyclic()) {
      ocontainer->add(std::string(file_name + " FAIL: cycle detected"));
      status = FAIL;
    } else if (verifier.isnonReachable()) {
      ocontainer->add(
          std::string(file_name + " FAIL: unused instructions detected"));
      status = FAIL;
    }
    if (status != FAIL) {
      ocontainer->add(std::string(file_name + " GOOD"));
    }
  }
}

int main(int args, char** argv) {
  if (args < ARGS_MIN) return -1;

  int n_threads = atoi(argv[ARGV_THREAD]);
  if (n_threads < 0) return -1;

  // Add the files into the files container
  filesContainer icontainer;
  for (int i = 0; i < (args - FIRST_FILE); i++) {
    std::string file_name = argv[FIRST_FILE + i];
    icontainer.add(file_name);
  }

  // Generate the output container for the threads results
  resultsContainer ocontainer;
  std::vector<std::thread> threads;
  for (int i = 0; i < n_threads; i++) {
    threads.push_back(std::thread(scans_files, &icontainer, &ocontainer));
  }

  // synchronize threads:
  for (size_t i = 0; i < threads.size(); i++) {
    threads[i].join();
  }

  // Show the results
  ocontainer.show();

  return 0;
}
