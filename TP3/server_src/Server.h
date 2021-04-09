#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__

#include <string>

#include "ThAccepter.h"

// ----------------------------------------------------------------------------

class Server {
 private:
  ThAccepter accepter;

 public:
  Server(const std::string& port, const size_t& max_client,
         const std::string& rootfile);

  void run();

  ~Server();
};

// ----------------------------------------------------------------------------
#endif  // __SERVIDOR_H__
