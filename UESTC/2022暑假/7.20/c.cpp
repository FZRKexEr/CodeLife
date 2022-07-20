//
//  c.cpp
//  2022-07-20 15:03
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long

const int INF = 0x3f3f3f3f3f3f3f3f;

struct Dijkstra {
  struct Edge {
    int w, v;

    Edge(int a, int b) : w(a), v(b) {}
    bool operator < (const Edge &oth) const {
      if (w != oth.w) return w > oth.w;
      return v > oth.v;
    }
  };
  
  vector<vector<Edge>> G; 
  vector<int> d;
  
  Dijkstra(int n) : G(n + 1), d(n + 1, INF) {}

  void add(int u, int v, int w) {  // 有向边
    G[u].push_back({w, v}); // (距离, 序号) w 在前!
  }
  
  void solve(int s) {
    d[s] = 0;
    set<Edge> que; // (距离, 序号) 

    for (int i = 0; i < (int)d.size(); i++) {
      que.insert({d[i], i}); // (距离, 序号) 
    }
    
    while (que.empty() == false) {
      int x = que.begin()->v;
      que.erase(que.begin());

      for (auto &it : G[x]) {
        int v = it.v, w = it.w;

        if (d[v] < d[x] + w) {
          que.erase({d[v], v}); // (距离, 序号) 
          d[v] = d[x] + w;
          que.insert({d[v], v});
        }
      }
    }
  }
};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int n, s; cin >> n >> s; 
  for (int i = 1;  i <= n; i++) {
    
  }

  return 0;
}
