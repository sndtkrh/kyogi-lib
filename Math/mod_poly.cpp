// $\mathbb{Z}/n\mathbb{Z} [x]$の掛け算
/*
 *
 */
#ifndef MODPOLY
#define MODPOLY
#include <vector>
#include "mod.cpp"
#include "FFT.cpp"
/* FFTを使いたいときはこれを使うけど誤差が怖い
vector<Z_nZ> operator * (const vector<Z_nZ> &g, const vector<Z_nZ> &h){
  int n = 1;
  int gs = g.size();
  int hs = h.size();
  int fs = gs + hs - 1;
  while( n <= fs + 1 ) n *= 2;
  vector<comp> gg(n), hh(n), ff(n);
  for(int i = 0; i < n; i++){
    gg[i] = (i < gs) ? g[i].m : 0;
    hh[i] = (i < hs) ? h[i].m : 0;
  }

  fft(gg, n, false);
  fft(hh, n, false);
  for(int i = 0; i < n; i++) ff[i] = gg[i] * hh[i];
  fft(ff, n, true);

  vector<Z_nZ> f(fs);
  for(int i = 0; i < fs; i++){
    f[i] = Z_nZ( round( ff[i].real() / n ) );
  }
  return f;
}
void operator *= (vector<Z_nZ> &g, vector<Z_nZ> &h){
  g = g * h;
}
*/
vector<Z_nZ> operator * (vector<Z_nZ> &g, vector<Z_nZ> &h){
  vector<Z_nZ> f( g.size() + h.size() - 1, Z_nZ(0) );
  for(int k = 0; k < f.size(); k++){
    for(int i = 0; i < g.size(); i++){
      int j = k - i;
      if( 0 <= j && j < h.size() ){
	f[k] += g[i] * h[j];
      }
    }
  }
  return f;
}
void operator *= (vector<Z_nZ> &g, vector<Z_nZ> &h){
  g = g * h;
}
#endif
