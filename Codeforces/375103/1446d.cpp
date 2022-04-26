//
//  1446d.cpp
//  2022-04-26 15:38
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, m; cin >> n >> m; 
  string a, b; cin >> a >> b;
  vector<vector<int>> dp(n, vector<int> (m, 0));

  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i] == b[j]) {
        if (i && j) dp[i][j] = max(0ll, dp[i - 1][j - 1]) + 2;
        else dp[i][j] = 2;
      } else dp[i][j] = -2;
      if (j) dp[i][j] = max(dp[i][j - 1] - 1, dp[i][j]);
      if (i) dp[i][j] = max(dp[i - 1][j] - 1, dp[i][j]);
      ans = max(ans, dp[i][j]);
    }
  }
  cout << ans;
   
  return 0;
}
