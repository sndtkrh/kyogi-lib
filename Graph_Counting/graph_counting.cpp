// グラフ数え上げライブラリに共通なもの

#ifndef GRAPHCOUNTING
#define GRAPHCOUNTING
#include <algorithm>
#include <vector>
#include "../Math/mod.cpp"
#include "../Math/mod_poly.cpp"
#include "../Math/combination.cpp"
#include "../Math/power.cpp"

// (nC0 * a^0, nC1 * a^1, ... , nCn * a^n)となっているvector<Z_nZ>を返す
// power( 1+x, n )よりこっちの方がよい（誤差とかオーバーフローの関係）
vector<Z_nZ> generate_binom(int n, Z_nZ a){
  vector<Z_nZ> ret(n+1);
  Z_nZ f(1);
  Z_nZ aa = Z_nZ(1);
  ret[0] = f * aa;
  for(int i = 1; i <= n; i++){
    f *= Z_nZ( n-i+1 ) / Z_nZ( i );
    aa *= a;
    ret[i] = f * aa;
  }
  return ret;
}
// 冪乗
vector<Z_nZ> power(vector<Z_nZ> a, long long n ){
  vector<Z_nZ> e(1, Z_nZ(1) );
  return power(a, n, e);
}
/*
vector<Z_nZ> power(vector<long long> a, long long n){
  vector<long long> e(1, 1);
  vector<long long> t = power(a, n, e);
  vector<Z_nZ> ret(t.size());
  for(int i = 0; i < t.size(); i++)
    ret[i] = Z_nZ(t[i]);
  return ret;
}
*/
Z_nZ power(Z_nZ a, long long n){
  return power(a, n, Z_nZ(1) );
}
#endif
