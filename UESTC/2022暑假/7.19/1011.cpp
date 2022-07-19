//
//  1011.cpp
//  2022-07-19 12:15
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
int power(int a, int b) {
  assert(b >= 0);
  int base = a, ans = 1;
  while (b) {
    if (b & 1) ans = ans * base % MOD;
    base = base * base % MOD;
    b >>= 1;
  }
  return ans;
}

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);

  int inv2 = power(2, MOD - 2);   

  int z; cin >> z; 
  while (z--) {
    int n, m; cin >> n >> m;
    cout << (n - m) * inv2 % MOD << endl;  
  }

  return 0;
}
