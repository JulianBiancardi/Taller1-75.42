#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <vector>

//--------------------------------------------------------------------------------------
class Parser {
 private:
  std::string firstline;
  std::string method;
  std::string resource;
  std::string body;

 public:
  Parser();

  /*A partir de una petición se encargará de obtener los argumentos necesarios*/
  void operator()(const std::string& petition);
  std::string getFirstLine();
  std::string getMethod();
  std::string getResource();
  std::string getBody();

  ~Parser();
};

#endif  // __PARSER_H__
//--------------------------------------------------------------------------------------
