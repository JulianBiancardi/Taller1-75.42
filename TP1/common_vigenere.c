#include "common_vigenere.h"

#include <stdlib.h>
#include <string.h>

#define EXITO 0
#define ERROR -1

#define DELIM '\0'
#define ASCII 256

int vigenere_crear(vigenere_t* this, const char* clave) {
  if (this == NULL || clave == NULL) {
    return ERROR;
  }

  size_t len = strlen(clave);
  if (len == 0) return ERROR;  // clave vacia o exedida

  this->clave = clave;
  this->clave_pos = 0;

  return EXITO;
}

int vigenere_cifrar(vigenere_t* this, const char* msg, char* dest, size_t n) {
  for (size_t pos_msg = 0; pos_msg < n; pos_msg++) {
    dest[pos_msg] = msg[pos_msg] + this->clave[this->clave_pos];
    (this->clave_pos)++;
    if (this->clave[this->clave_pos] == DELIM) this->clave_pos = 0;
  }

  return EXITO;
}

int vigenere_descifrar(vigenere_t* this, const char* msg, char* dest,
                       size_t n) {
  for (size_t pos_msg = 0; pos_msg < n; pos_msg++) {
    char resta = msg[pos_msg] - this->clave[this->clave_pos];
    dest[pos_msg] = (resta + (resta >= 0 ? 0 : ASCII)) % ASCII;
    (this->clave_pos)++;
    if (this->clave[this->clave_pos] == DELIM) this->clave_pos = 0;
  }

  return EXITO;
}

void vigenere_destruir(vigenere_t* this) { return; }
