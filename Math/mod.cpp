// $\mathbb{Z}/n\mathbb{Z}$
/*
 * $p$が素数のとき$\mathbb{F}_p = \mathbb{Z}/p\mathbb{Z}$は体になり，
 * $a \in \mathbb{F}_p \ {0}$の逆元は$a^{p-2}$である（フェルマーの小定理）．
 * 逆元を求める計算量は$\mathcal{O}(\log \mathrm{MOD})$である．
 */

#ifndef LIBMOD
#define LIBMOD
#include "power.cpp"
#include <iostream>
using namespace std;
const int MOD = 1e9+7;
class Z_nZ {
public:
  long long m;
  Z_nZ() { ; }
  Z_nZ(long long v){
    if(v < 0)
      m = v + (- v / MOD + 1) * MOD;
    else
      m = v;
    m %= MOD;
  }
  Z_nZ operator + (const Z_nZ &a){ return Z_nZ( m + a.m ); }
  Z_nZ operator - (const Z_nZ &a){ return Z_nZ( m - a.m ); }
  void operator += (const Z_nZ &a){ m = (m + a.m) % MOD; }
  void operator -= (const Z_nZ &a){ m = (m - a.m + MOD) % MOD; }
  Z_nZ operator * (const Z_nZ &a){ return Z_nZ( m * a.m ); }
  void operator *= (const Z_nZ &a){ m = (m * a.m) % MOD; }
  Z_nZ pow(int k){ return power( Z_nZ(m), k, Z_nZ(1) ); }
  // 以下はMODが素数のときにのみ正しい
  Z_nZ inv(){ return this->pow( MOD - 2 ); }
  Z_nZ operator / (Z_nZ a){ return Z_nZ( m * a.inv().m ); }
  void operator /= (Z_nZ a){ m = (m * a.inv().m) % MOD; }
  friend ostream& operator << (ostream& os, const Z_nZ & a);  
};
ostream& operator << (ostream& os, const Z_nZ & a){
  os << a.m;
  return os;
};
#endif
