// 橋列挙
/*
 * グラフ$G$の橋を全て求める．
 * $e \in E(G)$が橋であるとは，
 * $G-e$の連結成分が$G$の連結成分よりも真に大きくなることを言う．
 * 計算量$\mathcal{O}(V+E)$
 * （ただし以下の実装では$\mathcal{O}(V+E \log E)$になっている．）
 * （$\mathcal{O}(V+E)$にしたければ橋だけのGraphを返すようにすれば簡単にできる．）
 * - verified by: AOJ GRL 3 B
 * - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B
 */
#include "lowlink.cpp"
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
using namespace std;

typedef pair<int,int> edge;
set<edge> bridge(Lowlink &L){
  L.lowlink();
  set<edge> bs;
  for(int v = 0; v < L.V; v++){
    for(int i = 0; i < L.G[v].size(); i++){
      int u = L.G[v][i];
      if( L.order[v] < L.lowest[u] || L.order[u] < L.lowest[v] )
	bs.insert( edge( min(v,u), max(v,u) ) );
    }
  }
  return bs;
}
/* test
int main(){
  int V, E;
  cin >> V >> E;
  Lowlink L(V);
  for(int i = 0; i < E; i++){
    int s, t;
    cin >> s >> t;
    L.add_edge(s,t);
  }
  set<edge> bs = bridge(L);
  for(set<edge>::iterator it = bs.begin(); it != bs.end(); it++){
    cout << (it->first) << " " << (it->second) << endl;
  }
}
*/
