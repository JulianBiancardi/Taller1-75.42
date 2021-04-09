#include "Server.h"

#include <iostream>
#include <string>

#define STOP_COMMAND "q"

// ----------------------------------------------------------------------------

Server::Server(const std::string& port, const size_t& max_clients,
               const std::string& rootfile)
    : accepter(port, max_clients, rootfile) {}

void Server::run() {
  accepter.start();

  std::string character;
  do {
    std::getline(std::cin, character);
  } while (character != STOP_COMMAND);
}

Server::~Server() {
  accepter.close();
  accepter.join();
}

// ----------------------------------------------------------------------------
