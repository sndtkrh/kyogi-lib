#ifndef GEOMETRY
#define GEOMETRY
#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
typedef complex<double> Point; // 複素数平面をR^2とみなす
typedef pair<Point, Point> Line;
typedef vector<Point> Polygon;

// epsを考慮して同じ点か判定
bool is_same_point( Point a, Point b ){
  return (a.real() - eps < b.real()) && (b.real() < a.real() + eps) &&
    (a.imag() - eps < b.imag()) && (b.imag() < a.imag() + eps);
}
// 外積（平行四辺形の符号付き面積）
double det( Point a, Point b ){
  return a.real() * b.imag() - a.imag() * b.real();
}

// 点の辞書式順序
bool cmp_points( Point &a, Point &b){
  if( a.real() != b.real() ) return a.real() < b.real();
  return a.imag() < b.imag();
}

// 点a,bのa->bの位置に対して点cが半時計回りの位置にあるか
bool ccw( Point a, Point b, Point c ){
  Point u = b - a;
  Point v = c - a; 
  if( det(u,v) > -eps )
    return true;
  return false;
}

// 線分が交叉しているか
bool is_cross( Line m, Line n ){
  Point a1 = m.first, a2 = m.second;
  Point b1 = n.first, b2 = n.second;
  return (det(a2-a1, b1-a1) * det(a2-a1, b2-a1) < eps) &&
    (det(b2-b1, a1-b1) * det(b2-b1, a2-b1) < eps);
}

// ふたつの直線の交点
Point cross_point( Line m, Line n ){
  Point b = n.second - n.first;
  double d1 = abs( det( b, m.first  - n.first ) );
  double d2 = abs( det( b, m.second - n.first ) );
  double t = d1 / (d1 + d2);
  return m.first + (m.second - m.first) * t;
}

// 凸法
Polygon convex( vector<Point> ps ){
  sort( ps.begin(), ps.end(), cmp_points );
  int k = 0;
  vector<Point> poly( 2 * ps.size() );
  // 下側の凸法
  for(int i = 0; i < ps.size(); i++){
    while( k > 1 && ! ccw( poly[k-2], poly[k-1], ps[i] ) ) k--;
    poly[k++] = ps[i];
  }
  // 上側の凸法
  for(int i = ps.size() - 2, t = k; i >= 0; i--){
    while( k > t && ! ccw( poly[k-2], poly[k-1], ps[i] ) ) k--;
    poly[k++] = ps[i];
  }
  poly.resize( k - 1 );
  return poly;
}

// 凸多角形の面積
double area( Polygon poly ){
  double a = 0;
  Point p = poly[0], q = poly[1], r;
  for(int i = 2; i < poly.size(); i++){
    r = poly[i];
    a += abs( det( q-p, r-p) / 2.0 );
    q = r;
  }
  return a;
}

// 多角形と線分の交叉判定（点で接するものは交叉とみなさない）
// not verified
bool is_cross( const Polygon& poly, Line l ){
  Point q = poly[poly.size()-1];
  for(auto p : poly ){
    Line m(q,p);
    if( is_cross( m, l ) ){
      Point t = cross_point( m, l );
      if( !is_same_point(t, l.first) && !is_same_point(t, l.second) )
	return true;
    }
    q = p;
  }
  return false;
}
#endif

/* test AOJ 2635 */
bool solve( vector<Point>& ps ){
  double pre_area = -1;
  for(int i = 1; i < ps.size(); i++){
    vector<Point> b;
    for(int k = 0; k <= i; k++) b.push_back( ps[k] );
    double a = area( convex( b ) );
    if( abs( a - pre_area ) < eps ) return false;
    pre_area = a;
  }
  return true;
}
int main(){
  int N;
  cin >> N;
  vector<Point> ps;
  bool ans = true;
  for(int i = 0; i < N; i++){
    double x, y;
    cin >> x >> y;
    ps.push_back( complex<double>(x, y) );
  }
  if( !solve(ps) ) ans = false;
  reverse( ps.begin(), ps.end() );
  if( !solve(ps) ) ans = false;
  if( ans )
    cout << "Possible" << endl;
  else
    cout << "Impossible" << endl;
}
/**/
