// モンモール数
/*
 * モンモール数$a_n$は$1,\dots,n$の完全順列の総数である
 * 各$a_n$は 0-origin で，
 * \[0, 0, 1, 2, 9, 44, 265, 1854, 14833, 133496, 1334961, \dots \]
 * である．
 * 一般項は
 * \[ a_n = n! \sum_{k=0}^{n} \frac{(-1)^k}{k!} \]
 */

#ifndef MONTMORT
#define MONTMORT
#include <iostream>
#include <algorithm>
#include "mod.cpp"
#include "combination.cpp"
using namespace std;

Z_nZ montmort(int n){
  if ( n == 0 ) return Z_nZ(0);
  Z_nZ ret(0);
  for(int k = 0; k <= n; k++)
    ret += Z_nZ( 1 - (k%2) * 2 ) / factorial( k );
  return factorial(n) * ret;
}
/* test
int main(){
  int N = 100;
  for(int i = 0; i < N; i++){
    cout << montmort(i).m << " ";
  }
  cout << endl;
}
*/
#endif
