// 行列
/*
 * 行列ライブラリ
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2397
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1327
 * 行列式は全域木の数え上げでverifyされた
 */
#ifndef MATRIX
#define MATRIX
#include <iostream>
#include <algorithm>
#include <vector>
#include "mod.cpp"
#include "power.cpp"
template <typename T>
class Matrix{
public:
  int m, n;
  vector<vector<T> > M;
  Matrix(){;}
  Matrix(int m) : m(m), n(m){
    M.resize(m, vector<T>(n) );
  }
  Matrix(int m, int n) : m(m), n(n){
    M.resize(m, vector<T>(n) );
  }
  Matrix(int m, int n, T a) : m(m), n(n) {
    M.resize(m, vector<T>(n, a) );
  }
  Matrix(int m, int n, T a, T b) : m(m), n(n) {
    M.resize(m, vector<T>(n, a) );
    set_diag(b);
  }
  void set_all(T a){
    for(int i = 0; i < m; i++)
      for(int j = 0; j < n; j++)
	M[i][j] = a;
  }
  void set_diag(T a){
    for(int i = 0; i < min(n, m); i++)
      M[i][i] = a;
  }

  vector<T> & operator[] (int i){ return M[i]; }
  Matrix<T> operator + (Matrix<T> & A){
    if(m != A.m || n != A.n) return size_err();
    Matrix<T> ret( m, n );
    for(int i = 0; i < m; i++)
      for(int j = 0; j < n; j++)
	ret[i][j] = M[i][j] + A[i][j];
    return ret;
  }
  Matrix<T> operator - (Matrix<T> & A){
    if(m != A.m || n != A.n) return size_err();
    Matrix<T> ret( m, n );
    for(int i = 0; i < m; i++)
      for(int j = 0; j < n; j++)
	ret[i][j] = M[i][j] - A[i][j];
    return ret;
  }
  Matrix<T> operator * (Matrix<T> & A){
    if( n != A.m ) return size_err();
    Matrix<T> ret(m, A.n);
    for(int i = 0; i < m; i++){
      for(int j = 0; j < A.n; j++){
	ret[i][j] = M[i][0] * A[0][j];
	for(int k = 1; k < n; k++)
	  ret[i][j] += M[i][k] * A[k][j];
      }
    }
    return ret;
  }
  void operator *= (Matrix<T> & A){
    if( n != A.m ){ size_err(); return; }
    Matrix<T> ret = this->operator*(A);
    M = ret.M;
    m = ret.m;
    n = ret.n;
  }
  // 転置行列
  Matrix<T> t(){
    Matrix ret(P(M[0].size(), M.size()));
    for(int i = 0; i < M.size(); i++)
      for(int j = 0; j < M[0].size(); j++)
	ret[j][i] = M[i][j];
    return ret;
  }
  // サイズがおかしくて計算できないときこれが呼ばれる
  Matrix<T> size_err(){
    cerr << "size_error" << endl;
    return Matrix<T>(0,0);
  }
  // 行列表示
  void print(){
    for(int i = 0; i < M.size(); i++){
      for(int j = 0; j < M[i].size(); j++)
	cout << M[i][j] << " ";
      cout << endl;
    }
    cout << endl;
  }
};
// 行列累乗
template <typename T>
Matrix<T> power(Matrix<T> A, long long n){
  Matrix<T> I(A.m, A.n, 0, 1);
  return power(A, n, I);
}
// 行列式（有理数）
#include "./fraction.cpp"
Frac det(Matrix<Frac> A){
  Frac zero(0);
  if(A.m != A.n){ A.size_err(); return zero; }
  int n = A.n;
  // 上三角にする
  for(int i = 0; i < n; i++){
    if( A[i][i] == zero ){
      //対角線に0が来ないようにする
      int k;
      for(k = i + 1; k < n; k++)
	if( A[k][i] != zero ) break;
      if( k == n ) return zero;
      for(int j = i; j < n; j++)
	A[i][j] += A[k][j];
    }
    for(int j = i + 1; j < n; j++){
      Frac f = A[j][i] / A[i][i];
      for(int k = 0; k < n; k++){
	A[j][k] -= f * A[i][k];
      }
    }
  }
  Frac ret(1);
  for(int i = 0; i < n; i++)
    ret *= A[i][i];
  return ret;
}
// 行列式（整数，Z/nZで値を求める（グラフの数え上げなどに使う？））
#include "mod.cpp"
Z_nZ det(Matrix<Z_nZ> A){
  if(A.m != A.n){ A.size_err(); return Z_nZ(0); }
  int n = A.n;
  // 上三角にする
  for(int i = 0; i < n; i++){
    if( A[i][i].m == 0 ){
      //対角線に0が来ないようにする
      int k;
      for(k = i + 1; k < n; k++)
	if( A[k][i].m != 0 ) break;
      if( k == n ) return Z_nZ(0);
      for(int j = i; j < n; j++)
	A[i][j] += A[k][j];
    }
    for(int j = i + 1; j < n; j++){
      Z_nZ f = A[j][i] / A[i][i];
      for(int k = 0; k < n; k++){
	A[j][k] -= f * A[i][k];
      }
    }
  }
  Z_nZ ret(1);
  for(int i = 0; i < n; i++)
    ret *= A[i][i];
  return ret;
}
// 行列式（double）
const double EPS = 1e-10;
bool eq(double a, double b){
  return (a - EPS <= b && b <= a + EPS);
}
double det(Matrix<double> A){
  if(A.m != A.n){ A.size_err(); return 0; }
  int n = A.n;
  // 上三角にする
  for(int i = 0; i < n; i++){
    if( eq(A[i][i], 0) ){
      //対角線に0が来ないようにする
      int k;
      for(k = i + 1; k < n; k++)
	if( ! eq( A[k][i], 0 ) ) break;
      if( k == n ) return 0;
      for(int j = i; j < n; j++)
	A[i][j] += A[k][j];
    }
    for(int j = i + 1; j < n; j++){
      double f = A[j][i] / A[i][i];
      for(int k = 0; k < n; k++){
	A[j][k] -= f * A[i][k];
      }
    }
  }
  double ret = 1;
  for(int i = 0; i < n; i++)
    ret *= A[i][i];
  return ret;
}
Matrix<Frac> inverse(Matrix<Frac> A){
  if( A.m != A.n ){ return A.size_err(); }
  int n = A.m;
  Matrix<Frac> inv( n, n, Frac(0), Frac(1) );
  for(int i = 0; i < n; i++){
    if( A[i][i] == 0 ){
      int k;
      for(k = i + 1; k < n; k++){
	if( A[k][i] != 0 ) break;
      }
      if( k == n ){
	cerr << "no inverse" << endl;
	return Matrix<Frac>(0,0);
      }
      for(int j = i; j < n; j++){
	A[i][j] += A[k][j];
	inv[i][j] += inv[k][j];
      }
    }
    for(int j = 0; j < n; j++){
      if(i == j) continue;
      Frac f = A[j][i] / A[i][i];
      for(int k = 0; k < n; k++){
	A[j][k] -= f * A[i][k];
	inv[j][k] -= f * inv[i][k];
      }
    }
    Frac f = A[i][i];
    for(int k = 0; k < n; k++){
      A[i][k] /= f;
      inv[i][k] /= f;
    }
  }
  return inv;
}
/* test
int main(){
  int N;
  cin >> N;
  Matrix<Frac> A(N,N);
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      long long a; cin >> a;
      A[i][j] = Frac(a);
    }
  }
  A.print();
  Matrix<Frac> B = inverse(A);
  B.print();
  (A*B).print();
}
*/
#endif
