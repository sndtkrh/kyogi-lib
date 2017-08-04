// 最小全域木
/*
 * クラスカル法
 * - Union Find 木を使う方法
 * - $\mathcal{O}( |E| \log |V| )$
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A
 */
#include <algorithm>
#include <queue>
#include <vector>
#include "../Data_Structure/Union_Find.cpp"
using namespace std;

template <typename Cost>
class edge{
public:
  int u,v;;
  Cost cost;
  edge(int u, int v, Cost c) : u(u), v(v), cost(c) { ; }
  bool operator< (const edge &e) const {
    return cost < e.cost;
  }
};

template <typename Cost>
class SpanningTree{
public:
  int V;
  vector< edge<Cost> > edges;
  SpanningTree(int n) : V(n) {; }
  void add_edge(int v, int u, Cost c){
    edges.push_back( edge<Cost>(v,u,c) );
  }
  Cost kruskal(){
    sort( edges.begin(), edges.end() );
    UFT uft(V);
    Cost ret = 0;
    for(int i = 0; i < edges.size(); i++){
      edge<Cost> &e = edges[i];
      if( !uft.is_same(e.u, e.v) ){
	uft.unite(e.u, e.v);
	ret += e.cost;
      }
    }
    return ret;
  }
};
/* test
int main(){
  int V, E;
  cin >> V >> E;
  SpanningTree<int> st(V);
  for(int i = 0; i < E; i++){
    int s, t, w;
    cin >> s >> t >> w;
    st.add_edge(s,t,w);
  }
  cout << st.kruskal() << endl;
}
*/
