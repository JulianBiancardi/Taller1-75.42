// ----------------------------------------------------------------------------
#include "server.h"

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "common_socket.h"

#define EXITO 0
#define ERROR -1

#define MAX_CLIENTES 1  // 1 clientes maximo para la cola de espera
#define SOCKET_CERRADO 1
#define SHUT_RD 0
#define SHUT_WR 1
#define SHUT_RDWR 2

#define BUFF_SIZE 64
#define CANT_RECIBIR 4
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------

static int _descifrarBuffer(servidor_t* this) {
  char buffer[BUFF_SIZE] = {0};
  ssize_t recibidos = socket_recibir(&(this->peer), buffer, CANT_RECIBIR);

  if (recibidos == 0) return SOCKET_CERRADO;
  if (recibidos == -1) return ERROR;

  char destino[BUFF_SIZE] = {0};
  crypto_descifrar(&(this->crypto), buffer, destino, recibidos);
  fwrite(destino, 1, recibidos, stdout);
  return EXITO;
}

static int _recibir(servidor_t* this) {
  // recibimos hasta que se cierre el socket del cliente
  int status;
  do {
    status = _descifrarBuffer(this);
  } while (status == EXITO);

  if (status != SOCKET_CERRADO) {
    return ERROR;
  }
  return EXITO;
}

int servidor_crear(servidor_t* this, const char* metodo, const char* clave) {
  socket_t socket_aceptador, socket_peer;
  crypto_t crypto;

  if (socket_crear(&socket_aceptador)) return ERROR;
  if (socket_crear(&socket_peer)) return ERROR;
  if (crypto_crear(&crypto, metodo, clave)) return ERROR;

  this->aceptador = socket_aceptador;
  this->peer = socket_peer;
  this->crypto = crypto;

  return EXITO;
}

int servidor_correr(servidor_t* this, const char* host, const char* puerto) {
  if (socket_bind_listen(&(this->aceptador), host, puerto, MAX_CLIENTES)) {
    servidor_destruir(this);
    return ERROR;
  }
  if (socket_aceptar(&(this->aceptador), &(this->peer))) {
    servidor_destruir(this);
    return ERROR;
  }

  if (_recibir(this)) {
    servidor_destruir(this);
    return ERROR;
  }
  return EXITO;
}

void servidor_destruir(servidor_t* this) {
  socket_apagar(&(this->aceptador), SHUT_RDWR);
  socket_apagar(&(this->peer), SHUT_RDWR);
  socket_destruir(&(this->aceptador));
  socket_destruir(&(this->peer));
  crypto_destruir(&(this->crypto));

  return;
}

// ----------------------------------------------------------------------------
