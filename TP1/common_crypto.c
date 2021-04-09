#include "common_crypto.h"

#include <stdlib.h>
#include <string.h>

#include "common_cesar.h"
#include "common_rc4.h"
#include "common_vigenere.h"

#define EXITO 0
#define ERROR -1

int crypto_crear(crypto_t* this, const char* metodo, const char* clave) {
  if (this == NULL || metodo == NULL || clave == NULL) return ERROR;

  if (strncmp(metodo, "cesar", 5) == 0) {
    this->metodo = CESAR;
    this->cifrador = (cesar_t*)malloc(sizeof(cesar_t));
    return cesar_crear(this->cifrador, clave);
  } else if (strncmp(metodo, "vigenere", 8) == 0) {
    this->metodo = VIGENERE;
    this->cifrador = (vigenere_t*)malloc(sizeof(vigenere_t));
    return vigenere_crear(this->cifrador, clave);
  } else if (strncmp(metodo, "rc4", 3) == 0) {
    this->metodo = RC4;
    this->cifrador = (rc4_t*)malloc(sizeof(rc4_t));
    return rc4_crear(this->cifrador, clave);
  } else {
    return ERROR;
  }
}

int crypto_cifrar(crypto_t* this, const char* msg, char* dest, size_t n) {
  if (this == NULL || msg == NULL || dest == NULL) return ERROR;

  switch (this->metodo) {
    case CESAR:
      return cesar_cifrar(this->cifrador, msg, dest, n);
      break;
    case VIGENERE:
      return vigenere_cifrar(this->cifrador, msg, dest, n);
      break;
    case RC4:
      return rc4_cifrar(this->cifrador, msg, dest, n);
      break;
    default:
      return ERROR;
  }
}

int crypto_descifrar(crypto_t* this, const char* msg, char* dest, size_t n) {
  if (this == NULL || msg == NULL || dest == NULL) return ERROR;

  switch (this->metodo) {
    case CESAR:
      return cesar_descifrar(this->cifrador, msg, dest, n);
      break;
    case VIGENERE:
      return vigenere_descifrar(this->cifrador, msg, dest, n);
      break;
    case RC4:
      return rc4_descifrar(this->cifrador, msg, dest, n);
      break;
    default:
      return ERROR;
  }
}

void crypto_destruir(crypto_t* this) {
  if (this != NULL) {
    switch (this->metodo) {
      case CESAR:
        cesar_destruir(this->cifrador);
        break;
      case VIGENERE:
        vigenere_destruir(this->cifrador);
        break;
      case RC4:
        rc4_destruir(this->cifrador);
        break;
      default:
        return;
    }
    free(this->cifrador);
  }
  return;
}
