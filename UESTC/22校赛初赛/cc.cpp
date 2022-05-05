//
//  cc.cpp
//  2022-05-04 13:31
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define LOCAL
using namespace std;

signed main() {
//  freopen("in.txt", "r", stdin);
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, t; cin >> n >> t; 
  vector<int> a(n + 1, 0);
  vector<array<int, 3>> opt;
  for (int i = 1; i <= t; i++) {
    string s; cin >> s;
    if (s == "A") {
      int l, r, x;
      cin >> l >> r >> x;
      opt.push_back({l, r, x});
      for (int j = l; j <= r; j++) {
        a[j] += x;
      }
    }
    if (s == "B") {
      int x; cin >> x;
      int l = x, r = x;
      while (l >= 1 && a[l] == a[x]) l--;
      while (r <= n && a[r] == a[x]) r++;
      l++, r--;
      cout << l << " " << r << endl;
    }
    if (s == "C") {
      auto [l, r, x] = opt.back();   
      for (int j = l; j <= r; j++) {
        a[j] -= x;
      }
    }
  }
   
  return 0;
}
