//
//  test.cpp
//  2022-07-19 23:04
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
    cout << a << endl;
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
   
  LCA T(5, 1);   
  T.add(3, 2);
  T.add(4, 3);
  T.add(3, 5);
  T.add(2, 1);
  T.init();
  cout << T.lca(4, 5);

  return 0;
}
