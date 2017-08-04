// フィボナッチ数
/*
 * フィボナッチ数
 * \[0, 1, 1, 2, 3, 5, 7, 13, 21, \dots \]
 * を高速に求める．
 */

#ifndef FIBNACCI
#define FIBNACCI
#include "mod.cpp"
#include "matrix.cpp"

Z_nZ fibonacci_number(long long n){
  Matrix<Z_nZ> A(P(2,2),Z_nZ(1));
  A.M[1][1] = Z_nZ(0);
  A = power(A, n - 1);
  return A.M[0][0];
}
/* test
int main(){
  long long n;
  cin >> n;
  Z_nZ f = fibonacci_number( n );
  cout << f.m << endl;
}
*/
#endif
