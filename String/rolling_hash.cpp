// ローリングハッシュ
/*
 * 文字列$S=c_1 \dots c_n$の部分文字列$c_l \dots c_r$のハッシュ$H(l,r)$を次の式で計算する．
 * ただし，$p,M$は互いに素である． 
 * \[ H(0,k) = \sum_{i=0}^{k-1} c_i p^{k-i-1} \mod M \]
 * \[ H(l,r) = (H(0,r) - H(0,l)p^{r-l}) \mod M \]
 * ハッシュ値が衝突しそうなときは$\verb|pair|$などで値を複数持つ．
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2444
 */
#include <algorithm>
#include <vector>
#include "../Math/mod.cpp"
using namespace std;

template <long long p0>
class RollingHash{
  Z_nZ p;
  vector<Z_nZ> h;
public:
  RollingHash(string str){
    p = Z_nZ(p0);
    int n = str.size();
    h.resize(n + 1);
    fill(h.begin(), h.end(), Z_nZ(0));
    h[0] = Z_nZ(0);
    for(int i = 0; i < n; i++){
      h[i+1] = h[i] * p + Z_nZ(str[i]);
    }
  }
  Z_nZ get_hash(int l, int r){
    return h[r] - h[l] * p.pow(r-l);
  }
};
