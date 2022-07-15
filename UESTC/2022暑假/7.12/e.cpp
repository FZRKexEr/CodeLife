//
//  e.cpp
//  2022-07-12 19:22
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long

signed main() {
//  freopen("in.txt", "r", stdin);
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int n, m; 
  cin >> n >> m; 
  vector<set<int>> G(n + 1);
  map<int, map<int, int>> edges; 
  for (int i = 1; i <= m; i++) {
    int u, v; cin >> u >> v;        
    if (edges[u][v]) continue;
    G[u].insert(v);
    G[v].insert(u);
    edges[u][v]++; edges[v][u]++;
  }
  queue<int> que; 
  for (int i = 1; i <= n; i++) {
    if (G[i].size() == 2) {
      que.push(i);
    }
  }
  int cnt = 0;
  vector<int> vis(n + 1, 0);
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    if (G[x].size() != 2) continue;

    if (vis[x]) continue;
    vis[x] = 1;

    cnt++;
    auto it = G[x].begin();
    int u = *it;
    it++;
    int v = *it; 

    G[x].clear();
    edges[u][x] = 0;
    edges[x][u] = 0;
    edges[x][v] = 0;
    edges[v][x] = 0;

    G[u].erase(x); 
    G[v].erase(x);
    if (edges[u][v] == 0) {
      edges[u][v] = 1;
      edges[v][u] = 1;
      G[u].insert(v);
      G[v].insert(u);
    }
    if (G[u].size() == 2) {
        que.push(u); 
    }
    if (G[v].size() == 2) {
      que.push(v);
    }
  }

  if (cnt == n - 2) cout << "Yes" << endl;
  else cout << "No" << endl;


  return 0;
}
