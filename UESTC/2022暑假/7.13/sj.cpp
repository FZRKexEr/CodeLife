//
//  sj.cpp
//  2022-07-13 12:25
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
  freopen("in.txt", "w", stdout);
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z = 10;
  cout << z << endl;
  
  mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
  uniform_int_distribution<long long> U(1, 1000000000);

  while (z--) {
    int n = 200000;
    cout << n << endl;
    for (int i = 1; i <= n; i++) {
      cout << U(rng) << " ";
    }
    cout << endl;
    for (int i = 1; i <= n; i++) {
      cout << U(rng) << " ";
    }
    cout << endl;
  }

  return 0;
}
