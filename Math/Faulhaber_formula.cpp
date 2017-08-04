// ファウルハーバーの公式
/*
 * 最初の$n$個の$k$乗数の和
 * \[ S_k(n) := 0^k + 1^k + 2^k + \dots + (n-1)^k \]
 * をベルヌーイ数を用いてnの多項式で表す．
 * \[B_0 = 1, \ B_n = \frac{-1}{n+1} \sum_{k=0}^{n-1} \binom{n+1}{k} B_k \]
 * でベルヌーイ数を定義する．
 * \[ S_k(n) = \frac{1}{k+1} \sum_{j=0}^k \binom{k+1}{j} B_j n^{k+1-j} \]
 * が成り立つ．
 *
 * $S_k(n)$ を求めるのに
 * ベルヌーイ数を求める前処理に$\mathcal{O}( k^2 \log \mathrm{MOD} )$ぐらい，
 * $S_k(n)$ を求めるのに$\mathcal{O}( k^2 \log k)$ぐらい．
 * ベルヌーイ数を求めるのは一度でよい
 */
#include "combination.cpp"
#include "mod.cpp"
#include <vector>
using namespace std;

// ベルヌーイ数 B_i
// B_0 , ... , B_k までを返す
// O( k^2 log MOD )ぐらい
vector<Z_nZ> bernoulli_number(int k){
  vector<Z_nZ> B(k+1, Z_nZ(0) );
  B[0] = 1;
  for(int i = 1; i <= k; i++){
    Z_nZ b(1);
    for(int j = 0; j < i; j++){
      B[i] += b * B[j];
      b *= Z_nZ(i - j + 1) / Z_nZ(j + 1);
    }
    B[i] /= Z_nZ( -(i+1) );
  }
  return B;
}

// sum_of_power_i_k(k,n,B) = 0^k + 1^k + ... + n^k
// O( k^2 log k )
Z_nZ sum_of_power_i_k(int k, long long n, vector<Z_nZ> &B){
  Z_nZ ret(0);
  for(int j = 0; j <= k; j++){
    ret += binomial(k+1, j) * B[j] * power(n+1, k-j+1, 1LL);
  }
  return ret / Z_nZ(k+1);
}

/* test
int main(){
  int k;
  long long n;
  cin >> k >> n;
  vector<Z_nZ> B = bernoulli_number( k );
  for(int i = 1; i <= k; i++)
    cout << sum_of_power_i_k(i, n, B).m << endl;
}
*/
