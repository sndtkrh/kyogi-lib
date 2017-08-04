// Lowlink
/*
 * グラフの関節点や橋を求めるときに使う．
 * 計算量$\mathcal{O}(V+E)$
 * - 橋，関節点でverifiedされた．
 */
#include <vector>
#include <algorithm>
using namespace std;
const char UNUSED = 0;
const char USED   = 1;
typedef vector< vector<int> > Graph;

class Lowlink{
public:
  int V;
  Graph G;
  int root; // DFS木の根 parent[root] = -1;
  vector<int> parent; //DFS木の各ノードの親
  vector<int> order;
  vector<int> lowest;
  vector<char> used;
  int ord;
  Lowlink(int n) : V(n){
    G.resize(V);
    order.resize(V);
    parent.resize(V);
    lowest.resize(V);
    used.resize(V);
  }
  void add_edge(int v, int u){
    G[v].push_back(u);
    G[u].push_back(v);
  }
  // lowest[v] を返す
  int dfs(int v, int p){
    used[v] = USED;
    order[v] = ord++;
    int low = order[v];
    for(int i = 0; i < G[v].size(); i++){
      int u = G[v][i];
      if( u == p ) continue;
      if( !used[u] ){
	parent[u] = v;
	low = min( low, dfs(u, v) );
      }else{
	// backedge 後退辺
	low = min( low, order[u] );
      }
    }
    return lowest[v] = low;
  }
  void lowlink(){
    ord = 0;
    root = 0; // dfsの根
    fill(used.begin(), used.end(), UNUSED);
    parent[root] = -1;
    dfs(root, -1);
  }
};
