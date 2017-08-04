// 最大公約数・最小公倍数，拡張ユークリッドの互除法
/*
 * 拡張ユークリッドの互除法では$ax + by = \mathrm{gcd}(a,b)$ となる$x,y$を求める．
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E
 */
#ifndef GCDLCM
#define GCDLCM
#include <algorithm>
using namespace std;
typedef pair<long long, long long> P;
// 最大公倍数
long long gcd(long long a, long long b){
  return __gcd(a,b); // gccのときのみ使える
}
// 最小公倍数
long long lcm(long long a, long long b){
  return a / __gcd(a,b) * b;
}
// long long x = 0, y = 0;
// extgcd(a, b, x, y);
long long extgcd(long long a, long long b, long long &x, long long &y){
  long long g = a; x = 1; y = 0;
  if(b != 0){
    g = extgcd( b, a % b, y, x );
    y -= (a / b) * x;
  }
  return g;
}
#endif

