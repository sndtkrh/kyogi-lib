// 汎用遅延評価segment木
/*
 * 遅延評価して区間に対する処理も効率的に出来るようにしたsegment木．
 * - (StarrySky木) verified by: http://abc014.contest.atcoder.jp/tasks/abc014_3
 * - ただし上の問題はStarrySky木を使わなくてもimos法だけで解ける．
 * - veridied by: http://yukicoder.me/problems/625
 */
#ifndef LSEGTREE
#define LSEGTREE
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
// 使い方:
// typedef long long ll;
// LazySegmentTree<ll, ll, StarrySkyUpdater> sst(N,StarrySkyUpdater());

// 区間に一様に足す・区間の最大値を求める ことができる
class StarrySkyUpdater{
public:
  long long dflt;
  long long lazy_dflt;
  StarrySkyUpdater(): dflt(0), lazy_dflt(0) {;}

  // それまでの実際の値に，遅延評価して更新するとき
  void lazy_eval(long long &tree, long long lazy, int l, int r){
    tree += lazy;
  }
  // それまでの遅延している値を新しい遅延している値で更新するとき
  void lazy(long long &pre_lazy, long long lazy){
    pre_lazy += lazy;
  }
  // queryやupdateで右と左の値を使って更新するとき
  long long merge(long long ltree, long long rtree){
    return max(ltree, rtree);
  }
};

// 区間に一様に足す・区間の和を求める ことができる
class AddSumUpdater{
public:
  long long dflt;
  long long lazy_dflt;
  AddSumUpdater(): dflt(0), lazy_dflt(0) {;}

  void lazy_eval(long long &tree, long long lazy, int l, int r){
    tree += lazy * (r - l);
  }
  void lazy(long long &pre_lazy, long long lazy){
    pre_lazy += lazy;
  }
  long long merge(long long ltree, long long rtree){
    return ltree + rtree;
  }
};

// 区間を特定の値に変更・区間の和を求める ことができる
class UpdateSumUpdater{
public:
  long long dflt;
  long long lazy_dflt;
  UpdateSumUpdater() : dflt(0), lazy_dflt(0) {;}

  void lazy_eval(long long &tree, long long lazy, int l, int r){
    tree = lazy * (r - l);
  }
  void lazy(long long &pre_lazy, long long lazy){
    pre_lazy = lazy;
  }
  long long merge(long long ltree, long long rtree){
    return ltree + rtree;
  }
};

template <typename T, typename Tlazy, typename Updater>
class LazySegmentTree{
  int N; // 葉の数
  vector<  T  > tree; // 値
  vector<Tlazy> lazy; // 遅延評価用
  Updater updater; // 値を更新するときに使う
public:
  LazySegmentTree(){;}
  LazySegmentTree(int n, Updater f) : updater(f) {
    N = 1;
    while(N < n) N *= 2;
    tree.resize( 2 * N - 1, updater.dflt);
    lazy.resize( 2 * N - 1, updater.lazy_dflt);
  }
  // ノードkを遅延評価（kに対応する区間が[l,r)）
  inline void lazy_eval_node(int k, int l, int r){
    updater.lazy_eval(tree[k], lazy[k], l, r);
    if ( k < N - 1 ){ // 末端のノードではないとき
      updater.lazy( lazy[2 * k + 1], lazy[k] );
      updater.lazy( lazy[2 * k + 2], lazy[k] );
    }
    lazy[k] = updater.lazy_dflt;
  }
  inline void update_node(int k){
    tree[k] = updater.merge( tree[ 2 * k + 1 ], tree[ 2 * k + 2 ] );
  }
  // 区間[a,b)をvで更新
  void update(int a, int b, Tlazy v, int k, int l, int r){
    lazy_eval_node(k, l, r);
    if( b <= l || r <= a ) return; // [a,b)と[l,r)に共通部分がない
    if( a <= l && r <= b ){ // ノードkに対応する区間が[a,b)に含まれている
      updater.lazy( lazy[k], v);
      lazy_eval_node(k, l, r);
      return;
    }
    update(a, b, v, 2 * k + 1, l, (r + l) / 2);
    update(a, b, v, 2 * k + 2, (r + l) / 2, r);
    update_node(k);
  }
  void update(int a, int b, Tlazy v){ update(a, b, v, 0, 0, N); }

  T query(int a, int b, int k, int l, int r){
    lazy_eval_node(k, l, r);
    if( b <= l || r <= a) return updater.dflt;
    if( a <= l && r <= b) return tree[k];
    T lv = query(a,b, 2*k+1, l, (l+r)/2 );
    T rv = query(a,b, 2*k+2, (l+r)/2, r );
    update_node(k);
    return updater.merge(lv, rv);
  }
  T query(int a, int b){ return query(a, b, 0, 0, N); }

  // 木を表示する
  void print(){
    int p = 1;
    for(int i = 0; i < 2 * N - 1 ; i++){
      if(i+1 >= p){
	p *= 2;
	cerr << endl;
      }
      cerr << "[" << tree[i] << "," << lazy[i] << "] ";
    }
    cerr << endl;
  }
};
/* test
int main(){
  LazySegmentTree<long long, long long, StarrySkyUpdater>
    sst(1000001, StarrySkyUpdater() );
  int n;
  cin >> n;
  for(int i = 0; i < n; i++){
    int a, b;
    cin >> a >> b;
    sst.update(a,b+1,1);
  }
  cout << sst.query(0,1000001) << endl;
}
*/
#endif
