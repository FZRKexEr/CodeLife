//
//  c.cpp
//  2022-07-18 23:02
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
    vector<int> add(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 2; i < n; i++) {
      if (a[i] > max(a[i - 1], a[i + 1])) add[i] = 0;
      else {
        add[i] = max(a[i - 1], a[i + 1]) - a[i] + 1;
      }
    }
    if (n % 2) {
      int ans = 0;
      for (int i = 2; i < n; i++) {
        if (i % 2 == 0) ans += add[i]; 
      }
      cout << ans << endl;
    } else {
      int ans = 0x3f3f3f3f3f3f3f3f;
      vector<int> odd(n + 2, 0), even(n + 2, 0);
      for (int i = 1; i < n; i++) {
        even[i] = even[i - 1];
        if (i % 2 == 0) even[i] += add[i];
      }
      for (int i = n; i > 1; i--) {
        odd[i] = odd[i + 1];
        if (i % 2) odd[i] += add[i];
      }
      for (int i = 1; i < n; i++) {
        if (i % 2 == 0) continue;
        int res = even[i] + odd[i + 1]; 
        ans = min(ans, res);
      }
      cout << ans << endl;
    }
  }

  return 0;
}
