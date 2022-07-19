//
//  d.cpp
//  2022-07-18 19:49
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
    double r, x, y, d; cin >> r >> x >> y >> d;
    double dis = sqrt(x * x + y * y);
    double a1 = acos((dis - d) / r); 
    double a2 = acos((dis + d) / r);
    cout << fixed << setprecision(12) << (a1 - a2) * r << endl; 
  }

  return 0;
}
