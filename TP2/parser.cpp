#include "parser.h"

#include <string>

#define SUCCED 0
#define ERROR -1

#define LABEL_DELIM ':'
#define ARGUMENT_DELIM ','

parser::parser() {}

std::string parser::detect_label(const std::string line) const {
  std::string label;
  size_t label_pos = line.find_first_of(LABEL_DELIM);
  if (label_pos != std::string::npos) {
    label = line.substr(0, label_pos);
  }
  return label;
}

void parser::remove_label(std::string& line) const {
  std::string label = detect_label(line);
  if (!label.empty()) {
    line.erase(0, label.size() + 1);
  }
}

void parser::remove_whitespace(std::string& line) const {
  size_t current = line.find_first_not_of(' ');
  if (current != std::string::npos) {
    line.erase(0, current);
  }
}

void parser::clean_argument(std::string& argument) const {
  // removes the coma "," of the argument
  size_t pos = argument.find(ARGUMENT_DELIM);
  if (pos != std::string::npos) {
    argument.erase(pos, 1);
  }
}

void parser::split(const std::string& str, std::vector<std::string>& args,
                   char delim) const {
  size_t current, previous = 0;

  current = str.find(delim);
  while (current != std::string::npos) {
    std::string argument = str.substr(previous, current - previous);
    clean_argument(argument);
    args.push_back(argument);
    previous = current + 1;
    current = str.find(delim, previous);
  }
  args.push_back(str.substr(previous, current - previous));
}

std::vector<std::string> parser::iterate(const std::string line) const {
  std::vector<std::string> arguments;

  std::string line_aux = line;
  remove_label(line_aux);
  remove_whitespace(line_aux);
  split(line_aux, arguments, ' ');

  return arguments;
}

parser::~parser() {}
