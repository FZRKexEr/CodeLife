//
//  x.cpp
//  2022-05-09 20:16
//
//  Created by liznb
//  

#include <bits/stdc++.h>
//#define int long long
#define endl '\n'
using namespace std;

void file() {
#ifndef ONLINE_JUDGE
  freopen("test/2.in", "r", stdin);
  // freopen("out.txt", "w", stdout);
#endif
}

signed main() {
//  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n; cin >> n; 
  int s; cin >> s;
  vector<vector<array<int, 2>>> G(n + 1);
  for (int i = 1; i <= n - 1; i++) {
    int u, v, w; cin >> u >> v >> w;
    G[u].push_back({w, v});
    G[v].push_back({w, u});
    assert(u != v);
    assert(u <= n && u >= 1);
    assert(v <= n && v >= 1);
  }
  assert(s <= n && s >= 1);
  long long ans = 0;
  vector<int> maxn(n + 1, 0);
  function<void(int, int)> dfs = [&] (int pos, int fa) {
    for (int i = 0; i < (int) G[pos].size(); i++) {
      auto [w, v] = G[pos][i];
      if (v == fa) continue;
      dfs(v, pos);   
      maxn[pos] = max(maxn[v] + w, maxn[pos]); 
    }
    for (int i = 0; i < (int) G[pos].size(); i++) {
      auto [w, v] = G[pos][i];
      if (v == fa) continue;
      ans += maxn[pos] - maxn[v] - w;
    }
  };
  dfs(s, -1);
  cout << ans << endl;
  return 0;
}
