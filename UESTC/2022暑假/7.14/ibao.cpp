//
//  ibao.cpp
//  2022-07-14 12:57
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
   
  int z; cin >> z; 
  while (z--) {
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n;j ++) {
        if ((a[i] ^ a[j]) == gcd(a[i], a[j])) ans++;
      }
    }
    cout << ans << endl;
  }

  return 0;
}
