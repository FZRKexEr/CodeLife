//
//  lbao.cpp
//  2022-07-21 12:38
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
//  freopen("in.txt", "r", stdin);
 // freopen("out1.txt", "w", stdout);
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int z; cin >> z;
  while (z--) {
    int n; 
    cin >> n;
    vector<int> dp(n + 1, 0x3f3f3f3f3f3f3f3fll);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
      if (i >= 7) dp[i] = min(dp[i - 7] + 1, dp[i]);
      if (i >= 31) dp[i] = min(dp[i - 31] + 1, dp[i]);
      if (i >= 365) dp[i] = min(dp[i - 365] + 1, dp[i]);
    }
    if (dp[n] != 0x3f3f3f3f3f3f3f3fll) 
      cout << dp[n] << endl;
    else cout << -1 << endl;
  }

  return 0;
}
