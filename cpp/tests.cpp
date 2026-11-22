#include "core.hpp"
#include <cassert>
#include <cmath>
int main(){
 using lord_sumi::Graph;Graph g(false);
 assert(g.add_node()&&g.add_node()&&g.add_node());
 assert(g.add_edge(0,1,2)&&g.add_edge(1,2,3)&&g.add_edge(0,2,10));
 int path[16],length=0;double cost=0;
 assert(g.shortest(2,0,cost,path,16,length)&&cost==5&&length==3&&path[0]==2&&path[2]==0);
 assert(!g.shortest(0,2,cost,path,1,length));
 assert(!g.add_edge(0,2,-1)&&g.fault());
 assert(!g.shortest(0,2,cost,path,16,length));
 g.reset();assert(!g.fault());
 Graph d;assert(d.add_node()&&d.add_node()&&d.add_edge(0,1,1));
 assert(!d.shortest(1,0,cost,path,16,length));
 assert(!d.add_edge(0,1,NAN));
}