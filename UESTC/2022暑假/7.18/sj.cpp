//
//  sj.cpp
//  2022-07-18 14:00
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
  freopen("in.txt", "w", stdout);
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int z = 1; cout << z << endl;

  mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

  for (int i = 1; i <= z; i++) {
    int n = 2e5; cout << n << endl; 
    vector<vector<int>> belong(n + 1);

    for (int i = 0; i < n; i++) {
      if (i * 2 + 1 < n) {
        belong[i * 2 + 1].push_back(i + 1);
      }
      if (i * 2 < n) {
        belong[i * 2].push_back(i + 1);
      }
    }
    for (int i = 0; i < n; i++) {
      cout << belong[i].size() << " ";
      for (auto &it : belong[i]) cout << it << " ";
      cout << endl;
    }
  }

  return 0;
}
