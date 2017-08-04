#include <bits/stdc++.h>
#include "Smith_normal_form.cpp"
using namespace std;

// 単体複体のホモロジーを計算する
typedef int Point;
typedef vector<Point> Simplex;
typedef vector<vector<Simplex> > Complex; // 単体を次元ごとに分けて持っておく

// 足りない単体を追加して単体複体を作る
Complex get_complex(Complex c){
  int dim = c.size() - 1;
  vector< set<Simplex> > S(dim+1);
  // 今ある単体を全部入れておく
  for(int d = 0; d <= dim; d++){
    for(int i = 0; i < c[d].size(); i++){
      sort( c[d][i].begin(), c[d][i].end() ); // ソートしておく
      S[d].insert( c[d][i] );
    }
  }
  for(int d = dim-1; d >= 0; d--){
    // 各d+1単体の primary face を全部追加する
    for( Simplex s : S[d+1] ){
      Simplex t(d+1); // 追加するd単体
      for(int i = 1; i < s.size(); i++){
	t[i-1] = s[i];
      }
      S[d].insert( t );
      for(int i = 0; i < t.size(); i++){
	t[i] = s[i];
	S[d].insert( t );
      }
    }
  }

  Complex ret(dim+1);
  for(int d = 0; d <= dim; d++)
    for(Simplex s : S[d])
      ret[d].push_back( s );
  return ret;
}

void show(Complex c){
  int dim = c.size() - 1;
  for(int d = 0; d <= dim; d++){
    printf("dim=%d, #=%d\n", d, c[d].size()  );
    for(int i = 0; i < c[d].size(); i++){
      printf("|");
      for(int j = 0; j < c[d][i].size(); j++){
	printf("%d", c[d][i][j] );
	if( j == d )
	  printf("|, ");
	else
	  printf(",");
      }
    }
    puts("");
  }
}
void pm(Matrix &M){
  // print matrix
  for(int i = 0; i < M.size(); i++){
    for(int j = 0; j < M[i].size(); j++){
      printf("%3d", M[i][j]);
    }
    puts("");
  }
}

class SimplicialHomology{
public:
  Complex cpx;
  vector<int> C; // 単体で生成される自由加群
  int dim;
  vector< vector<long long> > boundary_map; // 境界写像（Smith標準形）
  vector< map< Simplex, int> > index; // d単体のインデックス
  vector< int > Hrank; // d次ホモロジー群のランク
  vector< vector<int> > Htor; // d次ホモロジー群の捻れ
  SimplicialHomology( Complex c ) : cpx(c) {
    dim = cpx.size() - 1;
    index.resize( dim + 1 );
    for(int d = 0; d <= dim; d++){
      C.push_back( cpx[d].size() );
      for(int i = 0; i < cpx[d].size(); i++){
	index[d][ cpx[d][i] ] = i;
      }
    }
    boundary_map.resize( dim+2 );
    boundary_map[0] = {}; // boundary_map[0] : C_0 -> 0 は零写像
    boundary_map[dim+1] = {}; // boundary_map[dim+1] : 0 -> C_{dim} は零写像
    for(int d = 1; d <= dim; d++){
      // boundary_map[d] : C_d -> C_{d-1} を計算する
      Matrix M( C[d-1], vector<long long>( C[d], 0 ) ); // 境界準同型の表現行列
      printf("M=(%d * %d)\n", M.size(), M[0].size() );
      for(Simplex s : cpx[d]){
	int j = index[d][s];
	Simplex t;
	for(int k = 1; k < s.size(); k++){
	  t.push_back( s[k] );
	}
	int i = index[d-1][t];
	M[i][j] = 1;
	int sgn = -1;
	for(int k = 0; k < t.size(); k++){
	  t[k] = s[k];
	  i = index[d-1][t];
	  M[i][j] = sgn;
	  sgn *= -1;
	}
      }
      pm(M);
      boundary_map[d] = compute_snf(M); // Smith標準形を計算
      printf("Smith normal form (size=%d) : ", boundary_map[d].size() );
      for(int a : boundary_map[d]){
	printf("%d ", a);
      }
      puts("\n");
    }
    // ホモロジー群のランクと捻れを求める
    Hrank.resize(dim+1);
    Htor.resize(dim+1);
    for(int d = 0; d <= dim; d++){
      Hrank[d] = C[d] - boundary_map[d].size() - boundary_map[d+1].size();
      for(int a : boundary_map[d+1]){
	if( a != 1 ){
	  Htor[d].push_back( a );
	}
      }
      printf("H_%d = Z^{%d} ", d, Hrank[d]);
      for(int tor : Htor[d] ){
	printf("(+) Z/%dZ ", tor );
      }
      puts("");
    }
  }
};


int main(){
  Complex T2 = // 2-dim Torus
    {
      {}, // 0-simplices
      {}, // 1-simplices
      {   // 2-simplices
	{0,1,4}, {0,1,6}, {0,2,3}, {0,2,8}, {0,3,4}, {0,6,8},
	{1,2,5}, {1,2,7}, {1,4,5}, {1,6,7},
	{2,3,5}, {2,7,8},
	{3,4,7}, {3,5,6}, {3,6,7},
	{4,7,8}, {4,5,8},
	{5,6,8}
      }
    };
  Complex K2 = // 2-dim Klein bottle
    {
      {}, {},
      {
	{0,1,4}, {0,2,6}, {0,2,3}, {0,1,8}, {0,3,4}, {0,6,8},
	{1,2,5}, {1,2,7}, {1,4,5}, {2,6,7},
	{2,3,5}, {1,7,8},
	{3,4,7}, {3,5,6}, {3,6,7},
	{4,7,8}, {4,5,8},
	{5,6,8}
      }
    };
  Complex P2 = // 2-dim Projective space
    {
      {}, {},
      {
	{0,1,4}, {0,1,8}, {0,3,4}, {0,3,8},
	{1,2,5}, {1,2,7}, {1,4,5}, {1,7,8},
	{2,5,6}, {2,6,7},
	{3,4,7}, {3,5,6}, {3,6,7}, {3,5,8},
	{4,5,8}, {4,7,8}
      }
    };
  Complex S2 = { {}, {}, { {0,1,2}, {0,1,3}, {0,2,3}, {1,2,3} } }; // 2-dim Sphere
  
  P2 = get_complex( P2 );
  show(P2);
  SimplicialHomology H( P2 );
}
