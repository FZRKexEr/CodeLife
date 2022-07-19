//
//  sj.cpp
//  2022-07-18 01:47
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
   
  int n = 3, m = 3, q = 5; 
  cout << n << " " << m << " " << q << endl;

  mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
  uniform_int_distribution<long long> U(1, 3);

  for (int i = 1; i <= q; i++) {
    cout << U(rng) << " " << U(rng) << endl;
  }
  

  return 0;
}
