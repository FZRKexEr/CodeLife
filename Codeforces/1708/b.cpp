//
//  b.cpp
//  2022-07-17 16:28
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
    int n, l, r; cin >> n >> l >> r;
    vector<int> a(n + 1);
    int flag = true;
    for (int i = 1; i <= n; i++) {
      a[i] = l / i * i;
      if (a[i] < l) a[i] += i;
      if (a[i] > r) flag = false;
    }
    if (!flag) {
      cout << "NO" << endl;
    } else {
      cout << "YES" << endl;
      for (int i = 1; i <= n; i++) {
        cout << a[i] << " ";
      }
      cout << endl;
    }
  }

  return 0;
}
