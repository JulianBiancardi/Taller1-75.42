#ifndef __SOCKET_H__
#define __SOCKET_H__

// ----------------------------------------------------------------------------
#include <string>

#include "SocketClosedException.h"

class Socket {
 private:
  int fd;  // file descriptor

  explicit Socket(int fd);
  void set_fd(struct addrinfo* address);
  void fixTimeWait(struct addrinfo* address) const;
  void get_address(const std::string& host, const std::string& port,
                   bool pasive, addrinfo** address);

  /* Se intentara realizar un  bind del socket a las direcciones posibles.
   * Prepara el socket para escuchar conexiones en FD.
   * N conexiones maximas seran puestas en esperas hasta ser aceptadas. */
  void bind_listen(const std::string& host, const std::string& port,
                   const size_t& max_clients);

  /* Intenta conectarse a las direcciones posibles dadas por el host y puerto*/
  void connect(const std::string& host, const std::string& port);

 public:
  Socket();
  /* Constructor para obtener un servidor en el puerto especificado */
  Socket(const std::string& port, const size_t& max_clients);
  /* Constructor para obtener un cliente conectado al host y puerto */
  Socket(const std::string& host, const std::string& port);

  Socket(const Socket&) = delete;             // No copy constructor
  Socket& operator=(const Socket&) = delete;  // No copy constructor
  Socket(Socket&& other);                     // Move constructor
  Socket& operator=(Socket&& other);          // Move constructor

  /* Espera una conexion entrante.Devolvera un nuevo socket para poder
   * comunicarse. Esta funcion es bloqueante*/
  Socket accept() const;

  /* Envia len bytes del buffer por el FD. */
  size_t send(const char* buffer, const size_t& len) const;
  /* Recibe len bytes del buffer por el FD. */
  size_t recv(char* buffer, const size_t& len) const;

  /* Apaga el canal solicitado del socket. */
  void shutdown(const int& channel);
  /* Cierra el socket, apagando ambos canales de comunicacion */
  void close();

  ~Socket();
};

#endif  // __SOCKET_H__
