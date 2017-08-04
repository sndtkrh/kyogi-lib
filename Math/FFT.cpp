// 高速フーリエ変換
/*
 * $n$次多項式$g(x) = \sum_{i=0}^n a_i x^i, \ h(x) = \sum_{i=0}^n b_i x^i $について，
 * \[ f(x) = (g*h)(x) = \sum_{k=0}^{2n} \sum_{i=0}^{k} a_i b_{k-i} x^k \]
 * を$\mathcal{O}(n \log n)$で求める．
 * 使い方:
 * $g(x)$の係数を \verb|vector<T> g|，
 * $h(x)$の係数を \verb|vector<T> h|
 * としたとき，
 * \verb|vector<T> f = multiply(g, h);|
 * で$f(x)$の係数\verb|f|が求まる．
 * - verified by: http://atc001.contest.atcoder.jp/tasks/fft_c
*/

#ifndef FFT
#define FFT
#include <cstdio>
#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;
typedef complex<double> comp;
const double PI = 3.141592653589793;

/*
 * n次多項式fを高速フーリエ変換する
 * is_inv = false => 順変換
 * is_inv = true  => 逆変換
 * 逆変換したときはmultiplyの中でnで割っている
 */
void fft(vector<comp> &f, int n, bool is_inv){
  if(n == 1) return;
  vector<comp> f0(n/2), f1(n/2);
  for(int i = 0; i < n/2; i++){
    f0[i] = f[ 2 * i ];
    f1[i] = f[ 2 * i + 1 ];
  }
  fft(f0, n / 2, is_inv);
  fft(f1, n / 2, is_inv);
  comp zeta = comp( cos( 2 * PI  / n ), sin( 2 * PI / n ) );
  if(is_inv) zeta = 1.0 / zeta;
  comp pow_zeta = 1.0;
  for(int i = 0; i < n; i++){
    f[i] = f0[ i % ( n / 2 ) ] + pow_zeta * f1[ i % ( n / 2 ) ];
    pow_zeta *= zeta;
  }
}
template<typename T>
vector<T> multiply(vector<T> g, vector<T> h){
  int n = 1;
  int gs = g.size();
  int hs = h.size();
  int fs = gs + hs - 1;
  while( n <= fs + 1 ) n *= 2;
  vector<comp> gg(n), hh(n), ff(n);
  for(int i = 0; i < n; i++){
    if( i < gs ){
      gg[i] = g[i];
    }else{
      gg[i] = 0;
    }
    //gg[i] = (i < gs) ? g[i] : 0;
    hh[i] = (i < hs) ? h[i] : 0;
  }

  fft(gg, n, false);
  fft(hh, n, false);
  for(int i = 0; i < n; i++) ff[i] = gg[i] * hh[i];
  fft(ff, n, true);

  vector<T> f(fs);
  for(int i = 0; i < fs; i++){
    f[i] = (T)round( ff[i].real() / n );
  }
  return f;
}
vector<long long> operator *(const vector<long long> &g,const vector<long long> &h){
  return multiply(g,h);
}
void operator *= (vector<long long> &g, const vector<long long> &h){
  g = g * h;
}

/* test
// verify用
int main(){
  int N;
  vector<long long> A, B;
  A.push_back(0); B.push_back(0);
  cin >> N;
  for(int i = 0; i < N; i++){
    long long t, s;
    cin >> t >> s;
    A.push_back(t);
    B.push_back(s);
  }
  vector<long long> C;
  C = multiply(A, B);
  for(int i = 1; i <= 2*N; i++){
    cout << C[i] << endl;
  }
}
*/
#endif
