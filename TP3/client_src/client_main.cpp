
#include <iostream>

#include "Client.h"

// ----------------------------------------------------------------------------
// Constantes para el manejo de errores

#define EXIT_CODE 0

#define ARGS_MIN 3
#define ARGV_HOST 1
#define ARGV_PORT 2

int main(int argc, char** argv) {
  if (argc < ARGS_MIN) {
    std::cout << "Error: el comando que ha ingresado no se reconoce. Quizas "
                 "quiso decir: ./client host port"
              << std::endl;
    return EXIT_CODE;
  }

  std::string hostname = argv[ARGV_HOST];
  std::string port = argv[ARGV_PORT];
  try {
    Client client(hostname, port);
    client.send();  // Send the petition to the server
    client.recv();  // Wait to the server respond
  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknow error" << std::endl;
  }

  return EXIT_CODE;
}

// ----------------------------------------------------------------------------
