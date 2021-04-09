#ifndef __THREAD_H__
#define __THREAD_H__

#include <thread>

// ----------------------------------------------------------------------------
class Thread {
 private:
  std::thread thread;

 public:
  Thread();

  Thread(const Thread&) = delete;              // No copy constructor
  Thread& operator=(const Thread&) = delete;   // No copy constructor
  Thread(Thread&& other) = delete;             // No move constructor
  Thread& operator=(Thread&& other) = delete;  // No move constructor

  void start();
  virtual void run() = 0;
  void join();

  ~Thread();
};

#endif  // __THREAD_H__
// ----------------------------------------------------------------------------
