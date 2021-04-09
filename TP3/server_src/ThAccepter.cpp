#include "ThAccepter.h"

#include <sys/socket.h>

#include <iostream>
#include <utility>

//------------------------------------------------------------------------------
ThAccepter::ThAccepter(const std::string& port, const size_t& max_clients,
                       const std::string& rootfile)
    : accepter(port, max_clients), resources(rootfile) {}

void ThAccepter::accept_client() {
  Socket peer = std::move(accepter.accept());
  ThClient* client = new ThClient(peer, resources);
  client->start();
  clients.push_back(client);
}

void ThAccepter::clean_deadclients() {
  std::vector<ThClient*> tmp;
  std::vector<ThClient*>::iterator it = clients.begin();

  for (; it != clients.end(); ++it) {
    if ((*it)->is_dead()) {
      (*it)->join();
      delete (*it);
    } else {
      tmp.push_back(*it);
    }
  }
  clients.swap(tmp);
}

void ThAccepter::join_clients() {
  for (auto& client : clients) {
    client->join();
    delete (client);
  }
}

void ThAccepter::clean_clients() {
  for (auto& client : clients) {
    client->force_stop();
    client->join();
    delete (client);
  }
}

void ThAccepter::run() {
  try {
    while (true) {
      accept_client();
      clean_deadclients();
    }
  } catch (const SocketClosedException& e) {
    join_clients();
  } catch (const std::runtime_error& e) {
    clean_clients();
    std::cerr << e.what() << std::endl;
  } catch (const std::exception& e) {
    clean_clients();
    std::cerr << e.what() << std::endl;
  } catch (...) {
    clean_clients();
    std::cerr << "Unknow error" << std::endl;
  }
}

void ThAccepter::close() {
  // Shutdown and close the accepter, no more connections
  accepter.shutdown(SHUT_RDWR);
  accepter.close();
}

ThAccepter::~ThAccepter() {}
//------------------------------------------------------------------------------
