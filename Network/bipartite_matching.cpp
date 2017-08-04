// 二部マッチング
/*
 * 二部グラフ$G$の最大マッチングの辺数を$\nu$，
 * 最大独立集合の点数を$\alpha$，最少点カバーの点数を$\tau$とする．
 * フローを流して$\alpha$を求める．
 * 一般のグラフで$\alpha + \tau = |G|$と$\nu < \tau$が成り立つ．
 * さらに，二部グラフにおいては$\nu = \tau$が成り立つ．
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A
 */
#ifndef BIPMAT
#define BIPMAT
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const char USED = 1;
const char UNUSED = 0;

class BipGraph {
  vector< char > used;
public:
  vector< vector<int> > G;
  vector< int > match; // マッチングのペア
  BipGraph(int v){
    G.resize(v);
    used.resize(v, UNUSED);
    match.resize(v, -1);
  }
  void add_edge(int u, int v){
    G[u].push_back(v);
    G[v].push_back(u);
  }
  bool dfs(int v){
    used[v] = USED;
    for( int i = 0; i < G[v].size(); i++){
      int u = G[v][i], w = match[u];
      if( w < 0 || used[w] == UNUSED && dfs(w) ){
	match[v] = u;
	match[u] = v;
	return true;
      }
    }
    return false;
  }
  int bipartite_matching(){
    int res = 0;
    fill(match.begin(), match.end(), -1);
    for(int v = 0; v < G.size(); v++){
      if( match[v] < 0 ){
	fill(used.begin(), used.end(), UNUSED);
	if( dfs(v) ) res++;
      }
    }
    return res;
  }
  int min_covering(){
    return bipartite_matching();
  }
  int max_independent_set(){
    return G.size() - min_covering();
  }
};
/* test
int main(){
  int X, Y, E;
  cin >> X >> Y >> E;
  BipGraph bg(X + Y);
  for(int i = 0; i < E; i++){
    int x, y;
    cin >> x >> y;
    bg.add_edge(x,X+y);
  }
  cout << bg.bipartite_matching() << endl;
}
*/
#endif
