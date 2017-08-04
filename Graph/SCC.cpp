// 強連結成分分解
/*
 * 2回DFSすることで強連結成分に分解する．
 * 計算量$\mathcal{O}(V+E)$．
 * また，\verb|V == G.scc()|で有向グラフの閉路検出ができる．
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_A
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const char UNUSED = 0;
const char USED = 1;
class SCC{
public:
  int V;
  vector< vector<int> > G;
  vector< vector<int> > Grev;
  vector<int> vs; // 帰りがけ順の並び
  vector<char> used;
  //各頂点が属する強連結成分のトポロジカル順序
  vector<int> topological_ord;
  bool is_scced; // scc が呼ばれたかどうかのフラグ
  SCC(int n) : V(n) {
    G.resize(V);
    Grev.resize(V);
    used.resize(V);
    topological_ord.resize(V);
    is_scced = false;
  }
  void add_edge(int v, int u){
    G[v].push_back(u);
    Grev[u].push_back(v);
  }
  void dfs(int v){
    used[v] = USED;
    for(int i = 0; i < G[v].size(); i++){
      int u = G[v][i];
      if(used[ u ] != USED)
	dfs( u );
    }
    vs.push_back(v);
  }
  void rdfs(int v, int k){
    used[v] = USED;
    topological_ord[v] = k;
    for(int i = 0; i < Grev[v].size(); i++){
      int u = Grev[v][i];
      if( used[u] != USED )
	rdfs(u, k);
    }
  }
  // 強連結成分の個数を返す
  int scc(){
    is_scced = true;
    fill(used.begin(), used.end(), UNUSED);
    vs.clear();
    for(int v = 0; v < V; v++)
      if( used[v] != USED ) dfs(v);
    fill(used.begin(), used.end(), UNUSED);
    int k = 0;
    for(int i = vs.size() - 1; i >= 0; i--){
      int v = vs[i];
      if( used[v] != USED )
	rdfs(v, k++);
    }
    return k;
  }
  // 二つの頂点が同じ強連結成分に属するかどうかを返す
  bool is_same_scc(int v, int u){
    if( ! is_scced ) scc();
    return topological_ord[v] == topological_ord[u];
  }
};
/* test
int main(){
  int V, E;
  cin >> V >> E;
  SCC G(V);
  for(int i = 0; i < E; i++){
    int s, t;
    cin >> s >> t;
    G.add_edge(s, t);
  }
  int Q;
  cin >> Q;
  for(int i = 0; i < Q; i++){
    int u, v;
    cin >> u >> v;
    cout << ( G.is_same_scc(u,v) ? 1 : 0 ) << endl;
  }
  
}
*/
/* test */
// 有向グラフの閉路検出
int main(){
  int V, E;
  cin >> V >> E;
  SCC G(V);
  for(int i = 0; i < E; i++){
    int s, t;
    cin >> s >> t;
    G.add_edge(s, t);
  }
  if( V == G.scc() )
    cout << 0 << endl;
  else
    cout << 1 << endl;
}
/**/
