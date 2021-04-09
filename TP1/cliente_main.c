// ----------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>

#include "cliente.h"
#include "common_freader.h"

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Constantes para el manejo de errores

#define EXITO 0
#define ERROR -1

#define ARGUMENTOS_NECESARIOS 5
#define ARGV_HOST 1
#define ARGV_PUERTO 2
#define ARGV_METODO 3
#define ARGV_CLAVE 4

// ----------------------------------------------------------------------------

static int _enviarBuffer(const char* buffer, size_t nleido, void* contexto) {
  cliente_t* cliente = contexto;

  return (cliente_enviar(cliente, buffer, nleido) == ERROR) ? ERROR : EXITO;
}

int main(int argc, char** argv) {
  if (argc != ARGUMENTOS_NECESARIOS) {
    printf(
        "Error: el comando que ha ingresado no se reconoce. ./client host port "
        "--method=<value> --key=<value> ..\n");
    return ERROR;
  }

  char* metodo = strchr(argv[ARGV_METODO], '=');
  char* clave = strchr(argv[ARGV_CLAVE], '=');

  cliente_t cliente;
  printf("Creando el cliente...\n");
  if (cliente_crear(&cliente, ++metodo, ++clave)) {
    printf("Error: no se pudo crear el cliente.\n");
    return ERROR;
  }

  printf("Conectandose al servidor...\n");
  if (cliente_conectar(&cliente, argv[ARGV_HOST], argv[ARGV_PUERTO])) {
    printf("Error: no se pudo conectar.\n");
    cliente_destruir(&cliente);
    return ERROR;
  }

  printf("Conectado\n");

  file_reader_t freader;
  if (freader_crear(&freader, NULL)) {  // Leer de stdin
    printf("Error: no se pudo crear el freader.\n");
    cliente_destruir(&cliente);
    return ERROR;
  }

  if (freader_iterar(&freader, _enviarBuffer, &cliente)) {
    printf("Error: hubo un problema al leer el archivo.\n");
    freader_destruir(&freader);
    cliente_destruir(&cliente);
    return ERROR;
  }

  freader_destruir(&freader);
  cliente_destruir(&cliente);

  return EXITO;
}

// ----------------------------------------------------------------------------
