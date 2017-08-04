// 全域木の数え上げ
/*
 * グラフ$G=(E,V)$の隣接行列$M$が与えられたとき，
 * そのラプラシアン行列$L$を求める．
 * 行列木定理より$L$の任意の余因子は
 * $G$の全域木の個数に等しい．
 * \[ L[u,v] = \deg u (\mbox{if } u = v), \ -M[u,v] (\mbox{if } u \ne v) \]
 * - verified by:
 * - http://code-festival-2014-china-open.contest.atcoder.jp/tasks/code_festival_china_g
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include "../Math/mod.cpp"
#include "../Math/matrix.cpp"
using namespace std;

class Graph{
public:
  int V;
  vector< vector<char> > G;
  vector<int> deg;
  Graph(int V) : V(V) {
    G.resize( V, vector<char>( V, 0 ) );
    deg.resize( V, 0 );
  }
  void add_edge(int v, int u){
    G[v][u] = 1;
    G[u][v] = 1;
    deg[v]++;
    deg[u]++;
  }
  Matrix<Z_nZ> laplacian_matrix(){
    Matrix<Z_nZ> L(V);
    for(int i = 0; i < V; i++){
      for(int j = 0; j < V; j++){
	if( i == j )
	  L[i][j] = Z_nZ( deg[i] );
	else
	  L[i][j] = Z_nZ( -G[i][j] );
      }
    }
    return L;
  }
  Z_nZ count_spanning_tree(){
    Matrix<Z_nZ> L = laplacian_matrix();
    L.m--; L.n--;
    return det(L);
  }
};

int main(){
  int V, E;
  cin >> V >> E;
  Graph G(V);
  for(int i = 0; i < E; i++){
    int u, v;
    cin >> u >> v;
    G.add_edge(u, v);
  }
  cout << G.count_spanning_tree().m << endl;
}
