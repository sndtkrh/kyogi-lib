// ペラン数
/*
 * ペラン数は以下の漸化式で定義される数である：
 * \[ P_0 = 3, \  P_1 = 0, \ P_2 = 2, \  P_n = P_{n-2} + P_{n-3} \]
 * 具体的には
 * \[ 3, 0, 2, 3, 2, 5, 5, 7, 10, 12, 17, 22, 29, \dots \]
 * $n$-頂点の標識閉路グラフに置ける異なる極大独立集合の個数は，$n$番目のペラン数に等しい．
 */
#include "mod.cpp"
#include "matrix.cpp"

Z_nZ perrin_number(long long n){
  Matrix<Z_nZ> A(P(3,3), Z_nZ(0));
  A.M[0][1] = A.M[0][2] = Z_nZ(1);
  A.M[1][0] = Z_nZ(1);
  A.M[2][1] = Z_nZ(1);
  return Z_nZ(2) * A.M[2][0] + Z_nZ(3) * A.M[2][2];
}
/* test
int main(){
  long long n;
  cin >> n;
  cout << perrin_number(n).m << endl;
}
*/
