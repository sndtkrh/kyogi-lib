// 区間クラス
/*
 * 区間を扱うための基盤
 */
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
typedef int Value;

// 半開区間[s,t)
class Interval{
public:
  long long s, t;
  int id; // 区間のID
  Value value; // 区間の値
  Interval(){;}
  Interval(long long s, long long t) : s(s), t(t) {;}
  Interval(long long s, long long t, int i) : s(s), t(t), id(i) {;}
  Interval(long long s, long long t, int i, Value v):s(t),t(t),id(i),value(v){;}
  
  // 区間の交差包含判定
  // 真に交差しているときにtrue
  bool is_cross(const Interval &i){
    return (i.s - t) * (i.t - s) < 0;
  }
  // 含まれているときに true
  bool in(const Interval &i){
    return (i.s <= s && t <= i.t);
  }
  // 含んでいるときに true
  bool ni(const Interval &i){
    return (s <= i.s && i.t <= t);
  }
  // 共通部分を持つとき true
  bool intersection(const Interval &i){
    return (is_cross(i) || in(i) || ni(i));
  }
};
// 比較は区間が直線上（円環状でない）の場合のみ有効に機能することに注意
// 始点sで比較
bool comp_with_s(const Interval &j, const Interval &i){
  if( j.s < i.s ) return true;
  if( j.s > i.s ) return false;
  if( j.t < i.t ) return true;
  return false;
}
// 終点tで比較
bool comp_with_t(const Interval &j, const Interval &i){
  if( j.t < i.t ) return true;
  if( j.t > i.t ) return false;
  if( j.s < i.s ) return true;
  return false;
}
bool operator == (const Interval &j, const Interval &i){
  return (j.s == i.s && j.t == i.t);
}
bool operator < (const Interval &j, const Interval &i){
  return comp_with_t( j, i );
}
bool operator > (const Interval &j, const Interval &i){
  return !(j < i && j == i);
}

// 直線上の区間の集合
class LineI : public vector<Interval>{
public:
  void add(long long s, long long t){
    // i(0-origin)番目に add_interval() された区間のidがiになる
    push_back( Interval(s, t, size() ) );
  }
  // id を指定して区間を追加
  void add(long long s, long long t, int id){
    at(id) = Interval(s, t, id);
  }
  void add(Interval i){
    at(i.id) = i;
  }
};

// 円環状の区間の集合
class RingI : public LineI{
public:
  long long R;
  RingI(int n, long long ring_size) : R(ring_size){
    resize(n);
  }
  // 場所posで円環を切り開きpos=0とする区間の集合に変換．
  // posをまたぐ(s<pos<=tとなる)区間IがあるときはI=[s, R+t)とする．
  LineI cut_at(long long pos){
    LineI i;
    for(int k = 0; k < i.size(); k++){
      if( at(k).s < pos ){
	if( pos <= at(k).t )
	  i.add( at(k).s, at(k).t + R, at(k).id );
	else
	  i.add( at(k) );
      }else{
	i.add( at(k).s - pos, at(k).t - pos, at(k).id );
      }
    }
    return i;
  }
};
