#ifndef __TH_CLIENT_H__
#define __TH_CLIENT_H__

#include <atomic>
#include <string>

#include "../common_src/Socket.h"
#include "Parser.h"
#include "ServerResources.h"
#include "Thread.h"

// ----------------------------------------------------------------------------
class ThClient final : public Thread {
 private:
  Socket peer;
  Parser parser;
  ServerResources& resources;
  std::string recv_msg;
  std::atomic_bool keep_talking;
  std::atomic_bool is_running;

  void recv();
  void getResponse();

 public:
  ThClient(Socket& socket, ServerResources& resources);

  ThClient(const ThClient&) = delete;              // No copy constructor
  ThClient& operator=(const ThClient&) = delete;   // No copy constructor
  ThClient(ThClient&& other) = delete;             // No move constructor
  ThClient& operator=(ThClient&& other) = delete;  // No move constructor

  /*Corre el hilo cliente comenzando la comunicacion con el servidor.*/
  void run() override;
  /*Indica si el hilo ya ha terminado su ejecucion.*/
  bool is_dead();
  /*Se fuerza el cierre de la ejecucion del hilo.*/
  void force_stop();

  ~ThClient();
};

#endif  // __TH_CLIENT_H__
//--------------------------------------------------------------------------------------
