#include "GetRequest.h"

//------------------------------------------------------------------------------
GetRequest::GetRequest() {}

std::string GetRequest::getResponse(ServerResources& resources,
                                    const std::string& resource,
                                    const std::string& content) {
  std::string response;
  std::string body = resources.getBody(resource);
  if (resource == "/") {
    response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + body;
  } else {
    if (body.empty()) {
      response = "HTPP/1.1 404 NOT FOUND\n\n";
    } else {
      response = "HTPP/1.1 200 OK\n\n " + body;
    }
  }
  return response;
}

GetRequest::~GetRequest() {}
//------------------------------------------------------------------------------
