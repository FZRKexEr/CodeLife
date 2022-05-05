//
//  c.cpp
//  2022-04-30 23:03
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int limit = 40000;  
  vector<int> prec;
  for (int i = 1; i <= limit; i++) {
    string s = to_string(i);
    string t = to_string(i);
    reverse(t.begin(), t.end());
    if (s == t) prec.push_back(i);
  }
  vector<vector<int>> dp(limit + 1, vector<int> (prec.size(), 0));
  for (int i = 0; i < (int) prec.size(); i++) {
    dp[0][i] = 1;
  }
  const int MOD = 1e9 + 7;
  vector<int> ans(limit + 1, 0);
  for (int i = 1; i <= limit; i++) {
    for (int j = 0; j < (int) prec.size(); j++) {
      if (i - prec[j] < 0) {
        if (j) dp[i][j] = dp[i][j - 1];
        continue;
      }
      dp[i][j] += dp[i - prec[j]][j];
      dp[i][j] %= MOD;
      if (j) (dp[i][j] += dp[i][j - 1]) %= MOD;
    }
    ans[i] = dp[i][(int) prec.size() - 1] % MOD;
  }
  int z; cin >> z; 
  
  while (z--) {
    int n; cin >> n;
    cout << ans[n] << endl;
  }
  return 0;
}
