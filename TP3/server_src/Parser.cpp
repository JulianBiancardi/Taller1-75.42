#include "Parser.h"

#include <iostream>
#include <sstream>

#define WHITE_SPACE ' '
#define LINE_DELIM "\n"

//--------------------------------------------------------------------------------------
Parser::Parser() {}

void Parser::operator()(const std::string& petition) {
  std::istringstream iss(petition);

  std::string line;
  bool isfirstline = true;
  bool bodynext = false;
  while (getline(iss, line)) {
    if (isfirstline) {
      firstline = line.append(LINE_DELIM);
      std::istringstream iss_firstline(line);
      getline(iss_firstline, method, WHITE_SPACE);
      getline(iss_firstline, resource, WHITE_SPACE);
      isfirstline = false;
    } else if (bodynext) {
      body.append(line.append(LINE_DELIM));
    } else if (line.empty()) {
      bodynext = true;
    }
  }
}

std::string Parser::getFirstLine() { return firstline; }
std::string Parser::getMethod() { return method; }
std::string Parser::getResource() { return resource; }
std::string Parser::getBody() { return body; }

Parser::~Parser() {}
//--------------------------------------------------------------------------------------
