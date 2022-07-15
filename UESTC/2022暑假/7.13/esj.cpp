//
//  esj.cpp
//  2022-07-13 16:16
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
   
  int z = 20;  
  cout << z << endl;

  while (z--) {
    int n = 1 << 13, k = 13;
    cout << n << " " << k << endl;
    mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<long long> U(0, 1);

    for (int i = 1; i <= n; i++) {
      for (int k = 1; k <= 13; k++) {
        cout << U(rng);
      }
      cout << endl;
    }
  }

  return 0;
}
