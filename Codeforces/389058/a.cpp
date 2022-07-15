//
//  a.cpp
//  2022-07-10 15:23
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define LOCAL
using namespace std;

#ifdef ONLINE_JUDGE
#ifndef LOCAL_TEST
#pragma GCC optimize("O3","unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif
#endif
// 回滚并查集
// 1. 操作的两个数 >= 0
// 2. rollback 回滚到第 t 次操作，注意一次合并有两次操作
struct DSU {
  vector<int> f, size;   
  vector<array<int, 2>> ops;
  DSU(int n) : f(n + 1), size(n + 1, 1) { iota(f.begin(), f.end(), 0); }

  inline int find(int x) {
    while (x != f[x]) x = f[f[x]];
    return x;
  }

  inline bool merge(int x, int y) {
    x = find(x), y = find(y); 
    if (x == y) return false;
    if (size[x] > size[y]) swap(x, y);
    ops.push_back({x, f[x]});
    f[x] = y;    
    ops.push_back({~y, size[y]});
    size[y] += size[x];
    return true;
  }

  void rollback(int t) {
    while ((int) ops.size() > t) {
      assert(ops.size());
      auto [i, j] = ops.back();
      ops.pop_back();
      if (i >= 0) {
        f[i] = j;
      } else {
        size[~i] = j;
      }
    }
  }
};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  
  int n, m; cin >> n >> m; 
  int cnt = 0;

  vector<array<int, 3>> edges(m + 1); 
  vector<vector<array<int, 3>>> add(500000 + 1);
  for (int i = 1; i <= m; i++) {
    cnt++;
    cin >> edges[i][1] >> edges[i][2] >> edges[i][0];
    add[edges[i][0]].push_back(edges[i]);
  }
  
  int q; cin >> q;
  
  vector<map<int, vector<int>>> belong(500000 + 1);
  for (int i = 1; i <= q; i++) {
    cnt++;
    int k; cin >> k;
    for (int j = 1; j <= k; j++) {
      cnt++;
      int ord; cin >> ord;
      belong[edges[ord][0]][i].push_back(ord);
    }
  }

  DSU T(n + 1);
  vector<int> ans(q + 1, 1);

  for (int i = 1; i <= 500000; i++) {
    cnt++;
    int backup = (int) T.ops.size();
     
    for (auto &it : belong[i]) {
      cnt++;
      T.rollback(backup);
      int o = it.first;
      for (auto &jt : it.second) {
        cnt++;
        auto [w, u, v] = edges[jt];
        if (T.find(u) == T.find(v)) ans[o] = false;   
        else {
          T.merge(u, v);
        }
      }
    }
    T.rollback(backup);
    for (auto &it : add[i]) {
      cnt++;
      auto [w, u, v] = it;
      if (T.find(u) == T.find(v)) continue;
      T.merge(u, v);
    }
  }

  for (int i = 1; i <= q; i++) {
    cnt++;
    if (ans[i]) cout << "YES" << endl;
    else cout << "NO" << endl;
  }
  return 0;
}
