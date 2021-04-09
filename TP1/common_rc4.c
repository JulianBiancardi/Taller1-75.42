#include "common_rc4.h"

#include <stdlib.h>
#include <string.h>

#define EXITO 0
#define ERROR -1

#define ASCII 256

static void _swap(char* S, size_t i, size_t j) {
  char aux = S[i];
  S[i] = S[j];
  S[j] = aux;
}

static void _ksa(rc4_t* this, size_t len) {
  for (size_t i = 0; i < ASCII; i++) {
    this->S[i] = i;
  }
  unsigned char j = 0;
  for (size_t i = 0; i < ASCII; i++) {
    j = (j + this->S[i] + this->clave[i % len]) % ASCII;
    _swap(this->S, i, j);
  }
}

static char _prga(rc4_t* this) {
  this->clave_pos = (this->clave_pos + 1) % ASCII;
  this->j_pos = (this->j_pos + this->S[this->clave_pos]) % ASCII;
  _swap(this->S, this->clave_pos, this->j_pos);
  unsigned char t = (this->S[this->clave_pos] + this->S[this->j_pos]) % ASCII;
  return this->S[t];
}

int rc4_crear(rc4_t* this, const char* clave) {
  if (this == NULL || clave == NULL) {
    return ERROR;
  }

  size_t largo = strlen(clave);
  if (largo == 0 || largo > ASCII) return ERROR;  // clave vacia o exedida

  this->clave = clave;
  this->clave_pos = 0;
  this->j_pos = 0;
  _ksa(this, largo);

  return EXITO;
}

int rc4_cifrar(rc4_t* this, const char* msg, char* dest, size_t n) {
  for (size_t pos = 0; pos < n; pos++) {
    dest[pos] = msg[pos] ^ _prga(this);
  }
  return EXITO;
}

int rc4_descifrar(rc4_t* this, const char* msg, char* dest, size_t n) {
  return rc4_cifrar(this, msg, dest, n);
}

void rc4_destruir(rc4_t* this) { return; }
