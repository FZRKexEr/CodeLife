//
//  b.cpp
//  2022-07-21 12:00
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
    string s; cin >> s;
    string ans;
    for (auto &it : s) {
      if (it <= 'z' && it >= 'a') continue;
      if (it == ':') continue;
      if (it == '_') continue;
      ans += it;
    }
    cout << ans << endl;
  }

  return 0;
}
