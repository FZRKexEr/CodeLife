//
//  g.cpp
//  2022-07-18 12:04
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
   
  string n; cin >> n; 
  string res2;

  for (int i = 0; i < (int) n.length() - 1; i++) {
    res2 += "9";
  }

  cout << max(res2, n);

  return 0;
}
