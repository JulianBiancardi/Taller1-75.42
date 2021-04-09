#include "ThClient.h"

#include <sys/socket.h>

#include <iostream>
#include <utility>

#include "RequestFactory.h"

#define BUFF_SIZE 64
#define SOCKET_CLOSED 0

//------------------------------------------------------------------------------
ThClient::ThClient(Socket& socket, ServerResources& resources)
    : peer(std::move(socket)),
      resources(resources),
      keep_talking(true),
      is_running(true) {}

void ThClient::getResponse() {
  parser(recv_msg);
  std::cout << parser.getFirstLine();

  RequestFactory factory;
  Request* request = factory.generateRequest(parser.getMethod());
  std::string server_msg =
      request->getResponse(resources, parser.getResource(), parser.getBody());

  peer.send(server_msg.c_str(), server_msg.size());
  delete request;
}

void ThClient::recv() {
  char buffer[BUFF_SIZE] = {0};
  size_t recibidos = peer.recv(buffer, BUFF_SIZE - 1);
  if (recibidos == SOCKET_CLOSED) {
    getResponse();
    keep_talking = false;
  } else {
    recv_msg.append(buffer);
  }
}

void ThClient::run() {
  try {
    while (keep_talking) {
      recv();
    }
    peer.shutdown(SHUT_RDWR);
  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknow error" << std::endl;
  }
  is_running = false;
}

bool ThClient::is_dead() { return !is_running; }

void ThClient::force_stop() {
  keep_talking = false;
  peer.shutdown(SHUT_RDWR);
}

ThClient::~ThClient() {}
//------------------------------------------------------------------------------
