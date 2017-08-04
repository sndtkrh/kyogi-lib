// 標識連結グラフの数え上げ
/*
 * $C(x) = \sum_{n=1}^{\infty} C_n \frac{x^n}{n!}$を連結な標識グラフに対する指数型母関数とする．
 * ここで $C_n$は位数（頂点数）$n$の連結な標識グラフの個数である．
 *
 * 標識グラフの指数型母関数を$G(x)$とすると$ 1+G(x) = \exp ( C(x) )$ が成り立つ（Riddelの方程式）
 *
 * 次の漸化式が成り立つ：
 * \[ C_n = 2^{\binom{n}{2}} - \frac{1}{n} \sum_{k=1}^{n-1} 2^{ \binom{n-k}{2} } C_k \]
 */

#ifndef LIBCONNECTEDGRAPH
#define LIBCONNECTEDGRAPH
#include <iostream>
#include <vector>
#include <algorithm>
#include "graph_counting.cpp"
#include "labeled_graph.cpp"
using namespace std;

/*
 * 連結な標識グラフの個数をMODで割った余りのvectorを返す
 * vector<Z_nZ> C = labeled_connected_graph(グラフの位数)
 * C[i] := 位数iの連結な標識グラフの数をMODで割った余り
 */
vector<Z_nZ> labeled_connected_graph(int n){
  vector<Z_nZ> C(n+1);
  C[0] = 0;
  C[1] = Z_nZ(1);
  for(int i = 2; i <= n; i++){
    C[i] = power( Z_nZ(2), i*(i-1)/2 );
    Z_nZ t(0);
    for(int k = 1; k < i; k++){
      // t += k * iCk * 2^{n-k C 2} * C_k
      t += Z_nZ(k) * binomial(i, k) * power( Z_nZ(2), (i-k)*(i-k-1)/2 ) * C[k];
    }
    t /= Z_nZ(i);
    C[i] -= t;
  }
  return C;
}

/*
 * vector< vector<Z_nZ> > C = labeled_connected_graph_with_size(グラフの位数)
 * 位数n，大きさmの標識グラフの個数をMODで割ったあまりが
 * C[n][m]となるような vector< vector<Z_nZ> > C を返す．
 * vecotr<Z_nZ> D = labeled_connected_graph(n) とすると，
 * 定義より， \sum_{ j=0 }^{ G[i].size() } C[i][j] = D[i] がすべてのiに対して成り立つ．
 */
vector< vector<Z_nZ> > labeled_connected_graph_with_size(int n){
  vector< vector<Z_nZ> > C(n+1);
  vector< vector<Z_nZ> > G = labeled_graph_with_size(n);
  C[0].push_back( Z_nZ(0) );
  C[1].push_back( Z_nZ(1) );
  for(int i = 2; i <= n; i++){
    C[i] = G[i];
    vector<Z_nZ> t( i*(i-1)/2 , Z_nZ(0) );
    for(int k = 1; k < i; k++){
      vector<Z_nZ> s = C[k] * G[i-k]; // 多項式の掛け算
      Z_nZ f = Z_nZ(k) * binomial( i, k );
      for(int j = 0; j < s.size(); j++){
	t[j] += f * s[j];
      }
    }
    for(int j = 0; j < t.size(); j++){
      C[i][j] -= Z_nZ(i).inv() * t[j];
    }
  }
  return C;
}
/* test
int main(){
  int n = 10;

  vector<Z_nZ> C = labeled_connected_graph(n);
  for(int i = 0; i <= n; i++){
    cout << C[i].m << endl;
  }
  cout << endl;

  vector< vector< Z_nZ > > D = labeled_connected_graph_with_size(n);
  for(int i = 0; i <= n; i++){
    for(int j = 0; j < D[i].size(); j++){
      cout << D[i][j].m << " ";
    }
    cout << endl;
  }
}
*/
#endif
