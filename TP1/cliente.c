// ----------------------------------------------------------------------------
#include "cliente.h"

#define EXITO 0
#define ERROR -1
#define SHUT_RD 0
#define SHUT_WR 1
#define SHUT_RDWR 2

#define BUFF_SIZE 64

int cliente_crear(cliente_t* this, const char* metodo, const char* clave) {
  socket_t socket;
  crypto_t crypto;

  if (socket_crear(&socket)) return ERROR;
  if (crypto_crear(&crypto, metodo, clave)) return ERROR;

  this->socket = socket;
  this->crypto = crypto;

  return EXITO;
}

int cliente_conectar(cliente_t* this, const char* host, const char* puerto) {
  return socket_conectar(&(this->socket), host, puerto);
}

int cliente_enviar(cliente_t* this, const char* buffer, size_t n) {
  char destino[BUFF_SIZE] = {0};
  crypto_cifrar(&(this->crypto), buffer, destino, n);

  return socket_enviar(&(this->socket), destino, n);
}

void cliente_destruir(cliente_t* this) {
  socket_apagar(&(this->socket), SHUT_RDWR);
  socket_destruir(&(this->socket));
  crypto_destruir(&(this->crypto));

  return;
}
// ----------------------------------------------------------------------------
