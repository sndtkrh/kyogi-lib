// 組合せの基本
/*
 * 組合せなどを計算する時に必要なもの
 * - $n$の階乗
 * - 二項係数$\binom{n}{k}$
 */

#ifndef COMB
#define COMB
#include <algorithm>
#include "mod.cpp"

// n! nの階乗
Z_nZ factorial(long long n){
  Z_nZ ret(1);
  for(int i = 2; i <= n; i++) ret *= Z_nZ( i );
  return ret;
}

// 二項係数 aCb mod MOD
Z_nZ binomial(long long a, long long b){
  Z_nZ ret(1);
  for(int i = a; i > a - b; i--)
    ret *= Z_nZ( i );
  ret /= factorial( b );
  return ret;
}

#endif
