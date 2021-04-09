#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__

// ----------------------------------------------------------------------------
#include "common_crypto.h"
#include "common_socket.h"
// ----------------------------------------------------------------------------

typedef struct servidor {
  socket_t aceptador;
  socket_t peer;
  crypto_t crypto;
} servidor_t;

/*Inicializa el servidor, dejandolo en un estado valido.
 * La cantidad de chunks para enviar/recibir por parte del servidor es de 4
 * bytes.
 *  Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int servidor_crear(servidor_t* this, const char* metodo, const char* clave);

/*Corre el serivdor en el host y puerto especificado.
 * Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int servidor_correr(servidor_t* this, const char* host, const char* puerto);

/*Desinicializa el servidor, liberando los recursos.*/
void servidor_destruir(servidor_t* this);

// ----------------------------------------------------------------------------
#endif  // __SERVIDOR_H__
