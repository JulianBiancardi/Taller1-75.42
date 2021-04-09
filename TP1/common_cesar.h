#ifndef __CESAR_H__
#define __CESAR_H__

#include <stddef.h>

typedef struct cesar {
  long clave;
  size_t clave_pos;
} cesar_t;

/*Inicializa el cifrador, dejandolo en un estado valido.
 * Se debe especificar la clave usar. En caso de que sea NULL o este vacia
 * devolvera error.
 * Devuelve 0 si no  hubo errores, -1 en caso contrario.*/
int cesar_crear(cesar_t* this, const char* clave);

/*Cifrar N bytes del mensaje, guardandolos en el destino.
 *  Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int cesar_cifrar(cesar_t* this, const char* msg, char* dest, size_t n);

/*Descifra N bytes del mensaje, guardandolos en el destino.
 *  Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int cesar_descifrar(cesar_t* this, const char* msg, char* dest, size_t n);

/*Desinicializa el cifrador, liberando los recursos.*/
void cesar_destruir(cesar_t* this);

// ----------------------------------------------------------------------------
#endif  // __CESAR_H__
