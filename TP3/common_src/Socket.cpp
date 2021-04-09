#include "Socket.h"

#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdint>
#include <stdexcept>  //Runtime error
#include <utility>

#define SERVER_HOST "0"
#define INVALID_SOCKET -1

//--------------------------------------------------------------------------------------
void Socket::set_fd(addrinfo* address) {
  fd = ::socket(address->ai_family, address->ai_socktype, address->ai_protocol);

  if (fd == INVALID_SOCKET) {
    ::freeaddrinfo(address);
    throw std::runtime_error("Error in function set_fd");
  }
}

void Socket::fixTimeWait(addrinfo* address) const {
  int val = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val))) {
    ::freeaddrinfo(address);
    throw std::runtime_error("Error in function fixTimeWait.");
  }
}

void Socket::get_address(const std::string& host, const std::string& port,
                         bool pasive, addrinfo** address) {
  struct addrinfo hints;  // filtros

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;                   // IPv4
  hints.ai_socktype = SOCK_STREAM;             // TCP
  hints.ai_flags = (pasive) ? AI_PASSIVE : 0;  // Server/Cliente

  if (getaddrinfo(&host[0], &port[0], &hints, address)) {
    freeaddrinfo(*address);
    throw std::runtime_error("Error in function get_adress.");
  }
}

Socket::Socket(int fd) : fd(fd) {}

void Socket::bind_listen(const std::string& host, const std::string& port,
                         const size_t& max_clients) {
  struct addrinfo* address;
  struct addrinfo* rp;
  get_address(host, port, true, &address);

  for (rp = address; rp != NULL; rp = rp->ai_next) {
    set_fd(address);
    fixTimeWait(address);
    if (::bind(fd, address->ai_addr, address->ai_addrlen) == 0) {
      break; /* Success */
    }
    close();
  }
  ::freeaddrinfo(address);
  if (::listen(fd, max_clients)) {
    throw std::runtime_error("Error in function listen");
  }
}

Socket Socket::accept() const {
  int peer_socket = ::accept(fd, NULL, NULL);
  if (peer_socket == INVALID_SOCKET) {
    throw SocketClosedException(
        "Error in function accept, the socket was closed.");
  }
  return Socket(peer_socket);
}

void Socket::connect(const std::string& host, const std::string& port) {
  struct addrinfo* address;
  struct addrinfo* rp;
  get_address(host, port, false, &address);

  bool connected = false;
  for (rp = address; rp != NULL and !connected; rp = rp->ai_next) {
    set_fd(address);
    if (::connect(fd, rp->ai_addr, rp->ai_addrlen))
      close();
    else
      connected = true;
  }
  ::freeaddrinfo(address);
  if (!connected) {
    throw std::runtime_error("Error in function connect");
  }
}

size_t Socket::send(const char* buffer, const size_t& len) const {
  size_t total = 0;
  ssize_t sent = 1;
  while (total < len and sent > 0) {
    sent = ::send(fd, &buffer[total], len - total, MSG_NOSIGNAL);
    total += sent;
  }
  if (sent == -1) {
    throw std::runtime_error("Error in function send");
  }
  return total;
}

size_t Socket::recv(char* buffer, const size_t& len) const {
  size_t total = 0;
  ssize_t recvs = 1;
  while (total < len and recvs > 0) {
    recvs = ::recv(this->fd, &buffer[total], len - total, 0);
    total += recvs;
  }
  if (recvs == -1) {
    throw std::runtime_error("Error in function recv");
  }
  return total;
}

void Socket::shutdown(const int& channel) {
  if (fd != INVALID_SOCKET) {
    if (::shutdown(fd, channel)) {
      throw std::runtime_error("Error in function shutdown");
    }
  }
}

void Socket::close() {
  if (fd != INVALID_SOCKET) {
    ::close(fd);
    fd = INVALID_SOCKET;
  }
}

Socket::Socket(Socket&& other) {
  fd = other.fd;
  other.fd = INVALID_SOCKET;
}

Socket& Socket::operator=(Socket&& other) {
  fd = std::move(other.fd);
  other.fd = INVALID_SOCKET;
  return *this;
}

Socket::Socket() : fd(INVALID_SOCKET) {}

Socket::Socket(const std::string& port, const size_t& max_clients) {
  bind_listen(SERVER_HOST, port, max_clients);
}

Socket::Socket(const std::string& host, const std::string& port) {
  connect(host, port);
}

Socket::~Socket() noexcept { close(); }
//--------------------------------------------------------------------------------------
