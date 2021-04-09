#ifndef __GET_REQUEST_H__
#define __GET_REQUEST_H__

#include <string>

#include "Request.h"
//------------------------------------------------------------------------------
class GetRequest : public Request {
 public:
  GetRequest();

  std::string getResponse(ServerResources& resources,
                          const std::string& resource,
                          const std::string& content) override;

  ~GetRequest();
};

#endif  // __GET_REQUEST_H__
//------------------------------------------------------------------------------
