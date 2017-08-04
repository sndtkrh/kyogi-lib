// 最小費用流
/*
 * 最小費用流ライブラリ
 * - verified by: http://poj.org/problem?id=2135
 */

#ifndef MINCOSTFLOW
#define NINCOSTFLOW
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef int Cap; //辺の容量
const char USED = 1;
const char UNUSED = 0;

template <typename Cost>
class edge {
public:
  int to, rev;
  Cap cap;
  Cost cost;
  edge(int t, Cap ca, Cost co, int r) : to(t), cap(ca), cost(co), rev(r) { ; }
};

template <typename Cost>
class MinCostFlow{
public:
  vector< vector<edge<Cost> > > G;
  MinCostFlow(){;}
  MinCostFlow(int n){ G.resize(n); }
  void add_edge(int from, int to, Cap cap, Cost cost){
    G[from].push_back( edge<Cost>(to, cap,  cost, G[ to ].size()     ) );
    G[ to ].push_back( edge<Cost>(from, 0, -cost, G[from].size() - 1 ) );
  }
  // sからtへの流量fの最小費用流
  // 流せない場合は-1
  Cost mincostflow(int s, int t, Cap f, Cost inf){
    typedef pair<Cost, int> Pair;
    vector<Cost> h(G.size(), 0);
    vector<int> prevv(G.size(), 0);
    vector<int> preve(G.size(), 0);
    Cost res = 0;
    while( f > 0 ){
      priority_queue< Pair, vector<Pair>, greater<Pair> > que;
      vector<Cost> dist(G.size(), inf);
      dist[s] = 0;
      que.push( Pair(0,s) );
      // find shortest path
      while( !que.empty() ){
	Pair p = que.top(); que.pop();
	int v = p.second;
	if( dist[v] < p.first ) continue;
	for(int i = 0; i < G[v].size(); i++){
	  edge<Cost> &e = G[v][i];
	  if( e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to] ){
	    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
	    prevv[e.to] = v;
	    preve[e.to] = i;
	    que.push( Pair(dist[e.to], e.to) );
	  }
	}
      }
      if( dist[t] == inf ) return -1; // cannot flow!
      for(int v = 0; v < G.size(); v++) h[v] += dist[v];
      //flow s-t-shortest path
      int d = f;
      for(int v = t; v != s; v = prevv[v]){
	d = min(d, G[ prevv[v] ][ preve[v] ].cap);
      }
      f -= d;
      res += d * h[t];
      for(int v = t; v != s; v = prevv[v]){
	edge<Cost> &e = G[ prevv[v] ][ preve[v] ];
	e.cap -= d;
	G[v][e.rev].cap += d;
      }
    }
    return res;
  }
};
/* test
#include <cstdio>
const int INF = 1e9;
int main(){
  int N, M;
  scanf("%d %d", &N, &M);
  MinCostFlow<int> mcf(N);
  for(int i = 0; i < M; i++){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    mcf.add_edge(a - 1, b - 1, 1, c);
    mcf.add_edge(b - 1, a - 1, 1, c);
  }
  printf("%d\n", mcf.mincostflow(0,N-1,2,INF) );
}
*/
#endif
