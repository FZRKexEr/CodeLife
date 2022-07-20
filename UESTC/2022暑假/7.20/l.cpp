//
//  l.cpp
//  2022-07-20 12:31
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int z; cin >> z; 
  while (z--) {
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];  
    }
    double res1 = 0;
    double res2 = 0;
    for (int i = 1; i <= n; i++) {
      if (res2 < 100.0) {
        res2 += a[i] * 1.0;
      } else if (res2 >= 100.0 && res2 < 200.0) {
        res2 += a[i] * 0.8;
      } else {
        res2 += a[i] * 0.5;
      }

      if (res1 < 100.0) {
        if (a[i] * 1.0 + res1 <= 100.0) {
          res1 = res1 + a[i] * 1.0;
        } else {
          if (100.0 + (a[i] - (100.0 - res1) / 1.0) * 0.8 <= 200.0)
            res1 = 100.0 + (a[i] - (100.0 - res1) / 1.0) * 0.8;
          else {
            res1 = 200.0 + (a[i] - (100.0 - res1) / 1.0 - 100.0 / 0.8) * 0.5;
          }
        }
      } else if (res1 >= 100.0 && res1 < 200.0) {
        if (a[i] * 0.8 + res1 <= 200.0) {
          res1 = res1 + a[i] * 0.8;
        } else {
          res1 = 200.0 + (a[i] - (200.0 - res1) / 0.8) * 0.5;
        }
      } else {
        res1 += a[i] * 0.5;
      }
    }
    cout << fixed << setprecision(3) << res1 << " " << res2 << endl;
  }

  return 0;
}
