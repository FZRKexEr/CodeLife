//
//  g.cpp
//  2022-05-03 00:05
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define LOCAL
using namespace std;

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, m; cin >> n >> m;
  vector<vector<int>> G(n + 1);
  vector<int> in(n + 1, 0);
  for (int i = 1; i <= m; i++) {
    int u, v; cin >> u >> v;
    G[u].push_back(v); 
    in[v]++;
  }
  vector<int> dp(n + 1, 0);
  function<int(int)> dfs = [&] (int pos) {
    if (dp[pos]) return dp[pos];
    if (G[pos].size() <= 1) return dp[pos] = 1ll;
    int ans = 1;
    for (auto &v : G[pos]) {
      if (in[v] == 1) ans = max(ans, 1ll);
      else ans = max(ans, dfs(v) + 1);
    }
    return dp[pos] = ans;
  };
  int ans = 1;
  for (int i = 1; i <= n; i++) {
    ans = max(ans, dfs(i));
  }
  cout << ans;
  return 0;
}
