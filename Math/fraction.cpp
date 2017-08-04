// $\mathbb{Q}$
/*
 * 有理数ライブラリ
 */
#ifndef FRACTION
#define FRACTION
#include "gcdlcm.cpp"
#include <iostream>
class Frac{
public:
  long long a, b;
  char sign;
  Frac(){;}
  Frac(long long c){
    sign = 1;
    a = c; b = 1;
    reduce();
  }
  Frac(long long c, long long d){
    sign = 1;
    a = c; b = d;
    reduce();
  }
  inline void reduce(){
    if( a < 0 ){
      a *= -1; sign *= -1;
    }
    if( b < 0 ){
      b *= -1; sign *= -1;
    }
    if( a == 0 ){
      b = 1; sign = 0;
    }else{
      long long d = gcd(a,b);
      a /= d; b /= d;
    }
  }
  Frac operator + (const Frac &f){
    return Frac( sign * a * f.b + f.sign * f.a * b, b * f.b );
  }
  Frac operator += (const Frac &f){
    a = sign * a * f.b + f.sign * f.a * b;
    if( a < 0 ){
      sign = -1; a *= -1;
    }else if( a > 0 ){
      sign = 1;
    }else{
      sign = 0;
    }
    b = b * f.b;
    reduce();
  }
  Frac operator - (const Frac &f){
    return Frac( sign * a * f.b - f.sign * f.a * b, b * f.b );
  }
  Frac operator -(){
    return Frac( -sign * a, b);
  }
  Frac operator -= (const Frac &f){
    a = sign * a * f.b - f.sign * f.a * b;
    if( a < 0 ){
      sign = -1; a *= -1;
    }else if( a > 0 ){
      sign = 1;
    }else{
      sign = 0;
    }
    b = b * f.b;
    reduce();
  }
  Frac operator * (const Frac &f){
    return Frac( sign * f.sign * a * f.a, b * f.b );
  }
  Frac operator *= (const Frac &f){
    sign *= f.sign;
    a *= f.a;
    b *= f.b;
    reduce();
  }
  Frac operator / (const Frac &f){
    return Frac( sign * f.sign * a * f.b, b * f.a );
  }
  Frac operator /= (const Frac &f){
    sign *= f.sign;
    a *= f.b;
    b *= f.a;
    reduce();
  }
  Frac inv(){
    return Frac( sign * b, a );
  }
  bool operator == (long long c){
    return ( b == 1 && sign * a == c || c == 0 && a == 0 );
  }
  bool operator != (long long c){
    return !this->operator==(c);
  }
  bool operator == (const Frac &f){
    return ( a == f.a && b == f.b && sign == f.sign || (a == 0 && f.a == 0) );
  }
  bool operator != (const Frac &f){
    return !(this->operator==(f));
  }
  bool operator > (const Frac &f){
    if ( sign > f.sign ){
      return true;
    }else if(sign < f.sign){
      return false;
    }else{
      if ( sign == 1 ){
	return ( a * f.b > b * f.a );
      }else{
	return ( a * f.b < b * f.a );
      }
    }
  }
  bool operator < (const Frac &f){
    return ( this->operator!=(f) && !(this->operator>(f) ) );
  }
  long double value(){
    long double s = sign;
    long double x = a;
    long double y = b;
    return s * x / y;
  }

  friend ostream& operator << (ostream& os, const Frac& p);
};

ostream& operator << (ostream& os, const Frac& f){
  os << (f.sign < 0 ? "-" : "") << f.a << "/" << f.b;
  return os;
};
/* test
int main(){
  long long a, b, c, d;
  cin >> a >> b >> c >> d;
  Frac s(a,b), t(c,d);
  cout << s.value() <<" " << t.value() << endl;
  cout << (s * t).value() << endl;
  cout << " A < B ? " << ((s < t) ? "true" : "false") << endl;
}
*/
#endif
