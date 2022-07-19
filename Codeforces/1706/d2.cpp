//
//  d2.cpp
//  2022-07-18 23:23
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif


signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int z; cin >> z;
  while (z--) {
    int n, k; cin >> n >> k;
    vector<int> a(n + 1);
    int maxn = 0; 
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      maxn = max(maxn, a[i]); 
    }
    vector<int> b(maxn + 2, 0);
    for (int i = 1; i <= n; i++) {
      int last = 0x3f3f3f3f; 
      for (int j = 1, nxt; j <= min(k, a[i]); j = nxt) {
        nxt = a[i] / (a[i] / j) + 1;
        int val = a[i] / j; 
        b[val + 1] = max(last, b[val + 1]); 
        last = val;
      }
      b[0] = max(b[0], last);
    }
    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= maxn; i++) {
      if (i != 0)
        b[i] = max(b[i - 1], b[i]);      
      ans = min(b[i] - i, ans);
    }
    cout << ans << endl;
  }


  return 0;
}
