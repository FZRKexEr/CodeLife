//
//  c.cpp
//  2022-07-15 21:48
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
    int n, c, q; cin >> n >> c >> q;
    string s; cin >> s;
    vector<array<int, 2>> opt(c + 1);  
    vector<int> sum(c + 2, 0);
    sum[0] = n;
    for (int i = 1; i <= c; i++) {
      cin >> opt[i][0] >> opt[i][1];  
      sum[i] = sum[i - 1] + opt[i][1] - opt[i][0] + 1;
    }
    function<char(int x)> ask = [&] (int pos) {
      if (pos <= sum[0]) return s[pos - 1];
      for (int i = 1; i <= c; i++) {
        if (sum[i] >= pos) {
          pos -= sum[i - 1];
          pos = pos + opt[i][0] - 1;
          return ask(pos);
        }
      }
      assert(0);
    };

    for (int i = 1; i <= q; i++) {
      int x; cin >> x;
      cout << ask(x) << endl;
    }
  }

  return 0;
}
