#ifndef __VIGENERE_H__
#define __VIGENERE_H__

#include <stddef.h>

typedef struct vigenere {
  const char* clave;
  size_t clave_pos;
} vigenere_t;

/*Inicializa el cifrador, dejandolo en un estado valido.
 * Se debe especificar la clave usar. En caso de que sea NULL o este vacia
 * devolvera error.
 * Devuelve 0 si no  hubo errores, -1 en caso contrario.*/
int vigenere_crear(vigenere_t* this, const char* clave);

/*Cifra N bytes del mensaje, guardandolos en el destino.
 *  Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int vigenere_cifrar(vigenere_t* this, const char* msg, char* dest, size_t n);

/*Descifra N bytes del mensaje, guardandolos en el destino.
 *  Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int vigenere_descifrar(vigenere_t* this, const char* msg, char* dest, size_t n);

/*Desinicializa el cifrador, liberando los recursos.*/
void vigenere_destruir(vigenere_t* this);

// ----------------------------------------------------------------------------
#endif  // __VIGENERE_H__
