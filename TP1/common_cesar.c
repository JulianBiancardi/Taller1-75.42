#include "common_cesar.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXITO 0
#define ERROR -1

#define ASCII 256

int cesar_crear(cesar_t* this, const char* clave) {
  if (this == NULL || clave == NULL) {
    return ERROR;
  }

  size_t len = strlen(clave);
  if (len == 0) return ERROR;  // clave vacia

  char* resultado;
  this->clave = strtol(clave, &resultado, 10);
  if (resultado == clave) return ERROR;  // Error de parseo
  this->clave_pos = 0;

  return EXITO;
}

int cesar_cifrar(cesar_t* this, const char* msg, char* dest, size_t n) {
  for (size_t pos = 0; pos < n; pos++)
    dest[pos] = (msg[pos] + this->clave) % ASCII;

  return EXITO;
}

int cesar_descifrar(cesar_t* this, const char* msg, char* dest, size_t n) {
  for (size_t pos = 0; pos < n; pos++)
    dest[pos] = (msg[pos] - this->clave) % ASCII;

  return EXITO;
}

void cesar_destruir(cesar_t* this) { return; }
