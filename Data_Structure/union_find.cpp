// Union-Find 木
/*
 * 互いに素な集合族を扱うためのデータ構造．
 * 各操作のならし計算量は$\mathcal{O}(\alpha(n))$である．
 * ここで$\alpha(n)$はアッカーマン関数の逆関数である．
 * - verified by: http://codeforces.com/contest/438/problem/B
 */

#ifndef UNIONFIND
#define UNIONFIND
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class UFT {
  vector<int> parent;
  vector<int> rank; //木の高さ
  vector<int> size; //その頂点が属している集合の大きさ（必要な場合だけ）
public:
  UFT(int n){
    parent = vector<int>(n);
    rank = vector<int>(n,0);
    size = vector<int>(n,1);
    for(int i = 0; i < n; i++)
      parent[i] = i;
  }
  int find_root(int x){
    if ( parent[x] == x ) return x;
    return parent[x] = find_root( parent[x] );
  }
  void unite(int x, int y){
    int u = find_root(x);
    int v = find_root(y);
    if ( u == v ) return;
    if ( rank[u] < rank[v] ){
      parent[u] = v;
      size[v] += size[u];
    }else{
      parent[v] = u;
      size[u] += size[v];
      if ( rank[u] == rank[v] ) rank[x]++;
    }
  }
  bool is_same ( int x, int y ){
    return find_root(x) == find_root(y);
  }
  int size_of ( int x ){
    return size[ find_root(x) ];
  }
};
#endif
