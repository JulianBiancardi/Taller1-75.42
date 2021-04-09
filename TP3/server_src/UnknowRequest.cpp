#include "UnknowRequest.h"

//------------------------------------------------------------------------------
UnknowRequest::UnknowRequest(const std::string& method) : method(method) {}

std::string UnknowRequest::getResponse(ServerResources& resources,
                                       const std::string& resource,
                                       const std::string& content) {
  std::string response = "HTTP/1.1 405 METHOD NOT ALLOWED\n\n" + method +
                         " es un comando desconocido";

  return response;
}

UnknowRequest::~UnknowRequest() {}
//------------------------------------------------------------------------------
