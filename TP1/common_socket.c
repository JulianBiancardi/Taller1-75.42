/**
 * Para avisarle al compilador que vamos a usar las extensiones POSIX que no
 * estan incluidas en el std=c99.
 */

#define _POSIX_C_SOURCE 200112L

// ----------------------------------------------------------------------------
#include "common_socket.h"

#include <netdb.h>
#include <string.h>
#include <sys/socket.h>

#define EXITO 0
#define ERROR -1
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------

static int _fix_tiempo_espera(socket_t* this) {
  int val = 1;
  if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val))) {
    freeaddrinfo(this->direcciones);
    return ERROR;
  }
  return EXITO;
}

static int _set_fd(socket_t* self, addrinfo_t* direcciones) {
  self->fd = socket(direcciones->ai_family, direcciones->ai_socktype,
                    direcciones->ai_protocol);

  return (self->fd == -1) ? ERROR : EXITO;
}

/*Obtiene la lista de direcciones, dadas por el host y puerto, a las que se
 * intentará conectar.Si se coloca como pasivo se obtendran solo direcciones
 * remotas.
 * Devuelve 0 si no hubo errores, -1 en caso contrario.*/
static int _get_direcciones(socket_t* this, const char* host,
                            const char* puerto, bool pasivo) {
  int resultado;
  struct addrinfo hints;  // filtros

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;                   // IPv4
  hints.ai_socktype = SOCK_STREAM;             // TCP
  hints.ai_flags = (pasivo) ? AI_PASSIVE : 0;  // Server/Cliente

  resultado = getaddrinfo(host, puerto, &hints, &(this->direcciones));
  if (resultado != 0) {
    freeaddrinfo(this->direcciones);
    return ERROR;
  }
  return EXITO;
}

int socket_crear(socket_t* this) {
  if (this == NULL) {
    return ERROR;
  }
  this->fd = -1;
  return EXITO;
}

int socket_bind_listen(socket_t* this, const char* host, const char* puerto,
                       int max_clientes) {
  if (_get_direcciones(this, host, puerto, true)) return ERROR;

  struct addrinfo* rp;
  for (rp = this->direcciones; rp != NULL; rp = rp->ai_next) {
    if (_set_fd(this, this->direcciones)) {
      return ERROR;
    }
    if (_fix_tiempo_espera(this)) {
      return ERROR;
    }
    if (bind(this->fd, rp->ai_addr, rp->ai_addrlen) == 0) {
      break; /* Success */
    }
    close(this->fd);
  }

  freeaddrinfo(this->direcciones); /* No longer needed */
  return listen(this->fd, max_clientes);
}

int socket_conectar(socket_t* this, const char* host, const char* puerto) {
  if (_get_direcciones(this, host, puerto, false)) return ERROR;

  bool conectado = false;
  struct addrinfo* rp;
  for (rp = this->direcciones; rp != NULL && !conectado; rp = rp->ai_next) {
    if (_set_fd(this, rp)) return ERROR;

    if (connect(this->fd, rp->ai_addr, rp->ai_addrlen))
      close(this->fd);
    else
      conectado = true;
  }

  freeaddrinfo(this->direcciones);
  return (!conectado);
}

int socket_aceptar(socket_t* this, socket_t* socket_aceptado) {
  socket_aceptado->fd = accept(this->fd, NULL, NULL);

  return (socket_aceptado->fd == -1) ? ERROR : EXITO;
}

ssize_t socket_enviar(socket_t* self, char* buffer, size_t n) {
  ssize_t total = 0;
  while (total < n) {
    ssize_t enviados = send(self->fd, &buffer[total], n - total, MSG_NOSIGNAL);

    if (enviados == -1) {
      return ERROR;
    } else if (enviados == 0) {
      return total;
    } else {
      total += enviados;
    }
  }
  return total;
}

ssize_t socket_recibir(socket_t* this, char* buffer, size_t n) {
  size_t total = 0;
  while (total < n) {
    ssize_t recibidos = recv(this->fd, &buffer[total], n - total, 0);

    if (recibidos == -1) {
      return ERROR;
    } else if (recibidos == 0) {  // socket cerrado
      return total;
    } else {
      total += recibidos;
    }
  }
  return total;
}

int socket_apagar(socket_t* this, int canal) {
  return shutdown(this->fd, canal);
}

void socket_destruir(socket_t* this) {
  close(this->fd);
  return;
}

// ----------------------------------------------------------------------------
