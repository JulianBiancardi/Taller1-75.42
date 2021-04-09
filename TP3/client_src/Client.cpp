#include "Client.h"

#include <sys/socket.h>

#include <iostream>

#define BUFF_SIZE 64
#define SOCKET_CLOSED 0

Client::Client(const std::string& host, const std::string& port)
    : socket(host, port) {}

void Client::send() {
  std::string line;
  while (std::getline(std::cin, line)) {
    line.append("\n");
    socket.send(line.c_str(), line.size());
  }
  // Close the write channel from the client
  socket.shutdown(SHUT_WR);
}

void Client::recv() {
  bool keep_recv = true;
  while (keep_recv) {
    char buffer[BUFF_SIZE] = {0};
    size_t recibidos = socket.recv(buffer, BUFF_SIZE - 1);
    if (recibidos == SOCKET_CLOSED) {
      keep_recv = false;
    } else {
      // Print the server message
      std::cout << buffer;
    }
  }
}

Client::~Client() {}

// ----------------------------------------------------------------------------
