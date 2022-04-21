//
//  k.cpp
//  2022-04-21 18:47
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define LOCAL
using namespace std;


struct LCA {
  vector<vector<int>> G, p;
  vector<int> d;
  int n, s; 

  LCA(int _n, int _s) : G(_n + 1), d(_n + 1, 1), n(_n), s(_s) {
    p.resize(_n + 1);
    int level = 0;
    while ((1 << level) <= _n) level++;
    for (int i = 0; i <= _n; i++) {
      p[i].resize(level + 1);
    }
  }

  int flag = false;

  void add(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
  }
  
  void dfs(int pos, int fa) {
    p[pos][0] = fa;
    for (auto &v : G[pos]) {
      if (v == fa) continue;
      d[v] = d[pos] + 1;
      dfs(v, pos);
    }
  }

  void init() {
    flag = true; 
    dfs(s, s); 
    for (int level = 1; (1 << level) <= n; level++) {
      for (int i = 1; i <= n; i++) {
        p[i][level] = p[p[i][level - 1]][level - 1];
      }
    }
  }

  int lca(int a, int b) {
    assert(flag);
    if (d[a] < d[b]) swap(a, b); 
    int i, j;
    for (i = 0; (1 << i) <= d[a]; i++);  
    i--; 
    for (j = i; j >= 0; j--) {
      if (d[a] - (1 << j) >= d[b]) {
        a = p[a][j];
      }
    }
    if (a == b) return b; 
    for (j = i; j >= 0; j--) {
      if (p[a][j] != p[b][j]) {
        a = p[a][j];
        b = p[b][j];
      }
    }
    return p[a][0];
  }
};

signed main() {

  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, m; cin >> n >> m;

  LCA T(n, 1);

  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    T.add(u, v);
  }
  T.init(); 
  for (int i = 1; i <= m; i++) {
    int a, b; cin >> a >> b;
    int lca = T.lca(a, b);
    cout << T.d[a] + T.d[b] - T.d[lca] * 2 << endl;
  }
  return 0;
}
