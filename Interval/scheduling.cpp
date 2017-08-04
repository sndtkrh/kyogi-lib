// 区間スケジューリング問題
/*
 * $n$個の直線状区間の区間スケジューリング問題を$\mathcal{O}(n \log n)$で解く
 */
#include "interval.cpp"

// 区間スケジューリング問題を解く
int scheduling(LineI &li){
  sort(li.begin(), li.end(), comp_with_t);
  int ans = 0, pret = 0;
  for(int i = 0; i < li.size(); i++){
    if( pret <= li[i].s){
      ans++;
      pret = li[i].t;
    }
  }
  return ans;
}
/* test
int main(){
  int n;
  cin >> n;
  LineI itv;
  for(int i = 0; i < n; i++){
    long long a, b;
    cin >> a >> b;
    itv.add(a,b);
  }
  cout << scheduling(itv) << endl;
}
*/
