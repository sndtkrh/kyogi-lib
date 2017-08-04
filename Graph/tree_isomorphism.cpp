// 根付き非順序木の同型判定
/*
 * ハッシュを用いた同型判定を行う
 */
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Tree{
  vector< vector<int> > ch; // ch[v] : 頂点vの子
  int root;
  vector<long long> hash;
  long long M, A, B;
  // pa[v] : 頂点vの親
  Tree(int r, vector<int> pa) : root(r) {
    M = 1e9 + 7;
    A = 1145141919ll;
    B = 99999989ll;
    ch.resize( pa.size() );
    for(int i = 0; i < pa.size(); i++){
      if( i != root ) ch[ pa[i] ].push_back(i);
    }
    //for(int v = 0; v < ch.size(); v++){ cout << "v=" << v << endl; for(int i = 0; i < ch[v].size(); i++) cout << "  u=" << ch[v][i] << endl; }
    hash.resize( ch.size() );
    calc_hash( root );
  }
  Tree(int r, vector<int> pa, long long M, long long A, long long B) : root(r), M(M),A(A),B(B) {
    //cout << "M=" << M << " A=" << A << " B=" << B << endl;
    ch.resize( pa.size() );
    for(int i = 0; i < pa.size(); i++){
      if( i != root ) ch[ pa[i] ].push_back(i);
    }
    hash.resize( ch.size() );
    calc_hash( root );
  }

  long long calc_hash( int v ){
    vector<long long> hs;
    hash[v] = B;
    for(int i = 0; i < ch[v].size(); i++)
      hs.push_back( calc_hash( ch[v][i] ) );
    sort( hs.begin(), hs.end() );
    long long t = A;
    for(int i = 0; i < hs.size(); i++){
      hash[v] += hs[i] * t;
      hash[v] %= M;
      t *= A;
      t %= M;
    }
    return hash[v];
  }
  bool operator == (Tree &T){
    return (hash[root] == T.hash[T.root] && ch.size() == T.ch.size() );
  }
};

/* test */
int H[2], W[2];
char P[2][128][128];
bool used[2][128][128];
int pa[50000];
bool init(){
  for(int k = 0; k < 2; k++) for(int i = 0; i < 128; i++) for(int j = 0; j < 128; j++){ P[k][i][j] = '.'; used[k][i][j] = false; }
  for(int k = 0; k < 2; k++){
    scanf("%d%d",H+k,W+k);
    if( H[0] == 0 ) return false;
    char c;
    for(int i = 1; i <= H[k]; i++){
      scanf("%c", &c);
      for(int j = 1; j <= W[k]; j++){
	scanf("%c", &P[k][i][j]);
      }
    }
  }
  return true;
}
const int dh[2][8] = {{1,-1,0,0,0,0,0,0},{-1,-1,-1,0,0,1,1,1}};
const int dw[2][8] = {{0,0,1,-1,0,0,0,0},{-1,0,1,-1,1,-1,0,1}};
const int l[2] = {4,8};
int id;
bool notin(int k, int h, int w){
  return !(0 <= h && h <= H[k]+1 && 0 <= w && w <= W[k]+1);
}
void construct(const int k, int d, int h, int w){
  //cout << "k=" << k << " d=" << d << " h=" << h << " w=" << w << endl;
  int myid = id; id++;
  int D = d%2;
  queue< pair<int,int> > Q;
  vector< pair<int,int> > next;
  Q.push( pair<int,int>( h,w ) );
  while( !Q.empty() ){
    h = Q.front().first;
    w = Q.front().second; Q.pop();
    if( used[k][h][w] ) continue;
    used[k][h][w] = true;
    for(int t = 0; t < l[D]; t++){
      int nh = h + dh[D][t];
      int nw = w + dw[D][t];
      if( notin(k,nh,nw) || used[k][nh][nw] )
	continue;
      if( P[k][nh][nw] != P[k][h][w] ){
	next.push_back( make_pair(nh,nw) );
	continue;
      }
      Q.push( make_pair( nh, nw ) );
    }
  }
  for(int i = 0; i < next.size(); i++){
    h = next[i].first;
    w = next[i].second;
    if( used[k][h][w] ) continue;
    pa[id] = myid;
    construct(k,d+1,h,w);
  }
}
int main(){
  while( init() ){
    vector<int> pav;
    id = 0;
    construct(0,0,0,0);
    pav.resize(id);
    for(int i = 0; i < id; i++) pav[i] = pa[i];
    vector<int> pau;
    id = 0;
    construct(1,0,0,0);
    pau.resize(id);
    for(int i = 0; i < id; i++) pau[i] = pa[i];

    long long t = 114514ll;
    long long s = 19;
    long long x = 99999989ll;
    bool f = true;
    for(int i = 0; i < 100; i++){
      long long M = x;
      x = (t * x + s) % (long long)(1e9 + 7);
      long long A = x;
      x = (t * x + s) % (long long)(1e9 + 7);
      long long B = x;
      x = (t * x + s) % (long long)(1e9 + 7);
      Tree T( 0, pav, M, A, B );
      Tree S( 0, pau, M, A, B );
      if( !(T == S) ){
	cout << "no" << endl;
	f = false;
	break;
      }
    }
    if(f) cout << "yes" << endl;
  }
}
/**/
