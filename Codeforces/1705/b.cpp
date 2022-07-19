//
//  b.cpp
//  2022-07-15 21:44
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
    int pos = -1;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      if (a[i] && pos == -1) pos = i;
    }
    if (pos == -1) {
      cout << 0 << endl;
    } else {
      int cnt = 0;
      for (int i = pos + 1; i < n; i++) {
        if (a[i] == 0) cnt++;
      }
      for (int i = 1; i <= n - 1; i++) cnt += a[i];
      cout << cnt << endl;
    }
  }

  return 0;
}
