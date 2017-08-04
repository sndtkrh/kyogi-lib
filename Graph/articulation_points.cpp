// 関節点列挙
/*
 * グラフの関節点を全て求める．
 * グラフ$G$の関節点（または切断点）とは
 * $v \in V(G)$で$G-v$の連結成分が$G$の連結成分よりも
 * 真に大きくなるものである．
 * 計算量$\mathcal{O}(V+E)$
 * - verified by: AOJ GRL 3 A
 * - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A&lang=jp
 */
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include "lowlink.cpp"
using namespace std;
vector<int> articulation_points(Lowlink &L){
  L.lowlink();
  bool is_ap[L.V];
  fill(is_ap, is_ap + L.V, false);
  // root
  int ch = 0;
  for(int v = 0; v < L.V; v++)
    if( L.parent[v] == L.root )
      ch++;
  if( ch >= 2 ) is_ap[L.root] = true;
  // none root
  for(int v = 0; v < L.V; v++){
    int p = L.parent[v];
    if( p != -1 && p != L.root && L.order[ p ] <= L.lowest[v] )
      is_ap[p] = true;
  }

  vector<int> ap;
  for(int i = 0; i < L.V; i++){
    if( is_ap[i] ) ap.push_back(i);
  }
  return ap;
}

/* test */
int main(){
  int V, E;
  cin >> V >> E;
  Lowlink L(V);
  for(int i = 0; i < E; i++){
    int s, t;
    cin >> s >> t;
    L.add_edge(s,t);
  }
  vector<int> s = articulation_points(L);
  for(int i = 0; i < s.size(); i++){
    cout << s[i] << endl;
  }
}
/**/
