#ifndef __POST_REQUEST_H__
#define __POST_REQUEST_H__

#include <string>

#include "Request.h"
//------------------------------------------------------------------------------
class PostRequest : public Request {
 public:
  PostRequest();

  std::string getResponse(ServerResources& resources,
                          const std::string& resource,
                          const std::string& content) override;
  ~PostRequest();
};

#endif  // __POST_REQUEST_H__
//------------------------------------------------------------------------------
