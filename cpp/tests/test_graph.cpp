#include "graph.hpp"
#include <cassert>
#include <cmath>
#include <limits>
#include <stdexcept>
int main(){
 graphpath::Graph g(4);g.add_edge(0,1,4);g.add_edge(1,2,2);g.add_edge(0,2,10);
 auto d=g.distances(0);assert(d[2]==6);assert(!std::isfinite(d[3]));
 assert(g.reachable(0,2));assert(!g.reachable(2,0));
 graphpath::Graph u(2,false);u.add_edge(0,1,1.5);assert(u.distances(1)[0]==1.5);
 for(double w:{-1.0,std::numeric_limits<double>::infinity(),std::numeric_limits<double>::quiet_NaN()}){
 bool rejected=false;try{g.add_edge(0,1,w);}catch(const std::invalid_argument&){rejected=true;}assert(rejected);
 }
 bool rejected=false;try{g.add_edge(9,1,2);}catch(const std::invalid_argument&){rejected=true;}assert(rejected);
}
