#ifndef __EBPFVERIFIER_H__
#define __EBPFVERIFIER_H__

#include <map>
#include <string>
#include <vector>

#include "graph.h"
#include "parser.h"

class ebpfVerifier {
 private:
  std::string file_name;
  parser parseador;
  std::map<std::string, size_t> symbol_table;
  size_t prg_lines;
  bool cyclic_status;
  bool nonreachable_status;

  std::vector<std::string> get_args(std::vector<std::string> vector);
  void generate_table(const std::string file_name);
  void generate_graph(const std::string file_name);
  void generate_edges(graph& graph, size_t pc,
                      const std::vector<std::string>& arguments) const;

 public:
  explicit ebpfVerifier(std::string file_name);

  bool isCyclic() const;
  bool isnonReachable() const;

  ~ebpfVerifier();
};

#endif  // __EBPFVERIFIER_H__
