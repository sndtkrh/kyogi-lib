// 標識グラフの数え上げ
/*
 * グラフの頂点数を位数，辺数を大きさとも呼ぶことにする．
 * 位数$n$の標識グラフとは，グラフの頂点と$\{1,\dots,n\}$との間に全単射があり，頂点同士が区別されているようなグラフである．
 */

#ifndef LIBGRAPHWITHLABEL
#define LIBGRAPHWITHLABEL
#include <iostream>
#include <algorithm>
#include <vector>
#include "graph_counting.cpp"
using namespace std;

/*
 * vector<Z_nZ> G = labeled_graph(グラフの位数)
 * 位数iの標識グラフの個数（のMODで割った余り）がG[i]となっているような vecotr<Z_nZ> G を返す．
 */
vector<Z_nZ> labeled_graph(int n){
  vector<Z_nZ> g(n+1);
  for(int i = 0; i <= n; i++){
    g[i] = power( Z_nZ(2), n*(n-1)/2 );
  }
  return g;
}

/*
 * vector< vector<Z_nZ> > G = labeled_graph_with_size(グラフの位数)
 * 位数i，大きさjのグラフの個数がG[i][j]となっているような vector< vector<Z_nZ> > G を返す．
 * vector<Z_nZ> H = labeled_graph(n) とすると
 * 定義から \sum_{ j=0 }^{ G[i].size() } G[i][[j] = H[i] がすべてのiに対して成り立つ．
 */
vector< vector<Z_nZ> > labeled_graph_with_size(int n){
  vector< vector<Z_nZ> > g(n+1);
  for(int i = 0; i <= n; i++){
    g[i] = generate_binom( i*(i-1)/2, Z_nZ(1) );
  }
  return g;
}
/* test
int main(){
  vector< vector<Z_nZ> > G = labeled_graph_with_size(4);
  for(int i = 0; i < G.size(); i++){
    for(int j = 0; j < G[i].size(); j++){
      cout << G[i][j].m << " ";
    }
    cout << endl;
  }
}
*/
#endif
