#ifndef __CRYPTO_H__
#define __CRYPTO_H__

#include <stddef.h>

typedef enum { CESAR, VIGENERE, RC4 } metodo_cifrado_t;

typedef struct crypto_t {
  metodo_cifrado_t metodo;
  void* cifrador;
} crypto_t;

/*Inicializa el crypto, dejandolo en un estado valido.
 * Se debe especificar que metodo y clave usar. En caso de que cualquiera de
 * estos parametros sean NULL o esten vacios devolvera error.
 * Devuelve 0 si no  hubo errores, -1 en caso contrario.*/
int crypto_crear(crypto_t* this, const char* metodo, const char* clave);

/*Encripta N bytes del mensaje, guardandolos en el destino. El metodo de
 * encriptacion esta definido por la inicializacion (ver crypto_init).
 *  Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int crypto_cifrar(crypto_t* this, const char* msg, char* dest, size_t n);

/*Desencripta N bytes del mensaje, guardandolos en el destino. El metodo de
 * desencriptacion esta definido por la inicializacion (ver crypto_init).
 *  Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int crypto_descifrar(crypto_t* this, const char* msg, char* dest, size_t n);

/*Desinicializa el servidor, liberando los recursos.*/
void crypto_destruir(crypto_t* this);

#endif /* __CRYPTO_H__ */
