//
//  c.cpp
//  2022-07-21 19:13
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
   
  int n; cin >> n; 
  vector<int> a(n + 1); 

  int g = 0;
  int maxn = 0;

  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    maxn = max(a[i], maxn);
    g = gcd(g, a[i]);
  }

  if ((maxn / g - n) % 2) cout << "Alice";
  else cout << "Bob"; 

  return 0;
}
