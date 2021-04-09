#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <list>
#include <stack>
#include <vector>

struct node {
  size_t value;
  node* next;
};

struct edge {
  size_t start, end;
};

class graph {
 private:
  size_t n_nodes;
  std::list<size_t>* adj;

  bool dfs(int head, std::vector<bool>& visited,
           std::vector<size_t>& recStack) const;

 public:
  explicit graph(size_t N);

  void add_edge(size_t start, size_t end);
  bool cyclic() const;
  bool nonreachable(size_t head) const;
  void print() const;

  ~graph();
};

#endif  //__GRAPH_H__
