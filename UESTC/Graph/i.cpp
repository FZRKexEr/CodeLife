//
//  i.cpp
//  2022-04-21 21:00
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

struct TwoSAT{
  vector<vector<int>> G; 
  vector<bool> vis;
  stack<int> stk;
  int n;

  TwoSAT(int _n) : G(_n * 2 + 2), vis(_n * 2 + 2, 0) { n = _n; }
 
  void addor(int a, bool at, int b, bool bt) {
    a += a + at;
    b += b + bt;
    G[a ^ 1].push_back(b); // !a -> b 
    G[b ^ 1].push_back(a); // !b -> a
  }

  bool dfs(int pos) {
    if (vis[pos ^ 1]) return false; 
    if (vis[pos]) return true;
    vis[pos] = 1;
    stk.push(pos);
    for (auto &v : G[pos]) {
      if (!dfs(v)) return false;
    }
    return true;
  }

  bool sol() {
    for (int i = 1; i <= n; i++) {
      if (!vis[i * 2 + 1] && !vis[i * 2]) {
        if (!dfs(i * 2)) {
          while (!stk.empty()) {
            vis[stk.top()] = 0;
            stk.pop();
          }
          if (!dfs(i * 2 + 1)) return false;
        }
      }
    }
    return true;
  }
};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, m; cin >> n >> m;

  TwoSAT T(n);
  for (int i = 1; i <= m; i++) {
    int u, x, v, y; cin >> u >> x >> v >> y;
    if (u == v) continue;
    T.addor(u, x, v, y);
  }
  if (T.sol()) {
    cout << "POSSIBLE" << endl;
    for (int i = 1; i <= n; i++) {
      if (T.vis[i * 2]) cout << 0 << " ";
      else cout << 1 << " ";
    }
  } else {
    cout << "IMPOSSIBLE" << endl;
  }
   
  return 0;
}
