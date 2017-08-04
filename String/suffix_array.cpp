// 接尾辞配列
/*
 * 文字列の長さを$n$とすると計算量$\mathcal{O}(n \log^2 n)$ 
 */
#ifndef SA
#define SA
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef pair<int,int> P;

class SuffixArray{
  string str;
public:
  vector<int> sa;
  SuffixArray(string str_) : str(str_){
    str += '$';
    int len = str.size();
    // ((左半分のランク, 右半分のランク), 添字)
    vector< pair<P, int> > ranks(len);
    for(int i = 0; i < len; i++){
      ranks[i].first.first = str[i];
      ranks[i].first.second = str[i];
      ranks[i].second = i;
    }
    for(int p = 1; p <= len * 2; p *= 2){
      sort(ranks.begin(), ranks.end());
      int r = 0;
      vector< pair<P, int> > new_ranks(len);
      for(int i = 0; i < len; i++){
	new_ranks[i].second = i;
	new_ranks[i].first.second = -1;
      }
      for(int i = 0; i < len; i++){
	if(i > 0 && ranks[i-1].first != ranks[i].first)
	  r++;
	int k = ranks[i].second;
	new_ranks[k].first.first = r;
	if( k - p >= 0 )
	  new_ranks[k - p].first.second = r;
      }
      ranks = new_ranks;
    }
    sort(ranks.begin(), ranks.end());
    sa.resize(len);
    for(int i = 0; i < len; i++)
      sa[i] = ranks[i].second;
  }
  // str[i:$] < q
  bool cmp(int i, string q){
    int t = min(str.size() - i, q.size() );
    for(int k = 0; k < t; k++){
      if(str[i + k] < q[k]) return true;
      if(str[i + k] > q[k]) return false;
    }
    if(str.size() - i < q.size() ) return true;
    return false;
  }
  int left_find(string q){
    int left = 0, right = str.size();
    for(int p = 1; p < str.size() * 2; p *= 2){
      int m = (left + right) / 2;
      if( cmp(sa[m], q) )
	left = m;
      else
	right = m;
    }
    return left + 1;
  }
  int right_find(string q){
    q += '~';
    int left = 0, right = str.size();
    for(int p = 1; p < str.size() * 2; p *= 2){
      int m = (left + right) / 2;
      if( cmp(sa[m], q) )
	left = m;
      else
	right = m;
    }
    return left + 1;
  }
};
#endif

