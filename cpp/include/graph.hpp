#pragma once
#include <cmath>
#include <cstddef>
#include <limits>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>
namespace graphpath {
class Graph {
 std::vector<std::vector<std::pair<std::size_t,double>>> adj; bool directed;
 public:
 explicit Graph(std::size_t n,bool is_directed=true):adj(n),directed(is_directed){if(n>10000)throw std::invalid_argument("too many nodes");}
 void add_edge(std::size_t u,std::size_t v,double w){
  if(u>=adj.size()||v>=adj.size()||!std::isfinite(w)||w<0)throw std::invalid_argument("invalid edge");
  adj[u].push_back({v,w});if(!directed)adj[v].push_back({u,w});
 }
 std::vector<double> distances(std::size_t source) const{
  if(source>=adj.size())throw std::out_of_range("source");
  const double inf=std::numeric_limits<double>::infinity();
  std::vector<double> dist(adj.size(),inf);
  using Item=std::pair<double,std::size_t>;
  std::priority_queue<Item,std::vector<Item>,std::greater<Item>> q;
  dist[source]=0;q.push({0,source});
  while(!q.empty()){
   const Item item=q.top();q.pop();if(item.first!=dist[item.second])continue;
   for(const auto& e:adj[item.second]){
    const double next=item.first+e.second;
    if(!std::isfinite(next))throw std::overflow_error("path overflow");
    if(next<dist[e.first]){dist[e.first]=next;q.push({next,e.first});}
   }
  }
  return dist;
 }
 bool reachable(std::size_t source,std::size_t target) const{
  if(target>=adj.size())return false;
  return std::isfinite(distances(source)[target]);
 }
};
}
