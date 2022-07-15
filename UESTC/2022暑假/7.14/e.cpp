//
//  e.cpp
//  2022-07-14 16:42
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define LOCAL
#define int long long
#define double long double


double min(double a, double b) {
  if (a < b) return a;
  return b;
}

double max(double a, double b) {
  if (a > b) return a;
  return b;
}

signed main() {
  int z; cin >> z; 

  auto calc = [&](int x, int y, int C) {
    double a = -1.0 * 5 * x * x, b = 1.0 * C * C * x, c = -1.0 * (5.0 * x * x + 1.0 * C * C * y);
    double delta = 1.0 * b * b - 4.0 * a * c;
    array<double, 2> ans;
    double x1 = (-b + sqrt(delta)) * 1.0 / (2.0 * a);
    double x2 = (-b - sqrt(delta)) * 1.0 / (2.0 * a);
    ans[0] = min(x1, x2);
    ans[1] = max(x1, x2);
    return ans;
  };

  while (z--) {
    int c, n; cin >> c >> n;
    array<double, 2> ans;
   
    auto merge = [&] (array<double, 2> a, array<double, 2> b) {
      return (array<double, 2>) {max(a[0], b[0]), min(a[1], b[1])};
    };

    for (int i = 1; i <= n; i++) {
      int x, y; cin >> x >> y;
      auto res = calc(x, y, c);
      if (i == 1) ans = res;
      else ans = merge(ans, res);
    }
    assert(ans[0] < ans[1]);
    printf("%.3Lf\n", (ans[0] + ans[1]) / 2.0);
  }

  return 0;
}
