//
//  e2.cpp
//  2022-04-24 23:14
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n; cin >> n; 
  string s; cin >> s;
  vector<int> f((1 << n) - 1);
  const int MOD = 998244353; 

  function <string(int)> dfs = [&] (int pos) {
    if (pos * 2 + 2 >= (int) f.size()) {
      f[pos] = 1;
      return (string) "" + s[pos];
    }
    string l = dfs(pos * 2 + 1);
    string r = dfs(pos * 2 + 2);
    if (l > r) swap(l, r);
    
    if (l == r) {
      f[pos] = f[pos * 2 + 1] * f[pos * 2 + 1] % MOD;
    } else {
      f[pos] = f[pos * 2 + 1] * f[pos * 2 + 2] % MOD * 2 % MOD;
    }
    return (string) "" + s[pos] + l + r;
  };

  dfs(0);
  cout << f[0];
   
  return 0;
}
