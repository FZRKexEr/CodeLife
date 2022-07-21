//
//  lsj.cpp
//  2022-07-21 12:42
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
   
  mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
  uniform_int_distribution<long long> U(1, 1000000ll);
  
  int z = 1;
  cout << z << endl;
  for (int i = 1; i <= z; i++) {
    cout << U(rng) << endl;  
  }

  return 0;
}
