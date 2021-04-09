#include "common_freader.h"

#include <stdio.h>

#define EXITO 0
#define ERROR -1

#define LECTURA "rb"
#define BUFF_SIZE 64
#define CANTIDAD_LEER 64

int freader_crear(file_reader_t *this, const char *archivo) {
  if (this == NULL) return ERROR;

  this->archivo = (archivo != NULL) ? fopen(archivo, LECTURA) : stdin;

  if (this->archivo == NULL) return ERROR;

  return EXITO;
}

int freader_iterar(file_reader_t *this, freader_t_callback_t funcion,
                   void *contexto) {
  if (this == NULL) return ERROR;

  char buffer[BUFF_SIZE] = {0};
  while (!feof(this->archivo)) {
    size_t nleido = fread(buffer, sizeof(char), CANTIDAD_LEER, this->archivo);
    if (funcion(buffer, nleido, contexto)) {
      return ERROR;
    }
  }
  return EXITO;
}

void freader_destruir(file_reader_t *this) {
  if (this->archivo != stdin) fclose(this->archivo);

  return;
}
