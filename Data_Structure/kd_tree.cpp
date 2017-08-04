// 平衡kD木
/*
 * $k$次元ユークリッド空間上の点に対するデータ構造
 * 計算量は次元$k$を定数としてデータの個数$n$とすると，
 * - 木の構築$\mathcal{O}(n \log n)$
 * - 要素の範囲検索$\mathcal{O}(\log n)$
 * である．
 * - verified by: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_C
 * - verify 用の問題はTLEが厳しい $\Rightarrow$ \verb|scanf| \verb|pintf| を使うとよい
 * - verify 用の問題はMLEも厳しい $\Rightarrow$ \verb|ps|を内部で持たず，その都度参照を渡すようにするとACできる
 * - 上のことをしてもダメなときは，おとなしく次元を固定して書き直そう．
 */
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> Point;

class Compare{
public:
  int k;
  Compare(int k) : k(k){ ; }
  bool operator() (const Point &a, const Point &b){
    return a[k] < b[k]; // k次元目の座標で比較
  }
};

class node{
public:
  int p; // 座標のindex
  int right, left; // 左右の子のindex
  node(){;}
  node(int p) : p(p), right(-1), left(-1) {;}
};

class kDTree{
public:
  int k; // 次元
  vector<node> ns;   // ノード
  vector<Point> ps;  // 座標
  vector<Point> tps; // 座標（作業用）
  kDTree(int k, vector<Point> &_ps) : k(k), ps(_ps), tps(_ps) {
    for(int i = 0; i < tps.size(); i++)
      tps[i].push_back(i); //各座標の末尾にindexを付け加える
    construct(0, tps.size(), 0);
    tps.clear();
  }
  // psの区間[l,r)のkD木を構築 構築したnodeのindexを返す
  int construct(int l, int r, int depth){
    if( l == r ) return -1;
    int cmp = depth % k; // この次元でソート
    int m = (l + r) / 2;
    sort( tps.begin() + l, tps.begin() + r, Compare(cmp) );
    int id = ns.size();
    ns.push_back( node( tps[m][k] ) );
    if( l + 1 == r ){
      return id;
    }
    int ll = construct(l, m, depth + 1);
    int rr = construct(m+1, r, depth + 1);
    ns[id].left = ll;
    ns[id].right = rr;
    // 以下のように書くとバグって死ぬ．なんで？
    // => 特定バージョンのコンパイラのバグっぽい
    // ns[id].left =  construct(l, m, depth + 1);
    // ns[id].right = construct(m+1, r, depth + 1);
    return id;
  }
  // range は開区間で与えてくれ．
  vector<int> ret;
  vector<int> find(const pair<Point,Point> &range){
    ret.clear();
    find( range, 0, 0 );
    return ret;
  }
  void find(const pair<Point,Point> &range, int nodeidx, int depth){
    int cmp = depth % k;
    const Point &L = range.first;
    const Point &R = range.second;
    const node &n = ns[nodeidx]; // 今見ているノード
    const Point &p = ps[n.p];    // 今見ているノードの座標

    if( L[cmp] <= p[cmp] && n.left != -1){
      find(range, n.left, depth + 1);
    }
    if( p[cmp] < R[cmp] && n.right != -1){
      find(range, n.right, depth + 1);
    }
    bool f = true;
    for(int i = 0; i < k; i++){
      if(p[i] < L[i] || R[i] <= p[i] ){
	f = false;
	break;
      }
    }
    if(f)
      ret.push_back( n.p ); // 座標のindexを返す
  }
};
/* test
int main(){
  int N;
  scanf("%d", &N);
  vector<Point> ps(N, vector<int>(2) );
  for(int i = 0; i < N; i++){
    int x, y;
    scanf("%d %d", &x, &y);
    ps[i][0] = x;
    ps[i][1] = y;
  }
  kDTree kdt(2,ps);
  ps.clear();
  int Q;
  scanf("%d", &Q);
  pair<Point,Point> range;
  for(int i = 0; i < Q; i++){
    int sx, tx, sy, ty;
    scanf("%d %d %d %d", &sx, &tx, &sy, &ty);
    range.first.clear();
    range.second.clear();
    range.first.push_back(sx);
    range.first.push_back(sy);
    range.second.push_back(tx + 1); // 開区間にするために1足している
    range.second.push_back(ty + 1);
    vector<int> ans = kdt.find(range);
    sort(ans.begin(), ans.end());
    for(int i = 0; i < ans.size(); i++)
      printf("%d\n", ans[i]);
    puts("");
  }
}
*/
