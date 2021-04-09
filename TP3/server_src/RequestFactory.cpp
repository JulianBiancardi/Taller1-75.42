#include "RequestFactory.h"

#include "GetRequest.h"
#include "PostRequest.h"
#include "UnknowRequest.h"

//------------------------------------------------------------------------------
RequestFactory::RequestFactory() {}

Request* RequestFactory::generateRequest(const std::string& method) const {
  if (method == "POST") {
    return new PostRequest;
  } else if (method == "GET") {
    return new GetRequest;
  } else {
    return new UnknowRequest(method);
  }
}

RequestFactory::~RequestFactory() {}
//------------------------------------------------------------------------------
