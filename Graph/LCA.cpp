// 最小共通祖先
/*
 * 最小共通祖先(LCA)を求める．
 * 前処理に$\mathcal{O}(V)$．
 * LCAを求める各クエリに対して$\mathcal{O}(\log V)$
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C
 */
#include <vector>
#include <algorithm>
#include "../Data_Structure/segment_tree.cpp"
using namespace std;
typedef vector< vector<int> > Graph;
typedef pair<int,int> P;
//値とindexのペアを返すようにしたRMQ
class RMQi{
public:
  P dflt;
  RMQi(){ dflt = P(1e9,-1); }
  P merge(P l, P r){ return min(l,r); }
  P update(P &node, P v){ node = v; }
};
class LCA{
public:
  int V, root;
  bool inited; // 初期化されたかどうかのフラグ
  Graph G;
  vector<int> vs; // vs[i] := dfsでi番目に訪れた頂点の番号
  vector<int> depth; // depth[i] := 頂点vs[i]の深さ
  vector<int> id; // 各頂点が最初にvsに現れる時のインデックス
  SegmentTree<P, RMQi > rmq;
  LCA(int V, int r) : V(V), root(r) {
    inited = false;
    G.resize(V);
    vs.resize(2 * V + 1);
    depth.resize(2 * V + 1);
    id.resize(V);
  }
  void add_edge(int v, int u){
    G[v].push_back(u);
    G[u].push_back(v);
  }
  void lca_init(){
    inited = true;
    int k = 0;
    dfs(root, -1, 0, k);
    vector<P> d(2*V+1);
    for(int i = 0; i < 2 * V + 1; i++)
      d[i] = P(depth[i], i);
    rmq = SegmentTree<P, RMQi > ( 2 * V + 1, RMQi(), d );
  }
  void dfs(int v, int p, int d, int &k){
    id[v] = k;
    vs[k] = v;
    depth[k++] = d;
    for(int i = 0; i < G[v].size(); i++){
      int u = G[v][i];
      if( u != p ){
	dfs(u, v, d + 1, k);
	vs[k] = v;
	depth[k++] = d;
      }
    }
  }
  int lca(int v, int u){
    if( ! inited ) lca_init();
    int minid = min(id[v],id[u]);
    int maxid = max(id[v],id[u]);
    P p = rmq.query(minid, maxid + 1);
    return vs[ rmq.query( minid , maxid + 1 ).second ];
  }
};
/* test
int main(){
  int V;
  cin >> V;
  LCA Tree(V, 0);
  for(int v = 0; v < V; v++){
    int k;
    cin >> k;
    for(int i = 0; i < k; i++){
      int c;
      cin >> c;
      Tree.add_edge(v,c);
    }
  }
  int Q;
  cin >> Q;
  for(int i = 0; i < Q; i++){
    int u, v;
    cin >> u >> v;
    cout << Tree.lca(u,v) << endl;
  }
}
*/
