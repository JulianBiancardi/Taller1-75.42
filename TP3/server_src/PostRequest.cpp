#include "PostRequest.h"

//------------------------------------------------------------------------------
PostRequest::PostRequest() {}

std::string PostRequest::getResponse(ServerResources& resources,
                                     const std::string& resource,
                                     const std::string& content) {
  std::string response;
  try {
    resources.addResource(resource, content);
    response = "HTTP/1.1 200 OK\n\n" + content;
  } catch (const std::exception& e) {
    response = "HTTP/1.1 403 FORBIDDEN\n\n";
  }
  return response;
}

PostRequest::~PostRequest() {}
//------------------------------------------------------------------------------
