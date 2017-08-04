#include <bits/stdc++.h>
using namespace std;

/* 木上のダブリング
 * 頂点数$N$の木の各頂点に可換モノイドの元が割り当てられているときに
 * あるパス上の演算結果を$\mathcal{O}(\log N)$で返すような
 * データ構造を得る
 * データ構造を構築するための計算量は$\mathcal{O}(N \log N)$
 */

const int LOGN = 20;
template <typename Monoid>
class DoublingOnTree{
  vector<int> parent[LOGN];
  vector< vector<int> > children;
  vector<Monoid> val[LOGN];
  vector<int> depth;
  Monoid e; // モノイドの単位元
  // 木の頂点iの親がp[i] (iが根の場合はp[i] == -1）
  DoublingOnTree(vector<int> p, vector<Monoid> v, Monoid e) : e(e){
    parent[0] = p;
    val[0] = v;
    for(int i = 1; i < LOGN; i++){
      parent[i].resize( p.size() );
      val[i].resize( p.size() );
    }
    // ダブリング
    for(int k = 0; k < LOGN-1; k++){
      for(int i = 0; i < N; i++){
	if( parent[k][i] == -1 ){
	  parent[k+1][i] = -1;
	  val[k+1][i] = val[k][i];
	}else{
	  parent[k+1][i] = parent[k][ parent[k][i] ];
	  val[k+1][i] = val[k][i] + val[k][ parent[k][i] ]; // モノイドの演算
	}
      }
    }
    // 根を検出
    // 子のリストを生成
    int root;
    for(int i = 0; i < p.size(); i++){
      if( p[i] == -1 ){
	root = p;
      }else{
	ch[ p[i] ].push_back( i );
      }
    }
    // 頂点の深さを計算
    depth[root] = 0;
    queue<int> Q;
    Q.push( root );
    while( ! Q.empty() ){
      int u = Q.front(); Q.pop();
      for(int i = 0; i < children[u].size(); i++){
	int v = children[u][i];
	depth[v] = u + 1;
	Q.push( v );
      }
    }
  }
  // 頂点vからその先祖である頂点aまでの演算の結果を返す
  Monoid v2a(int v, int a){
    if( v == a ) return val[0][v]; // 同じ頂点
    int dv = depth[v];
    int da = depth[a];
    Monoid t = e;
    for(int i = 0; i < LOGN; i++){
      if( 
    }
    return t + v2a( u, a ); // モノイドの演算
  }
};
