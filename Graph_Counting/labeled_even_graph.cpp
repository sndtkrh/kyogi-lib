// 標識偶グラフの数え上げ
/*
 * 頂点の次数が全て偶数であるようなグラフを偶グラフと呼ぶ
 */
#ifndef EVENGRAPH
#define EVENGRAPH
#include <iostream>
#include <algorithm>
#include <vector>
#include "graph_counting.cpp"
using namespace std;

/*
 * Z_nZ w = labeled_even_graph(グラフの位数n)
 * 位数nの標識偶グラフの個数wを返す．
 */
Z_nZ labeled_even_graph(int n){
  return power( Z_nZ(2), (n-1)*(n-2)/2 );
}
/*
 * vector<Z_nZ> w = labeled_even_graph_with_size(グラフの位数n)
 * 位数nの偶グラフで大きさがsのグラフの個数がw[s]となるwを返す．
 */
vector<Z_nZ> labeled_even_graph_with_size(int n){
  vector<Z_nZ> w( n*(n-1)/2 + 1 , Z_nZ(0) );
  vector<Z_nZ> f = generate_binom( n, Z_nZ(1) );
  for(int p = 0; p <= n; p++){
    vector<Z_nZ> v;
    v = generate_binom( p*(n-p), Z_nZ(-1) )
        * generate_binom( n*(n-1)/2 - p*(n-p) , Z_nZ(1) );
    for(int i = 0; i < w.size(); i++)
      w[i] += f[p] * v[i];
  }  
  for(int i = 0; i < w.size(); i++){
    w[i] /= power(Z_nZ(2), n);
  }
  return w;
}
/* test
int main(){
  int n;
  cin >> n; 
  vector<Z_nZ> w = labeled_even_graph_with_size( n );
  for(int i = 0; i < w.size(); i++){
    cout << w[i].m << " ";
  }
  cout << endl;
}
*/
#endif
