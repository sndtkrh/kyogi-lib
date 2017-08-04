// ピックの定理
/*
 * 格子点を頂点とする多角形について
 * 面積を$S$，辺上の格子点の個数を$b$，内部の格子点の個数を$i$とすると
 * \[ 2S = 2i + b - 2 \]
 * が成り立つ
 */
//多角形の内部の格子点の数i，多角形の辺上の格子点の数bとしたときその多角形の面積の2倍を返す
long long pick_theorem_2S(long long i, long long b){
  return 2 * i + b - 2;
}
//内部の格子点の数を求める
long long pick_theorem_i(long long S, long long b){
  return (2S - b + 2) / 2;
}
