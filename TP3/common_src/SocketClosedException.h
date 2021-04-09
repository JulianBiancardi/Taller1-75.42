#ifndef __SOCKET_CLOSED_EXCEPTION_H__
#define __SOCKET_CLOSED_EXCEPTION_H__

#include <stdexcept>
#include <string>

//-----------------------------------------------------------------------------

class SocketClosedException : public std::runtime_error {
 public:
  explicit SocketClosedException(const std::string& msg_error) noexcept
      : runtime_error(msg_error) {}
};

//-----------------------------------------------------------------------------
#endif  // __SOCKET_CLOSED_EXCEPTION_H__
