//
//  l2.cpp
//  2022-05-11 23:20
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define LOCAL
using namespace std;

signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, w; cin >> n >> w;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i]; 
    a[i] -= i;
  }
  const int INF = 0x3f3f3f3f;
  vector<int> len(n + 1, INF);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int p = upper_bound(len.begin() + 1, len.end(), a[i]) - len.begin();
    len[p] = a[i]; 
    ans = max(ans, p);
  }
  cout << (n - ans) * w;
   
  return 0;
}
