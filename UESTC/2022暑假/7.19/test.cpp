//
//  test.cpp
//  2022-07-19 16:04
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long

struct Hash {
  array<int, 2> MOD;
  array<int, 2> P;

  int n;
  string s; // 0 - indexed
  vector<array<int, 2>> hs; // 1 - indexed
  vector<array<int, 2>> pw; // 0 - indexed

  Hash(string _s) {
    
    MOD = {127657753, 987654319};
    P = {137, 277};

    assert(_s.length());
    n = _s.length(); 
    s = _s; 
    hs.resize(n + 1);
    pw.resize(n + 1);
    
    pw[0] = {1, 1};
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < 2; j++) {
        pw[i][j] = 1ll * pw[i - 1][j] * P[j] % MOD[j];
      }
    }
    hs.resize(n + 1, {0, 0}); 
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 2; j++) {
        hs[i + 1][j] = (1ll * hs[i][j] * P[j] % MOD[j] + s[i]) % MOD[j];
      }
    }
  }

  void add(string _s) {
    assert(_s.length());
    int old_n = n;
    n += _s.length(); 
    s += _s;
    hs.resize(n + 1);
    pw.resize(n + 1);
    for (int i = old_n + 1; i <= n; i++) {
      for (int j = 0; j < 2; j++) {
        pw[i][j] = 1ll * pw[i - 1][j] * P[j] % MOD[j];
      }
    }
    hs.resize(n + 1, {0, 0}); 
    for (int i = old_n; i < n; i++) {
      for (int j = 0; j < 2; j++) {
        hs[i + 1][j] = (1ll * hs[i][j] * P[j] % MOD[j] + s[i]) % MOD[j];
      }
    }
  }

  array<int, 2> get_hash(int l, int r) { // 1 - indexed
    assert(1 <= l && l <= r && r <= n); 
    array<int, 2> ans;
    for (int i = 0; i < 2; i++) {
      ans[i] = (hs[r][i] - 1ll * hs[l - 1][i] * pw[r - l + 1][i] % MOD[i] + MOD[i]) % MOD[i];
    }
    return ans;
  }
};
signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
   

  return 0;
}
