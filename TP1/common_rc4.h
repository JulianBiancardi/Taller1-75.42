#ifndef __RC4_H__
#define __RC4_H__

#include <stddef.h>

typedef struct rc4 {
  const char* clave;
  char S[256];
  size_t clave_pos;
  size_t j_pos;
} rc4_t;

/*Inicializa el cifrador, dejandolo en un estado valido.
 * Se debe especificar la clave usar. En caso de que sea NULL o este vacia
 * devolvera error.
 * Devuelve 0 si no  hubo errores, -1 en caso contrario.*/
int rc4_crear(rc4_t* this, const char* clave);

/*Cifrar N bytes del mensaje, guardandolos en el destino.
 *  Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int rc4_cifrar(rc4_t* this, const char* msg, char* dest, size_t n);

/*Descifra N bytes del mensaje, guardandolos en el destino.
 *  Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int rc4_descifrar(rc4_t* this, const char* msg, char* dest, size_t n);

/*Desinicializa el cifrador, liberando los recursos.*/
void rc4_destruir(rc4_t* this);

// ----------------------------------------------------------------------------
#endif  // __RC4_H__
