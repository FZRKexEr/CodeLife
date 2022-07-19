//
//  c.cpp
//  2022-07-17 16:31
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
    int n, limit; cin >> n >> limit;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    string s;
    int q = 0;
    for (int i = n; i >= 1; i--) {
      if (a[i] <= q) s += '1';
      else {
        if (q != limit) {
          q += 1;
          s += '1';
        } else s += '0';
      }
    }

    reverse(s.begin(), s.end());
    cout << s << endl;
  }

  return 0;
}
