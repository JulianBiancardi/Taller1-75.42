

#include <iostream>

#include "Server.h"

// ----------------------------------------------------------------------------
// Constantes para el manejo de errores

#define SUCCED 0
#define ERROR 1

#define ARGS_MIN 3
#define ARGV_PORT 1
#define ARGV_ROOT 2

#define MAX_CLIENTS 10  // 10  clientes maximo por default

int main(int argc, char** argv) {
  if (argc != ARGS_MIN) {
    std::cout << "Error: el comando que ha ingresado no se reconoce. Quizas "
                 "quiso decir: ./server port <rootfile>."
              << std::endl;
    return ERROR;
  }

  try {
    Server server(argv[ARGV_PORT], MAX_CLIENTS, argv[ARGV_ROOT]);
    server.run();
  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknow error" << std::endl;
  }

  return SUCCED;
}

// ----------------------------------------------------------------------------
