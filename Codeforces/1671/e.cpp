//
//  e.cpp
//  2022-04-22 23:11
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define LOCAL
using namespace std;

void file() {
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
#endif
}
const int MOD = 998244353;

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  int n; cin >> n;
  string s; cin >> s;

  vector<int> f(1 << n, 0);
  int ans = 1;
  function<string(int)> dfs = [&](int pos) {
    if (pos * 2 + 1 >= (1 << n)) {
      return (string)"" + s[pos - 1];
    }
    auto l = dfs(pos * 2);
    auto r = dfs(pos * 2 + 1);
    if (l != r) (ans *= 2) %= MOD;
    if (l > r) swap(l, r);
    return (string)"" + s[pos - 1] + l + r;
  };

  dfs(1);  
  cout << ans << endl;
  return 0;
}
