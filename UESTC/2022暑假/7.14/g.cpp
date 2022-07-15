//
//  g.cpp
//  2022-07-14 14:39
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long

const int MOD = 1e9 + 7;
int calc(int n, int k) {
  vector<int> c(n + 1, 0);
  c[1] = k % MOD;
  c[2] = k * (k - 1) % MOD;
  for (int i = 3; i <= n; i++) {
    c[i] = (c[i - 1] * (k - 1) % MOD + c[i - 2] * (k - 1) % MOD) % MOD;
  }
  return c[n];
}

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
   

  return 0;
}
