//
//  e.cpp
//  2022-05-02 23:01
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define LOCAL
using namespace std;

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  
  int n; cin >> n; 
  vector<int> a(n);
  for (auto &it : a) cin >> it;
  const int INF = 0x3f3f3f3f;
  int ans = INF;

  // 两个不相交
  vector<int> b(n);
  for (int i = 0; i < n; i++) {
    b[i] = (a[i] + 1) / 2; 
  }
  sort(b.begin(), b.end());
  ans = min(ans, b[0] + b[1]);

  // 两个相邻
  for (int i = 0; i < n - 1; i++) {
    ans = min(ans, max({(int) ceil((a[i] + a[i + 1]) * 1.0 / 3), (a[i] + 1) / 2, (a[i + 1] + 1) / 2}));
  }

  // 两个相间
  for (int i = 0; i < n - 2; i++) {
    ans = min(ans, 1 + a[i] / 2 + a[i + 2] / 2);
  }
  
  cout << ans;

  return 0;
}
