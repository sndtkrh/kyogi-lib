// Aho-Corasick 法
/*
 * 複数パターン検索を行う．
 * パターン文字列の長さの和&L&，検索文字列の長さ$M$のとき
 * PMA構築に$\mathcal{O}(L)$，検索に$\mathcal{O}(L+N)$かかる．
 * - verified by : UVa 10679
 */
#include <bits/stdc++.h>
using namespace std;

struct PMAnode{
  PMAnode * next[256];
  PMAnode * fail;
  vector<int> accept;
  PMAnode(){ fill( next, next+256, nullptr ); }
};
// Aho Corasick
struct PMA{
  PMAnode root;
  int n_pat; // number of patterns
  PMA(vector<string> &ps){
    n_pat = ps.size();
    // construct Trie tree
    for( int k = 0; k < ps.size(); k++ ){
      string p = ps[k];
      PMAnode * t = &root;
      for(int i = 0; i < p.size(); i++){
	if( t->next[ p[i] ] == nullptr ) t->next[ p[i] ] = new PMAnode;
	t = t->next[ p[i] ];
      }
      t->accept.push_back( k );
    }
    // construct failure link
    queue< PMAnode * > Q;
    for( char c = ' '; c <= '~'; c++ ){
      if( root.next[c] != nullptr ){
	root.next[c]->fail = &root;
	Q.push( root.next[c] ); // add node which is adjacent to root
      }else{
	root.next[c] = &root;
      }
    }
    while( ! Q.empty() ){
      PMAnode *t = Q.front(); Q.pop();
      for( char c = ' '; c <= '~'; c++ ){
	if( t->next[ c ] != nullptr ){
	  Q.push( t->next[ c ] );
	  PMAnode * r = t->fail;
	  while( r->next[c] == nullptr ) r = r->fail;
	  t->next[c]->fail = r->next[c];
	  vector<int> &tac = t->next[c]->accept;
	  vector<int> &rac = r->next[c]->accept;
	  tac.insert( tac.end(), rac.begin(), rac.end() );
	  sort( tac.begin(), tac.end() );
	  unique( tac.begin(), tac.end() );
	}
      }
    }
  }
  // strを最後まで見たときの最終的なPMAnodeを返す
  PMAnode * match( string str ){
    PMAnode * t = &root;
    for( char c : str ){
      while( t->next[c] == nullptr ) t = t->fail;
      t = t->next[c];
    }
    return t;
  }
  // strでマッチしたパターンの種類と回数を返す
  // res[i] := パターン文字列ps[i]のstrにおける出現回数
  vector< int > match_n( string str ){
    vector<int> res( n_pat, 0 );
    PMAnode * t = &root;
    for( char c : str ){
      while( t->next[c] == nullptr ) t = t->fail;
      t = t->next[c];
      for(int i = 0; i < t->accept.size(); i++){
	res[ t->accept[i] ]++;
      }
    }
    return res;
  }
};

/* test
int main(){
  int T;
  cin >> T;
  for(int t = 0; t < T; t++){
    int q;
    string str;
    cin >> str;
    cin >> q;
    vector<string> ps(q);
    for(int i = 0; i < q; i++) cin >> ps[i];
    PMA pma(ps);
    vector<int> r = pma.match( str );
    for(int i = 0; i < r.size(); i++){
      cout << ((r[i]>0)?'y':'n') << endl;
    }
  }
}
*/
