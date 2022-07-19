//
//  a.cpp
//  2022-07-15 21:27
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
    int n, k; cin >> n >> k;
    vector<int> a(n * 2 + 1); 
    for (int i = 1; i <= n * 2; i++) {
      cin >> a[i];   
    }
    sort(a.begin() + 1, a.end());
    int flag = true; 
    for (int i = 1; i <= n; i++) {
      if (a[i + n] >= a[i] + k) continue;
      flag = false;
    }
    if (flag) cout << "YES" << endl;
    else cout << "NO" << endl;
  }


  return 0;
}
