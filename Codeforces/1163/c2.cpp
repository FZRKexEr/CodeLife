//
//  c2.cpp
//  2022-07-21 18:48
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long



struct Frac {
  pair<int, int> frac; 

  pair<int, int> std(int a, int b) {
    if (a == 0) { return {0, 1}; }  
    if (b == 0) { return {1, 0}; }
    int g = gcd(a, b);
    a /= g; b /= g;
    if (a < 0) b *= -1, a *= -1;
    return {a, b};
  }

  int lcm(int a, int b) { return a / gcd(a, b) * b; }

  Frac(int a, int b) { frac = std(a, b); }

  bool operator == (const Frac &oth) const { return frac == oth.frac; }
  bool operator < (const Frac &oth) const {
    if (frac == oth.frac) return false;
    if (frac.first == 0) return false;
    if (oth.frac.first == 0) return true;
    return frac.second * oth.frac.first < frac.first * oth.frac.second;
  }
  Frac operator * (const Frac &oth) {
    assert(frac.first); 
    assert(oth.frac.first); 
    Frac ans(frac.first * oth.frac.first, frac.second * oth.frac.second); 
    return ans;
  }
  Frac operator + (const Frac &oth) {
    assert(frac.first); 
    assert(oth.frac.first); 
    int l = lcm(frac.first, oth.frac.first); 
    Frac ans(l, frac.second * (l / frac.first) + oth.frac.second * (l / oth.frac.first));
    return ans;
  }
  Frac operator + (const int &oth) { return (*this) + (Frac) {1, oth}; }
  Frac operator * (const int oth) { return (*this) * (Frac) {1, oth}; }
  Frac operator / (const Frac &oth) { return (*this) * (Frac) {oth.frac.second, oth.frac.first}; }
  Frac operator / (const int &oth) { return (*this) * (Frac) {oth, 1}; }
  Frac operator - (Frac oth) { return (*this) + oth * -1; }
  Frac operator - (int oth) { return (*this) + oth * -1; }
};

struct Line {
  Frac k;
  int a, b, c;
  
  Line(pair<int, int> a, pair<int, int> b) : k(b.first - a.first, b.second - a.second) {
    if (k.frac.first != 0) {
      k = k * 2;
      k = k / 2;
      k = k + 2;
      k = k - 2;
    }
    assert(a != b);
    this->a = - k.frac.second; 
    this->b = k.frac.first;
    this->c = -1 * (this->a) * a.first - (this->b) * a.second;
  }

  bool operator < (const Line &oth) const {
    if (a != oth.a) return a < oth.a;
    if (b != oth.b) return b < oth.b;
    return c < oth.c;
  }

  bool operator == (const Line & oth) const {
    if (!(k == oth.k)) return false;
    if (a != oth.a || b != oth.b || c != oth.c) return false;
    return true; 
  }
};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  
  int n; cin >> n;
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].first >> a[i].second;
  }

  set<Line> b;

  int ans = 0;

  map<Frac, int> cnt1;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      Line input(a[i], a[j]);
      b.insert(input);  
    }
  }

  int cnt = 0;
  for (auto &it : b) {
    ans += cnt - cnt1[it.k];     
    cnt++;
    cnt1[it.k]++;
  }

  cout << ans << endl;
  
  return 0;
}
