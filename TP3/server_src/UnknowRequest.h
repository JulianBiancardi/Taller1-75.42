#ifndef __UNKNOW_REQUEST_H__
#define __UNKNOW_REQUEST_H__

#include <string>

#include "Request.h"
//------------------------------------------------------------------------------
class UnknowRequest : public Request {
 private:
  std::string method;

 public:
  explicit UnknowRequest(const std::string& method);

  std::string getResponse(ServerResources& resources,
                          const std::string& resource,
                          const std::string& content) override;
  ~UnknowRequest();
};

#endif  // __UNKNOW_REQUEST_H__
//------------------------------------------------------------------------------
