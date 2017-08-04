// カタラン数
/*
 * 一般項は
 * \[ c_n = \binom{2n}{n} / n \]
 * 漸化式では
 * \[ c_0 = 1, c_{n+1} = \sum_{i=0}^{n} c_i \cdot c_{n-i} \]
 * 具体的なカタラン数は 0-origin で
 * \[1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900, 2674440, 9694845, \dots \]
 *
 * $n$番目のカタラン数 $c_n$ は次に等しい
 *
 * \subsection{$x_1, x_2, x_3, \dots ,x_n$に対し括弧づける方法の数}
 * 例えば
 * \[ (x_1 (x_2 (x_3 x_4))), \ (x_1 ((x_2 x_3) x_4)),\ ((x_1 x_2) (x_3 x_4)),\ ((x_1 (x_2 x_3)) x_4),\ (((x_1 x_2) x_3) x_4) \]
 * だから$c_4 = 5$である．
 *
 * \subsection{葉の数$n$の正則な二分木の個数}
 * 正則な二分木とは，葉以外の各ノードがちょうど2個の子を持ち
 * それぞれが右の子，左の子と順序付けられている二分木のことを言う．
 *
 * \subsection{$(0,0)$から対角線を超えずに格子点を通って，(n,n)まで最短距離で繋ぐ道順の総数}
 *
 * \subsection{$2n$人が円になって手を交差させないで握手をする場合の数}
 *
 */

#ifndef CATALAN
#define CATALAN
#include <iostream>
#include <vector>
#include <algorithm>
#include "mod.cpp"
#include "combination.cpp"

Z_nZ catalan(int n){
  return binomial( 2 * n, n) / Z_nZ(n + 1);
}

/* test
int main(){
  int N = 100;
  for(int i = 0; i < N; i++){
    cout << catalan(i).m << " ";
  }
  cout << endl;
}
*/
#endif
