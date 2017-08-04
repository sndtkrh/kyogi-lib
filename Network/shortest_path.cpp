// 最短経路
/*
 * グラフの最短経路に関するライブラリ．
 * Dijkstra 法：単一始点最短経路を$\mathcal{O}(|E| \log |V|)$で求める．負の閉路があるときは使えない．
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2021
 * Bellman-Ford 法：単一始点最短経路を$\mathcal{O}(|V||E|)$で求める．負閉路がある場合は検出できる．
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B
 * Warshall-Floyd 法：全点対最短経路を$\mathcal{O}(|V|^3)$で求める．
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2200
 */
#ifndef SHORTESTPATH
#define SHORTESTPATH
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

template <typename Cost>
class edge {
public:
  int from;
  int to;
  Cost cost;
  edge(int t, Cost c) : to(t), cost(c) { ; }
  edge(int f, int t, Cost c) : from(f), to(t), cost(c) { ; }
};

template <typename Cost>
class ShortestPath{
public:
  vector< vector<edge<Cost> > > G;
  ShortestPath(){;}
  ShortestPath(int n){ G.resize(n); }
  // 有向辺を追加する add_edge( 辺の始点, 辺の終点, 辺の距離)
  void add_edge(int s, int t,  Cost dist){
    G[s].push_back( edge<Cost>(s, t, dist) );
  }
  // 無向辺を追加する
  void add_bi_edge(int s, int t, Cost dist){
    G[s].push_back( edge<Cost>(s, t, dist) );
    G[t].push_back( edge<Cost>(t, s, dist) );
  }

  // ダイクストラ法 dijkstra( 始点, ゼロ, 無限大)
  // グラフのある頂点sから各頂点への最短経路配列vector<Cost> d を求める
  vector<Cost> dijkstra(int s, const Cost zero, const Cost inf){
    typedef pair<Cost, int> P; // first:最短距離 second:頂点番号
    int V = G.size();
    priority_queue< P, vector<P>, greater<P> > Q;
    vector<Cost> d(V);
    fill(d.begin(), d.end(), inf);
    d[s] = zero;
    Q.push( P( zero, s ) );
    while( !Q.empty() ){
      P p = Q.top(); Q.pop();
      int v = p.second;
      if( d[v] < p.first ) continue;
      for(int i = 0; i < G[v].size(); i++){
	edge<Cost> e = G[v][i];
	if( d[e.to] > d[v] + e.cost ){
	  d[e.to] = d[v] + e.cost;
	  Q.push( P( d[e.to], e.to ) );
	}
      }
    }
    return d;
  }

  // ベルマンフォード法
  // pair(始点から到達可能な負閉路が存在しないかどうか,最短距離のvector) = bellman_ford(始点,ゼロ,無限大)
  // グラフのある頂点sから各頂点への最短経路配列vector<Cost> d を求める
  pair<bool, vector<Cost> > bellman_ford (int s, const Cost zero, const Cost inf){
    vector<edge<Cost> > edgeset;
    vector<Cost> d( G.size() );
    
    for(int i = 0; i < G.size(); i++)
      for(int j = 0; j < G[i].size(); j++)
	edgeset.push_back( G[i][j] );
    
    fill( d.begin(), d.end(), inf );
    d[s] = zero;
    for(int k = 0; ; k++){
      bool update = false;
      for(int i = 0; i < edgeset.size(); i++){
	edge<Cost> e = edgeset[i];
	if ( d[e.from] != inf && d[e.to] > d[e.from] + e.cost ){
	  d[e.to] = d[e.from] + e.cost;
	  update = true;
	}
      }
      if ( !update ) break;
      else if( k == G.size() - 1 ) return make_pair(false, d); //負閉路が存在する
    }
    return make_pair(true, d);
  }
  
  // 全ての負閉路をベルマンフォードを用いて検出する．trueなら負閉路が存在する．
  bool find_negative_loop (const Cost zero){
    vector<edge<Cost> > edgeset;
    vector<Cost> d( G.size() );
    for(int i = 0; i < G.size(); i++)
      for(int j = 0; j < G[i].size(); j++)
	edgeset.push_back( G[i][j] );
    
    fill( d.begin(), d.end(), zero );
  
    for(int i = 0; i < G.size(); i++ ){
      for(int j = 0; j < edgeset.size(); j++){
	edge<Cost> e = edgeset[j];
	if( d[e.to] > d[e.from] + e.cost ){
	  d[e.to] = d[e.from] + e.cost;	  
	  if( i == G.size() - 1 ) return true;
	}
      }
    }
    return false;
  }
  
  // ワーシャル-フロイド法
  // 点間の距離のvector<vector<Cost> > d = warshall_floyd(ゼロ, 無限大)
  vector< vector< Cost> > warshall_floyd(const Cost zero, const Cost inf){
    int v = G.size();
    vector< vector<Cost> > d(v, vector<Cost> ( v, inf ) );
    for(int i = 0; i < v; i++){
      d[i][i] = zero; //自分自身に行くコストはゼロ
      for(int j = 0; j < G[i].size(); j++){
	edge<Cost> e = G[i][j];
	d[ e.from ][ e.to ] = e.cost;
      }
    }
    for(int k = 0; k < v; k++)
      for(int i = 0; i < v; i++)
	for(int j = 0; j < v; j++)
	  if( d[i][k] != inf && d[k][j] != inf ) //負の辺があるときにこのif文が必要（辺のコストが正のみのときはオーバーフローしなければなくてもよい）
	    d[i][j] = min( d[i][j], d[i][k] + d[k][j] );
    return d;
  }
};

/* test
// verify用(GRL_1_C) 以下は古いバージョンのコードである！注意
const long long INF = 1e17;
int main(){
  int V, E;
  cin >> V >> E;
  vector< vector<edge<long long> > > G(V);
  for(int i = 0; i < E; i++){
    int s, t;
    long long d;
    cin >> s >> t >> d;
    add_edge(G, s, t, d);
  }

  if( find_negative_loop( G, 0LL ) ){
    cout << "NEGATIVE CYCLE" << endl;
  }else{
    vector<vector<long long> > d = warshall_floyd(G, 0LL, INF);
    for(int i = 0; i < V; i++){
      for(int j = 0; j < V; j++){
	if( d[i][j] == INF ) cout << "INF";
	else cout << d[i][j];
	if( j == V-1 ) cout << endl;
	else cout << " ";
      }
    }
  }
}
*/
/* test
// verify用 GRL_1_A
const long long INF = 1e17;
int main(){
  int V, E, r;
  cin >> V >> E >> r;
  ShortestPath<long long> sp(V);
  for(int i = 0; i < E; i++){
    int s, t;
    long long d;
    cin >> s >> t >> d;
    sp.add_edge(s, t, d);
  }
  vector<long long> d = sp.dijkstra(r, 0LL, INF);
  for(int i = 0; i < V; i++){
    if(d[i] == INF)
      cout << "INF" << endl;
    else
      cout << d[i] << endl;
  }
}
*/
/* test
// verify用 GRL_1_B 以下は古いバージョンのコードである！注意！
const long long INF = 1e17;
int main(){
  int V, E, r;
  cin >> V >> E >> r;
  vector< vector<edge<long long> > > G(V);
  for(int i = 0; i < E; i++){
    int s, t;
    long long d;
    cin >> s >> t >> d;
    add_edge(G, s, t, d);
  }
  pair<bool, vector<long long> > p = bellman_ford(G, r, 0LL, INF);
  if( p.first == false ){
    cout << "NEGATIVE CYCLE" << endl;
  }else{
    vector<long long> d = p.second;
    for(int i = 0; i < V; i++){
      if(d[i] == INF)
	cout << "INF" << endl;
      else
	cout << d[i] << endl;
    }
  }
}
*/
#endif
