#ifndef __REQUEST_FACTORY_H__
#define __REQUEST_FACTORY_H__

#include <string>

#include "Request.h"
//------------------------------------------------------------------------------
class RequestFactory {
 public:
  RequestFactory();

  Request* generateRequest(const std::string& method) const;

  ~RequestFactory();
};

#endif  // __REQUEST_FACTORY_H__
//------------------------------------------------------------------------------
