//
//  a.cpp
//  2022-07-17 16:24
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
    int flag = true;
    for (int i = 2; i <= n; i++) {
      if (a[i] % a[1]) flag = false;
    }
    if (flag) cout << "YES" << endl;
    else cout << "NO" << endl;
  }


  return 0;
}
