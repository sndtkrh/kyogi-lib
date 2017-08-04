// ベル数
/*
 * \[B_n := n\text{個のものを分割する方法の総数}\]
 * $B_n$は 0-origin で
 * \[1, 1, 2, 5, 15, 52, 203, 877, 4140, 21147, 115975, 678570, 4213597, \cdots \]
 * 
 * $B_n$は以下の漸化式で求められる
 * \[B_0 = B_1 = 1, \ B_{n} = \sum_{k=0}^{n-1} \binom{n-1}{k} * B_k \]
 *
 * $p$を素数としたとき以下が成立する．
 * \[B_{p+n} = B_n + B_{n+1} \ (mod p)\]
 */

#ifndef BELL
#define BELL
#include "mod.cpp"
#include "combination.cpp"
#include <vector>
using namespace std;

// B_0, B_1, ... , B_n
vector<Z_nZ> bell_number(int n){
  vector<Z_nZ> B;
  vector<Z_nZ> v;
  B.push_back(Z_nZ(1));
  B.push_back(Z_nZ(1));
  v.push_back( B[0] );
  for(int i = 0; i < n - 1; i++){
    vector<Z_nZ> u(i+2);
    u[0] = v[i];
    for(int j = 0; j <= i; j++)
      u[j+1] = u[j] + v[j];
    B.push_back( u[i+1] );
    v = u;
  }
  return B;
}
/* test
int main(){
  vector<Z_nZ> B = bell_number(5);
  for(int i = 0; i < B.size(); i++){
    cout << B[i].m << endl;
  }
  cout << endl;
}
*/
#endif
