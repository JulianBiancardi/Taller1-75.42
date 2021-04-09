#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <string>

#include "ServerResources.h"
//#define HTTP "HTPP/1.1"

//------------------------------------------------------------------------------
class Request {
 public:
  Request();

  virtual std::string getResponse(ServerResources& resources,
                                  const std::string& resource,
                                  const std::string& content) = 0;

  virtual ~Request();
};

#endif  // __REQUEST_H__
//------------------------------------------------------------------------------
