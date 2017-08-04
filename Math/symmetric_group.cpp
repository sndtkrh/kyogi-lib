// 対称群$\mathfrak{S}_n$
/*
 * Cauchyの公式：
 * 対称群$\mathfrak{S}_n$の$(j) = (j_1, \dots , j_n)$型の共役類に含まれる元の個数$h(\mathfrak{S}_n:(j))$は
 * \[ h(\mathfrak{S}_n:(j)) = \frac{ n! }{ 1^{j_1} j_1 ! \cdots n^{j_n} j_n ! } \]
 * で与えられる．
 */

#ifndef CAUCHY
#define CAUCHY
#include <vector>
#include "mod.cpp"
#include "combination.cpp"

// Cauchy の公式
Z_nZ cauchy_h( vector<int> j){
  int t = 0, n = j.size();
  for(int i = 0; i < n; i++) t += (i+1) * j[i];
  if( n != t ) return Z_nZ(0);
  Z_nZ d(1);
  for(int i = 0; i < n; i++)
    d *= power( Z_nZ(i+1), j[i], Z_nZ(1) ) * factorial( j[i] );
  return factorial( n ) / d;
}

void calc_types(int i,int sum,int n,vector<int> &t,vector<vector<int> > &types);
// 対称群S_nの共役類の型の列挙
vector< vector<int> > enum_types(int n){
  vector< vector<int> > types;
  vector<int> t(n, 0);
  calc_types(n - 1, 0, n, t, types);
  return types;
}
void calc_types(int i,int sum,int n,vector<int> &t,vector<vector<int> > &types){
  if ( sum == n ){
    types.push_back( t );
    return;
  }
  if ( i == 0 ){
    t[0] = n - sum;
    types.push_back( t );
    t[0] = 0;
    return;
  }
  for(int k = 0; sum + (i + 1) * k <= n; k++){
    t[i] = k;
    calc_types( i - 1, sum + (i + 1) * k, n, t, types);
    t[i] = 0;
  }
}
/* test
#include <iostream>
int main(){
  int n;
  cin >> n;
  vector< vector<int> > types = enum_types(n);
  cout << types.size() << endl;
  for(int i = 0; i < types.size(); i++){
    for(int k = 0; k < types[i].size(); k++){
      cout << types[i][k] << " ";
    }
    cout << cauchy_h( types[i] ).m << endl;
  }
}
*/
#endif
