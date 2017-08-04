// 標識ブロックの数え上げ
/*
 * 標識連結グラフ$G$の点$v$について，$G-{v}$が非連結になるとき，$v$は$G$の切断点であるという．
 * 切断点を持たない標識連結グラフを標識ブロックという．
 */
#ifndef LABELEDBLOCK
#define LABELEDBLOCK
#include <iostream>
#include <vector>
#include <algorithm>
#include "graph_counting.cpp"
#include "labeled_connected_graph.cpp"
using namespace std;

// H[k][m] = ( x C'(x) )^k の x^m の係数
// H[M-1][M] の値まで作る
vector< vector<Z_nZ> > generate_H(int M){
  vector<Z_nZ> C = labeled_connected_graph(M);
  for(int i = 0; i < C.size(); i++){
    C[i] /= factorial( i - 1 );
  }
  vector<Z_nZ> v = C;
  vector< vector<Z_nZ> > H( M , vector<Z_nZ>( M + 1 ) );
  for(int k = 1; k <= M - 1; k++){
    for(int m = 1; m <= M; m++){
      H[k][m] = v[m];
    }
    v *= C;
    v.resize( M+1 );
  }
  return H;
}

// vector<Z_nZ> B = labeled_block(グラフの位数m)
// 位数mの標識ブロックの個数がB[m]であるようなBを返す
// ただし B[1] = 0 と定義している （B[1]=1のほうが自然に思えるがこの数え上げに置いてはこのように定める）
vector<Z_nZ> labeled_block(int m){
  vector< vector<Z_nZ> > H = generate_H(m);
  vector<Z_nZ> B(m+1);
  B[0] = B[1] = Z_nZ(0);
  for(int i = 2; i <= m; i++){
    B[i] = factorial( i - 1 ) * H[1][i];
    Z_nZ t(0);
    for(int l = 1; l <= i - 2; l++){
      t += Z_nZ( l ) * B[ l + 1 ] / factorial( l + 1 ) * H[l+1][i];
    }
    B[i] -= factorial(i-2) * Z_nZ(i) * t;
  }
  return B;
}

/* test
int main(){
  int M = 100;
  vector< vector< Z_nZ > > H = generate_H( M );
  cout << "H" << endl;
  for(int m = 1; m <= M; m++){
    for(int k = 1; k < M; k++){
      cout << H[k][m].m << " ";
    }
    cout << endl;
  }
  cout << endl;
  cout << "B" << endl;
  vector< Z_nZ > B = labeled_block( M );
  for(int i = 0; i < B.size(); i++){
    cout << B[i].m << " ";
  }
  cout << endl;
}
*/

#endif
