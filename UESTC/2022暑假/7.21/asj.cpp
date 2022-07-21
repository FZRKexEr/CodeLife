//
//  asj.cpp
//  2022-07-21 14:02
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
   
  int n = 2e5; 
  cout << n << endl;

  mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
  uniform_int_distribution<long long> U(1, 4);
  uniform_int_distribution<long long> LR(1, 1000000);

  for (int i = 1; i <= n; i++) {
    int k = U(rng), l = LR(rng), r = LR(rng); 
    if (l > r) swap(l, r);
    cout << k << " " << l << " " << r << endl;
  }

  return 0;
}
