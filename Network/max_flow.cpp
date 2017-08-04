// 最大流
/*
 * 最大流
 * - 計算量 $\mathcal{O}( |E| \mathrm{maxflow} )$ だが最悪ケースはまずない．
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A
 */
#ifndef MAXFLOW
#define MAXFLOW
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef int Cap; //辺の容量
const Cap INF = 1e9;
const char USED = 1;
const char UNUSED = 0;

class edge {
public:
  int to, rev;
  Cap cap;
  edge(int t, Cap c, int r) : to(t), cap(c), rev(r) { ; }
};

class MaxFlow{
public:
  vector< vector<edge> > G;
  MaxFlow(){;}
  MaxFlow(int n){ G.resize(n); }
  
  void add_edge( int from, int to, Cap cap){
    G[from].push_back( edge(to, cap, G[ to ].size()     ) );
    G[ to ].push_back( edge(from, 0, G[from].size() - 1 ) );
  }
  Cap dfs(int v, int t, Cap f, vector<char> &used){
    if( v == t ) return f;
    used[v] = USED;
    for(int i = 0; i < G[v].size(); i++){
      edge &e = G[v][i];
      if( used[e.to] == UNUSED && e.cap > 0 ){
	Cap d = dfs( e.to, t, min(f, e.cap), used );
	if( d > 0 ) {
	  e.cap -= d;
	  G[e.to][e.rev].cap += d;
	  return d;
	}
      }
    }
    return 0;
  }

  // Cap f = mf.maxflow(s,t) でsからtへの最大流を求める
  Cap maxflow(int s, int t){
    Cap flow = 0;
    while(true){
      vector<char> used( G.size(), UNUSED );
      Cap f = dfs( s, t, INF, used );
      if ( f == 0 ) return flow;
      flow += f;
    }
    return 0;
  }
};
/* test
int main(){
  int V, E;
  cin >> V >> E;
  MaxFlow mf(V);
  vector< vector<edge> > G( V );
  for(int i = 0; i < E; i++){
    int v, u;
    Cap c;
    cin >> v >> u >> c;
    mf.add_edge(v, u, c );
  }
  cout << mf.maxflow(0, V - 1 ) << endl;
}
*/
#endif
