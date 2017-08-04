// 繰り返し二乗法ライブラリ
/*
 * 繰り返し二乗法を用いて累乗を高速に計算する．
 * 計算量は$\mathcal{O}(f \log n)$である．ここで$f$は$a \cdot a$にかかる時間．
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B
 */

#ifndef LIBPOWER
#define LIBPOWER
#include <iostream>
#include <algorithm>
using namespace std;

// power(乗ずる数, 乗ずる回数, 乗法単位元)
template <typename T>
T power(const T &a, long long n, const T &e){
  T ret = e;
  T beki = a;
  for(long long i = 1LL; i <= n; i <<= 1){
    if( (n & i) > 0 )
      ret *= beki;
    beki = beki * beki;
  }
  return ret;
}
/* test
int main(){
  long long t;
  long long n;
  cin >> t;
  cin >> n;
  cout << power(t, n, 1LL) << endl;
}
*/
#endif
