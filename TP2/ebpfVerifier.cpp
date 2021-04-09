#include "ebpfVerifier.h"

#include <fstream>
#include <iostream>
#include <iterator>

#define LINE_DELIM '\n'

ebpfVerifier::ebpfVerifier(std::string file_name) {
  this->file_name = file_name;
  prg_lines = 0;
  cyclic_status = false;
  nonreachable_status = false;
  generate_table(file_name);
  generate_graph(file_name);
}

std::vector<std::string> ebpfVerifier::get_args(
    std::vector<std::string> vector) {
  if (vector.at(0) == "ret") {
    // removes all arguments included the instruction
    vector.clear();
  } else {
    // removes  the instruction
    vector.erase(vector.begin());
  }
  if (vector.size() == 3) {
    // removes the innecesary arguments
    vector.erase(vector.begin());
  }
  return vector;
}

void ebpfVerifier::generate_table(const std::string file_name) {
  std::ifstream file;
  file.open(file_name);

  if (!file.is_open()) {
    return;
  }

  size_t pc = 0;
  while (!file.eof()) {
    std::string line;
    getline(file, line, LINE_DELIM);
    if (!line.empty()) {
      std::string label = parseador.detect_label(line);
      if (!label.empty()) {
        symbol_table[label] = pc;
      }
      pc++;
    }
  }
  file.close();
  prg_lines = pc;
}

void ebpfVerifier::generate_graph(const std::string file_name) {
  std::ifstream file;
  size_t pc = 0;
  graph grafo(prg_lines);

  file.open(file_name);
  if (!file.is_open()) {
    return;
  }

  while (!file.eof()) {
    std::string line;
    getline(file, line, LINE_DELIM);
    if (!line.empty()) {
      std::vector<std::string> arguments;
      arguments = get_args(parseador.iterate(line));
      generate_edges(grafo, pc, arguments);
      pc++;
    }
  }
  file.close();
  cyclic_status = grafo.cyclic();
  nonreachable_status = grafo.nonreachable(0);
}

void ebpfVerifier::generate_edges(graph& graph, size_t pc,
                                  const std::vector<std::string>& args) const {
  for (std::string argument : args) {
    auto it = symbol_table.find(argument);
    if (it != symbol_table.end()) {
      graph.add_edge(pc, it->second);
    } else {
      graph.add_edge(pc, pc + 1);
    }
  }
}

bool ebpfVerifier::isCyclic() const { return cyclic_status; }

bool ebpfVerifier::isnonReachable() const { return nonreachable_status; }

ebpfVerifier::~ebpfVerifier() {}
