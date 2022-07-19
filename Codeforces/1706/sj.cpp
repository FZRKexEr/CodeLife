//
//  sj.cpp
//  2022-07-19 22:33
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long
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
   
  mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

  int z; 
  z = 1; 
  cout << z << endl;
  for (int i = 1; i <= z; i++) {
    int n = 5;
    uniform_int_distribution<long long> U(1, n), V(n - 1, n + 2);

    DSU T(n);
    map<int, map<int, int>> con;
    
    int cnt = n;
    vector<array<int, 2>> edges;
    
    while (cnt != 1) {
      int u = U(rng), v = U(rng);
      while (con[u][v] || u == v) {
        u = U(rng);
        v = U(rng);
      }
      con[u][v] = con[v][u] = 1;  
      edges.push_back({u, v});
      if (T.find(u) != T.find(v))
        T.merge(u, v), cnt--;
    }
    int q = n;
    cout << n << " " << edges.size() << " " << q << endl;
    for (auto &it : edges) cout << it[0] << " " << it[1] << endl;
    for (int i = 1; i <= q; i++) {
      cout << i << " " << n << endl;
    }
  }


  return 0;
}
