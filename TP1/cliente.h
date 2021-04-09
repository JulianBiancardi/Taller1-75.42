#ifndef __CLIENTE_H__
#define __CLIENTE_H__

// ----------------------------------------------------------------------------
#include <stddef.h>

#include "common_crypto.h"
#include "common_socket.h"
// ----------------------------------------------------------------------------

typedef struct cliente {
  socket_t socket;
  crypto_t crypto;
} cliente_t;

// ----------------------------------------------------------------------------

/*Inicializa el cliente, dejandolo en un estado valido.
 * Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int cliente_crear(cliente_t* this, const char* metodo, const char* clave);

/*Intenta conectarse a las direcciones posibles dadas por el host y puerto.
 * Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int cliente_conectar(cliente_t* this, const char* host, const char* puerto);

/*Envia N bytes del buffer por el socket.
 * Devuelve los bytes enviados o -1 en caso de error*/
int cliente_enviar(cliente_t* this, const char* buffer, size_t n);

/*Desinicializa el cliente, liberando los recursos.*/
void cliente_destruir(cliente_t* this);

// ----------------------------------------------------------------------------
#endif  // __CLIENTE_H__
