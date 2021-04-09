#ifndef __CLIENT_H__
#define __CLIENT_H__

// ----------------------------------------------------------------------------
#include <stddef.h>

#include <string>

#include "../common_src/Socket.h"
// ----------------------------------------------------------------------------

class Client {
 private:
  Socket socket;

 public:
  Client(const std::string& host, const std::string& port);

  void send();
  void recv();

  ~Client();
};

// ----------------------------------------------------------------------------
#endif  // __CLIENT_H__
