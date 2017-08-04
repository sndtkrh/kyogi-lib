// 非標識グラフの数え上げ
/*
 * 全ての非標識グラフを数え上げる
 */
#ifndef NLGRAPH
#define NLGRAPH
#include <vector>
#include <algorithm>
#include "../Math/mod.cpp"
#include "../Math/symmetric_group.cpp"
#include "../Math/gcdlcm.cpp"
#include "graph_counting.cpp"
using namespace std;
// Z_nZ g = graph(n)
// 位数nの非標識グラフの個数が求まる
Z_nZ graph(int n){
  Z_nZ ret(0);
  vector< vector<int> > j = enum_types( n );
  for(int i = 0; i < j.size(); i++){
    long long r = 0;
    for(int k = 1; k <= n; k++){
      long long s = 0;
      if ( 2 * k     <= n ) s += j[i][2*k-1];
      if ( 2 * k + 1 <= n ) s += j[i][2*k];
      long long jj = j[i][k-1];
      r += k * (s + jj * (jj - 1) / 2);
    }

    for(int x = 0; x < n; x++)
      for(int y = x + 1; y < n; y++)
	r += gcd( (x+1), (y+1) ) * j[i][x] * j[i][y];
    ret += cauchy_h( j[i] ) * power( Z_nZ(2), r );
  }
  return ret / factorial( n );
}
/* test
#include <iostream>
using namespace std;
int main(){
  int n;
  cin >> n;
  cout << graph(n).m << endl;

}
*/
#endif
