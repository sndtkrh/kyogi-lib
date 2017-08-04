// 素数
/*
 * 素数に関するライブラリ
 * - 素数判定（$\mathcal{O}(\sqrt{n})$）
 * - エラトステネスの篩
 */
#ifndef PRIME
#define PRIME
#include <algorithm>
#include <vector>
using namespace std;
bool is_prime(int n){
  if(n <= 1) return false;
  for(int i = 2; i * i <= n; i++)
    if( n % i == 0) return false;
  return true;
}

vector<char> primes(int n){
  vector<char> p(n+1, 1);
  p[0] = p[1] = 0;
  for(int i = 2; i <= n; i++){
    if( p[i] == 1 )
      for(int j = i * 2; j <= n; j += i)
	p[j] = 0;
  }
  return p;
}

/* test
#include <iostream>
int main(){
  int n = 100;
  vector<char> p = primes(n);
  for(int i = 0; i < n; i++){
    cout<< "i=" << i <<" p[i]=" << (p[i] == 1 ? 1 : 0) << " is_prime()=" << (is_prime(i) ? 1 : 0) << endl;
  }
}
*/
#endif
