//
//  cbao.cpp
//  2022-07-13 15:44
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
    vector<array<int, 2>> a(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i][0];
    }
    for (int i = 1; i <= n; i++) {
      cin >> a[i][1];
    }
    vector<int> dp(n + 1, 1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j < i; j++) {
        if (a[j][0] < a[i][0] && a[j][1] < a[i][1]) {
          if (i == 6) cout << j << endl;
          dp[i] = max(dp[i], dp[j] + 1);
        }
      }
      ans = max(dp[i], ans);
    }
    cout << ans << endl;
  }
  

  return 0;
}
