//
//  a.cpp
//  2022-07-20 20:36
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
    int l = 0, r = 1e9;
    while (l <= r) {
      int mid = (l + r) >> 1;

      if (check()) l = mid + 1;
      else r = mid - 1;
    }
    
  }

  return 0;
}
