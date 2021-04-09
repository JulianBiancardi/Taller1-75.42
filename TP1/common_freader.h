#ifndef __FREADER_H__
#define __FREADER_H__

#include <stdio.h>

typedef struct file_reader {
  FILE* archivo;
} file_reader_t;

/*Por cada set de datos esta funcion sera invocada.
 * Se recibe el buffer que contiene los datos recibidos como asi tambien la
 * cantidad de bytes recibidos. Se cuenta ademas con un contexto, que
 * podra usar para lo que desea realizar.
 * Esta funcion  debe retornar 0 si no hubo errores, -1 en caso contrario. */
typedef int (*freader_t_callback_t)(const char* buffer, size_t resultado,
                                    void* contexto);

/*Inicializa el freader, dejandolo en un estado valido.
 * Se debe especificar el arhcivo del cual recibir datos. Si archivo == NULL se
 * leera por entrada estandar (stdin).
 * Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int freader_crear(file_reader_t* this, const char* archivo);

/*Recibe datos del archivo. Por cada set de datos recibidos la
 * funcion es incovada (ver freader_t_callback_t).
 * Devuelve 0 si no hubo errores, -1 en caso contrario.*/
int freader_iterar(file_reader_t* this, freader_t_callback_t funcion,
                   void* contexto);

/*Desinicializa el freader, liberando los recursos.*/
void freader_destruir(file_reader_t* this);

#endif  // __FREADER_H__
