//
//  bsj.cpp
//  2022-07-13 13:23
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
  int limit = 20;
  for (int i = 1; i <= z; i++) {
    int n = limit;
    cout << n << endl;
    vector<int> a(n), res;
    iota(a.begin(), a.end(), 1); 

    for (int i = 1; i < (1ll << limit); i++) {
      int sum = 0;
      for (int j = 0; j < limit; j++) {
        if (i >> j & 1) sum += a[j]; 
      }
      res.push_back(sum);
    }
    assert((int) res.size() == (1ll << n) - 1);
    for (int j = 0; j < (int) res.size(); j++) {
      cout << res[j] << " ";
    }
    cout << endl;
  }

  return 0;
}
