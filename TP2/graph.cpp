#include "graph.h"

#include <iostream>

#define SUCCED 0
#define ERROR -1

graph::graph(size_t N) {
  n_nodes = N;
  adj = new std::list<size_t>[N];
}

static void push_back_unique(std::list<size_t>& list, size_t value) {
  bool inList = false;

  for (size_t list_value : list) {
    inList = (list_value == value) ? true : inList;
  }
  if (!inList) {
    list.push_back(value);
  }
}

void graph::add_edge(size_t start, size_t end) {
  if (end < n_nodes) {
    // Add unique edge from start to end
    push_back_unique(adj[start], end);
  }

  return;
}

static bool haselement(std::vector<size_t>& vector, size_t element) {
  bool inVector = false;
  size_t pos = 0;
  while (!inVector and pos < vector.size()) {
    inVector = (vector.at(pos) == element);
    pos++;
  }
  return inVector;
}

bool graph::dfs(int head, std::vector<bool>& visited,
                std::vector<size_t>& recStack) const {
  if (visited.at(head) == false) {
    // Mark the node as visited and add to te recStack
    visited.at(head) = true;
    recStack.push_back(head);

    bool status = false;
    for (size_t node : adj[head]) {
      bool result = dfs(node, visited, recStack);
      status = (status == false) ? result : status;
    }
    recStack.pop_back();
    return status;
  }
  // See if is in the reStack
  return haselement(recStack, head);
}

bool graph::cyclic() const {
  // Call the recursive function to detect cycle in different
  // DFS trees
  for (size_t i = 0; i < n_nodes; i++) {
    // Mark all the nodes as not visited and not part of recursion
    // stack
    std::vector<bool> visited;
    visited.assign(n_nodes, false);
    std::vector<size_t> recStack;

    if (dfs(i, visited, recStack)) {
      return true;
    }
  }
  return false;
}

bool graph::nonreachable(size_t head) const {
  // Mark all the vertices as not visited and not part of recursion
  // stack
  std::vector<bool> visited;
  for (size_t i = 0; i < n_nodes; i++) {
    visited.push_back(false);
  }
  if (visited.empty()) {
    return false;
  }

  std::vector<size_t> recStack;

  // Call the recursive function to detect non-reachables nodes just in
  // the head tree
  dfs(head, visited, recStack);

  // Check if all the nodes ar reachables, if is not return true
  std::vector<bool>::iterator it;
  for (it = visited.begin(); it != visited.end(); it++) {
    if (*it == false) {
      return true;
    }
  }
  return false;
}

void graph::print() const {
  // print adjacency list representation of graph
  for (size_t i = 0; i < n_nodes; i++) {
    // print given vertex
    std::cout << i << " --";

    // print all its neighboring vertices
    for (auto v : adj[i]) {
      std::cout << " ->" << v << " ";
    }
    std::cout << std::endl;
  }
}

graph::~graph() { delete[] adj; }
