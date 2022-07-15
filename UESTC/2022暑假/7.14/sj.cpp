//
//  sj.cpp
//  2022-07-14 12:59
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
   
  int z = 2; 
  cout << z << endl;

  mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
  uniform_int_distribution<long long> U(1, 1000);
  
  while (z--) {
    int n = 10; 
    cout << n << endl;
    for (int i = 1; i<= n;i ++) {
      cout << U(rng) << " ";
    }
    cout << endl;
    uniform_int_distribution<long long> V(1, 1000);
    int p = V(rng), q = V(rng);
    while (p == q) {
      p = V(rng);
    }
    if (p < q) swap(p, q);
    cout << p << " " << q << endl;
  }

  return 0;
}
