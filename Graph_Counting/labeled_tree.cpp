// 標識木の数え上げ
/*
 * Cayley の定理からわかる．
 * 母関数を用いても導ける．
 */

#ifndef LABELEDTREE
#define LABELEDTREE
#include "graph_counting.cpp"
/*
 * Z_nZ t = labeled_tree(グラフの位数n)
 * t := 位数nの標識木の個数
 * 定義から t == labeled_connected_graph(n)[n-1] となっている．
 */
Z_nZ labeled_tree(int n){
  return power(Z_nZ(n), n-2);
}
/* test
int main(){
  int n;
  cin >> n;
  cout << labeled_tree(n).m << endl;
}
*/
#endif
