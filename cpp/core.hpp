#pragma once
#include <cmath>
#include <limits>
namespace lord_sumi {
class Graph {
public:
 static const int N=16;
 explicit Graph(bool directed=true):directed_(directed),count_(0),fault_(false){clear();}
 bool add_node(){if(fault_||count_==N){fault_=true;return false;}++count_;return true;}
 bool add_edge(int a,int b,double cost){
  if(fault_||a<0||b<0||a>=count_||b>=count_||!std::isfinite(cost)||cost<0){fault_=true;return false;}
  w_[a][b]=cost;if(!directed_)w_[b][a]=cost;return true;
 }
 bool shortest(int start,int end,double& cost,int* path,int capacity,int& length)const{
  length=0;cost=std::numeric_limits<double>::infinity();
  if(fault_||!path||capacity<=0||start<0||end<0||start>=count_||end>=count_)return false;
  double d[N];int prev[N];bool used[N];
  for(int i=0;i<count_;++i){d[i]=std::numeric_limits<double>::infinity();prev[i]=-1;used[i]=false;}
  d[start]=0;
  for(int k=0;k<count_;++k){
   int u=-1;for(int i=0;i<count_;++i)if(!used[i]&&(u<0||d[i]<d[u]))u=i;
   if(u<0||!std::isfinite(d[u]))break;
   used[u]=true;
   for(int v=0;v<count_;++v)if(!used[v]&&std::isfinite(w_[u][v])){
    if(d[u]>std::numeric_limits<double>::max()-w_[u][v])continue;
    double next=d[u]+w_[u][v];if(next<d[v]){d[v]=next;prev[v]=u;}
   }
  }
  if(!std::isfinite(d[end]))return false;
  int reverse[N],n=0;for(int v=end;v>=0&&n<N;v=prev[v]){reverse[n++]=v;if(v==start)break;}
  if(!n||reverse[n-1]!=start||n>capacity)return false;
  for(int i=0;i<n;++i)path[i]=reverse[n-i-1];
  length=n;cost=d[end];return true;
 }
 bool fault()const{return fault_;}
 void reset(){count_=0;fault_=false;clear();}
private:
 void clear(){for(int i=0;i<N;++i)for(int j=0;j<N;++j)w_[i][j]=std::numeric_limits<double>::infinity();}
 bool directed_;int count_;bool fault_;double w_[N][N];
};
}