//
//  sj.cpp
//  2022-07-12 18:48
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
   
  int n = 50, m = 50;
  cout << n << " " << m << endl;
  mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
  uniform_int_distribution<long long> U(0, 2);
  
  int limit = 10;
  int haso = 0;
    
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int res = U(rng);
      if (res == 2 && limit) {
        cout << "*";
        limit--;
      } else if (res == 2) {
        cout << ".";
      }
      if (res == 1) {
        cout << "#";
      } 
      if (res == 0) {
        if (haso == 0) {
          haso = 1;
          cout << "O";
        } else cout << ".";
      }
    }
    cout << endl;
  }

  return 0;
}
