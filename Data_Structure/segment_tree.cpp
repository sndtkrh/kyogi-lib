// Segment 木
/*
 * 通常のセグメント木．
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
 */
#ifndef SEGTREE
#define SEGTREE
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
// RMQ 用
// SegmentTree<long long, RMQ> rmq(n, RMQ(INF) );
template <typename T = long long>
class RMQ{
public:
  T dflt;
  RMQ(){;}
  RMQ(T inf) : dflt(inf) {;}
  T merge  (T a, T b){ return min(a, b); }
  T update (T &node, T v){ node = v; }
};

template <typename T, typename Updater>
class SegmentTree{
  int N;
  vector<T> tree;
  Updater updater;
public:
  SegmentTree(){;}
  SegmentTree(int n, Updater f) : updater(f) {
    N = 1;
    while(N < n) N *= 2;
    tree.resize( 2 * N - 1, updater.dflt);
  }
  SegmentTree(int n, Updater f, vector<T> &vs) : updater(f) { // vsで初期化
    N = 1;
    while(N < n) N *= 2;
    tree.resize( 2 * N - 1, updater.dflt );
    int i;
    for(i = 0; i < vs.size(); i++)
      tree[i + N - 1] = vs[i];
    for(int k = N - 2; k >= 0; k--){
      tree[k] = updater.merge(tree[2 * k + 1], tree[2 * k + 2]);
    }
  }
  void update(int k, T a){
    k += N - 1;
    updater.update(tree[k], a);
    while(k > 0){
      k = (k-1) / 2;
      tree[k] = updater.merge(tree[2 * k + 1], tree[2 * k + 2]);
    }
  }
  T query(int a, int b, int k, int l, int r){
    if( r <= a || b <= l ) return updater.dflt;
    if( a <= l && r <= b ) return tree[k];
    return updater.merge( query(a, b, 2 * k + 1, l, (r + l) / 2),
			  query(a, b, 2 * k + 2, (r + l) / 2, r) );
  }
  T query(int a, int b){ return query(a, b, 0, 0, N); }
};
/* test
int main(){
  int n, q;
  cin >> n >> q;
  SegmentTree<long long, RMQ> st(n, RMQ( 2147483647ll ) );
  for(int i = 0; i < q; i++){
    int c, x, y;
    cin >> c >> x >> y;
    if ( c == 1 ){
      cout << st.query(x,y + 1) << endl;
    }else{
      st.update(x,y);
    }
  }
}
*/
#endif
