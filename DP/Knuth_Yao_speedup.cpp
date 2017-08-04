// KnuthとYaoの高速化
/*
 * $f:\mathcal{N}^2 \to \mathcal{N}$がMongeであるとは，
 * 任意の$i\le j, k \le l$に対して
 * \[ f(i,l) + f(j,k) \ge f(i,k) + f(j,l) \]
 * となることである．
 *
 * $w:\mathcal{N}^2 \to \mathcal{N}$が次を充たすとする．（$i\le j$）
 * - $w$はMonge
 * - $w$は単調，つまり$[i,j] \subseteq [k,l] $ならば$w(i,j) \le w(k,l)$
 * このとき
 * \[ X(i,j) = \min_{i \le s < j} \{ X(i,s) + X(s+1,j) \} + w(i,j) \]
 * で定まる$X$はMongeであり，動的計画法の計算量が落ち$\mathcal{O}(n^2)$で計算できる．
 * 以下のコードで
 * \[K(i,j) = \mathrm{argmin}\{ X(i,s) + X(s+1,j) \} = \max\{ r \in [i,j) \mid r = \min_{s}\{ X(i,s) + X(s+1,j) \} \} \]
 * である．
 * $K$は$K(i,j) \le K(i,j+1) \le K(i+1,j+1)$を充たすことが証明できる．
 * この事実を用いて動的計画法のテーブルを対角線から埋めていけば参照する箇所が減る．
 */
#include <algorithm>
using namespace std;
const int INF = 1e9;
const int MAXN = 3000;
long long X[MAXN][MAXN];
int K[MAXN][MAXN];
void dp(){
  for(int i = 0; i < N; i++){
    X[i][i] = 0; // 初期値
    K[i][i] = i;
  }
  for(int k = 1; k < N; k++){ // k=対角線からのズレ
    for(int i = 0; i + k < N; i++){
      int j = i + k;
      long long tmp = INF;
      // K の単調性から K[i][j-1] <= K[i][j] <= K[i+1][j]
      for(int r = K[i][j-1]; r <= K[i+1][j]; r++){
	long long c = X[i][r] + X[r+1][j] + weight(i,j);
	if ( c <= tmp ){
	  tmp = c;
	  K[i][j] = r;
	}
      }
      X[i][j] = tmp;
    }
  }
}
