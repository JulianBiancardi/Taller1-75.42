#ifndef __SOCKET_H__
#define __SOCKET_H__

// ----------------------------------------------------------------------------
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
// ----------------------------------------------------------------------------

typedef struct addrinfo addrinfo_t;

typedef struct socket {
  int fd;  // file descriptor del socket.
  struct addrinfo* direcciones;
} socket_t;

// ----------------------------------------------------------------------------

/*Inicializa el socket, dejandolo en un estado valido.
 * Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int socket_crear(socket_t* this);

/*Se intentara realizar un  bind del socket a las direcciones posibles.*/
/*Prepara el socket para escuchar conexiones en FD.
 * N conexiones maximas seran puestas en esperas hasta ser aceptadas.
 * Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int socket_bind_listen(socket_t* this, const char* host, const char* puerto,
                       int max_clientes);

/*Espera una conexion entrante en el socket_aceptado.
 * Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int socket_aceptar(socket_t* this, socket_t* socket_aceptado);

/*intenta conectarse a las direcciones posibles (ver socket_get_direcciones)
 * Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int socket_conectar(socket_t* this, const char* host, const char* puerto);

/*Envia N bytes del buffer por el FD.
 * Devuelve los bytes enviados o -1 en caso de error*/
ssize_t socket_enviar(socket_t* this, char* buffer, size_t n);

/*Recibe N bytes del buffer por el FD.
 * Devuelve los bytes recibidos o -1 en caso de error*/
ssize_t socket_recibir(socket_t* this, char* buffer, size_t n);

/*Apaga el canal solicitado del socket.
 * 0 == CANAL LECTURA,
 * 1 == CANAL ESCRITURA,
 * 2 == AMBOS CANALES
 * Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int socket_apagar(socket_t* this, int canal);

/*Desinicializa el socket, liberando los recursos.*/
void socket_destruir(socket_t* this);

// ----------------------------------------------------------------------------
#endif  // __SOCKET_H__
