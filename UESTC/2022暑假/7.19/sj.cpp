//
//  sj.cpp
//  2022-07-19 14:41
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
  uniform_int_distribution<long long> U('a', 'z');
  uniform_int_distribution<long long> V(1, 10);


  int z = 10;
  cout << z << endl;
  while (z--) {
    string s;   
    int n = 100;
    for (int i = 1; i <= n; i++) {
      s += (char) U(rng);
    }
    cout << s << endl;
    int k = V(rng);
    cout << k << endl;
  }

  return 0;
}
