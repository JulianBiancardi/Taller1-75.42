#ifndef __TH_ACCEPTER_H__
#define __TH_ACCEPTER_H__

#include <string>
#include <vector>

#include "../common_src/Socket.h"
#include "../common_src/SocketClosedException.h"
#include "ServerResources.h"
#include "ThClient.h"
#include "Thread.h"

//------------------------------------------------------------------------------
class ThAccepter : public Thread {
 private:
  Socket accepter;
  std::vector<ThClient*> clients;
  ServerResources resources;

  /*Espera una conexion entrante para poder generar un nuevo hilo y establecer
   * la comunicacion entre el cliente y el servidor*/
  void accept_client();
  /*Remueve los hilos que ya terminaron su ejecucion y por lo tanto consumen
   * recursos innecesarios*/
  void clean_deadclients();
  /*Remueve todos hilos que terminaron o no su ejecucion.*/
  void clean_clients();
  void join_clients();

 public:
  ThAccepter(const std::string& port, const size_t& max_clients,
             const std::string& rootfile);

  ThAccepter(const ThAccepter&) = delete;              // No copy constructor
  ThAccepter& operator=(const ThAccepter&) = delete;   // No copy constructor
  ThAccepter(ThAccepter&& other) = delete;             // No move constructor
  ThAccepter& operator=(ThAccepter&& other) = delete;  // No move constructor

  /*Corre el hilo aceptador esperando conexiones entrantes.*/
  void run() override;
  /*Cierra el socket aceptador por lo tanto no mas conexiones seran aceptadas.
   * Se cerraran todas las conexiones con los clientes vigentes.*/
  void close();

  ~ThAccepter();
};

#endif  // __TH_ACCEPTER_H__
//------------------------------------------------------------------------------
