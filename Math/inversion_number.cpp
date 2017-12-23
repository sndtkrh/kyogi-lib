/*
 * 転倒数を求める
 * O(N log N)
 */
#ifndef INVNUM
#define INVNUM
#include <bits/stdc++.h>
#include "../Data_Structure/segment_tree.cpp"
using namespace std;

// 順列の転倒数
int inversion_number_perm(vector<int> & p){
  vector<int> vs(p.size(), 1);
  SegmentTree<int, SUM<int> > st( vs, SUM<int>() );
  vector<int> idx(p.size());
  for(int i = 0; i < p.size(); i++){
    idx[p[i]] = i;
  }
  int ans = 0;
  for(int i = 0; i < idx.size(); i++){
    ans += st.query( 0, idx[i] );
    st.update( idx[i], 0 );
  }
  return ans;
}
// 一般の数列の転倒数
int inversion_number(vector<long long> & v){
  vector< tuple<long long,int> > vv;
  for(int i = 0; i < v.size(); i++){
    vv.emplace_back( v[i], i );
  }
  sort( vv.begin(), vv.end() );
  vector<int> p(v.size());
  for(int i = 0; i < vv.size(); i++){
    long long val;
    int idx;
    tie(val, idx) = vv[i];
    p[idx] = i;
  }
  return inversion_number_perm( p );
}
int main(){
  int N;
  while(1){
    cin >> N;
    if( N == 0 ) break;
    vector<long long> a( N );
    for(int i = 0; i < N; i++){
      cin >> a[i];
    }
    cout << inversion_number(a) << endl;
  }
}
#endif
