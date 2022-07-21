//
//  sj.cpp
//  2022-07-21 14:21
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
  ios::sync_with_stdio(false); 
  cin.tie(0);
  
  int z = 1; 
  cout << z << endl;
  while (z--) {
    int n = 2e3, q = 2e3 / 15; 
    cout << n << " " << q << endl;
    for (int i = 2; i <= n; i++) {
      cout << (i / 2) << " ";
    }
    cout << endl;

    mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<long long> U(1, n);


    for (int i = 1; i <= q; i++) {
      int a = 5, b = 5, c = 5; 
      cout << a << " " << b << " " << c << endl; 

      map<int, int> vis;
      for (int j = 1; j <= a; j++) {
        int x = U(rng);     
        while (vis[x]) x = U(rng);
        cout << x << " ";
        vis[x] = 1;
      }
      cout << endl;
      vis.clear();
      for (int j = 1; j <= b; j++) {
        int x = U(rng);     
        while (vis[x]) x = U(rng);
        cout << x << " ";
        vis[x] = 1;
      }
      cout << endl;

      vis.clear();
      for (int j = 1; j <= c; j++) {
        int x = U(rng);     
        while (vis[x]) x = U(rng);
        cout << x << " ";
        vis[x] = 1;
      }
      cout << endl;
    }
  }

  return 0;
}
