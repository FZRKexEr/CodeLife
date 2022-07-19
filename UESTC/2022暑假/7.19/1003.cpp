//
//  1003.cpp
//  2022-07-19 16:24
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  
  int z; cin >> z;
  while (z--) {
    int n, m; 
    cin >> n >> m;
    vector<array<int, 2>> a(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i][0] >> a[i][1];  
    }
    
    vector<bitset<1024>> dp[2];
    
    dp[0].resize(1 << 10);
    dp[1].resize(1 << 10);

    int o = 1;
    dp[0][0] = 1;

    for (int j = 1; j <= n; j++) {
      for (int i = 0; i < (1 << 10); i++) dp[o][i].reset();
      for (int i = 0; i < (1 << 10); i++) {
        auto res = dp[o ^ 1][i ^ a[j][1]] << (a[j][0]);
        dp[o][i] = dp[o ^ 1][i] | res;
      }
      if (j != n) o ^= 1;
    }
    
    int ans = -1;
    for (int i = 0; i < (1 << 10); i++) {
      if (dp[o][i][m] == 1) ans = max(ans, i);
    }
    cout << ans << endl;
  }

  return 0;
}
