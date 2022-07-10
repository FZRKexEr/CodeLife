//
//  I.cpp
//  2022-05-11 22:02
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

  int n; cin >> n;
  vector<int> a(n + 1);
  vector<int> sum(n + 1, 0);
  for (int i = 1; i <= n; i++) cin >> a[i];

  vector<vector<int>> f(n + 1, vector<int>(n + 1, -1)); 
  function<int(int, int)> get = [&] (int l, int r) {
    if (l == r) return a[l];
    if (f[l][r] != -1) return f[l][r];  
    f[l][r] = get(l, r - 1) ^ get(l + 1, r);
    return f[l][r];
  };

  vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0)); 
  for (int i = 1; i <= n; i++) {
    dp[i][i] = a[i];
    for (int j = i - 1; j >= 1; j--) {
      dp[j][i] = max(dp[j + 1][i], get(j, i)); 
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      dp[i][j] = max(dp[i][j], dp[i][j - 1]); 
    }
  }
  int q; cin >> q;
  for (int i = 1; i <= q; i++) {
    int l, r; cin >> l >> r;
    cout << dp[l][r] << endl;
  }
  
  return 0;
}
