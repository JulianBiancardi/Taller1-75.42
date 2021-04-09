// ----------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>

#include "server.h"
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Constantes para el manejo de errores

#define EXITO 0
#define ERROR -1

#define ARGUMENTOS_NECESARIOS 4
#define HOST 0
#define ARGV_PUERTO 1
#define ARGV_METODO 2
#define ARGV_CLAVE 3

int main(int argc, char** argv) {
  if (argc != ARGUMENTOS_NECESARIOS) {
    printf(
        "Error: el comando que ha ingresado no se reconoce. Quizas quiso decir "
        ": ./server port --method=<value> --key=<value>\n");
    return ERROR;
  }

  char* metodo = strchr(argv[ARGV_METODO], '=');
  char* clave = strchr(argv[ARGV_CLAVE], '=');

  servidor_t servidor;
  if (servidor_crear(&servidor, ++metodo, ++clave)) {
    printf("Error: no se pudo crear el servidor.\n");
    return ERROR;
  }

  if (servidor_correr(&servidor, HOST, argv[ARGV_PUERTO])) {
    servidor_destruir(&servidor);
    printf("Error: no se pudo correr el servidor.\n");
    return ERROR;
  }

  servidor_destruir(&servidor);

  return EXITO;
}

// ----------------------------------------------------------------------------
