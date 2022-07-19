//
//  1001.cpp
//  2022-07-19 18:35
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long

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

  void add(int u, int v, int val) {
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

struct DSU {
  vector<int> f, dep, size;   
  DSU(int n) : f(n + 1), dep(n + 1, 0), size(n + 1, 1) { iota(f.begin(), f.end(), 0); }

  inline int find(int x) {
    while (x != f[x]) x = f[x] = f[f[x]];
    return x;
  }

  inline bool merge(int x, int y) {
    x = find(x), y = find(y); 

    if (x == y) return false;
    if (dep[x] > dep[y]) swap(x, y);
    if (dep[x] == dep[y]) dep[y]++;

    f[x] = y;    
    size[y] += size[x];
    return true;
  }
};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int z; cin >> z;
  while (z--) {
    int n, m, q; cin >> n >> m >> q;
    vector<array<int, 3>> edges(m + 1);
    for (int i = 1; i <= m; i++) {
      cin >> edges[i][1] >> edges[i][2];  
      edges[i][0] = i;
    }
    sort(edges.begin() + 1, edges.end());

    DSU T1(n + 1);
    LCA T2(n + 1, 1);

    for (int i = 1; i <= m; i++) {
      if (T1.find(edges[i][1]) == T1.find(edges[i][2])) continue;  
      T1.merge(edges[i][1], edges[i][2]);
      T2.add(edges[i][1], edges[i][2], edges[i][0]); 
    }
    
    for (int i = 1; i <= n; i++) {
      
    }
  }

  return 0;
}
