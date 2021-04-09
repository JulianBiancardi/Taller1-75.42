#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <vector>

class parser {
 private:
  void remove_label(std::string& line) const;
  void remove_whitespace(std::string& line) const;
  void clean_argument(std::string& argument) const;
  void split(const std::string& line, std::vector<std::string>& args,
             char delim = ' ') const;

 public:
  parser();
  std::string detect_label(const std::string line) const;
  std::vector<std::string> iterate(const std::string line) const;
  ~parser();
};

#endif  // __PARSER_H__
