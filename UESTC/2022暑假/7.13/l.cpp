//
//  l.cpp
//  2022-07-13 12:16
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

signed main() {
//  freopen("in.txt", "r", stdin);
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int z; cin >> z;
  while (z--) {
    int n, m, k; cin >> n >> m >> k;
    string s1, s2; cin >> s1 >> s2;
    int ans = 0;
    
    for (int i = -max(n, m); i <= max(n, m); i++) {
      int p = 0; 
      while (p + i < 0) p++;
      if (p + i >= m) break;
      queue<array<char, 2>> que;
      int diff = 0, size = 0;
      while (p + i < m && p < n) {
        que.push({s1[p], s2[p + i]});  
        size++;
        if (s1[p] != s2[p + i]) diff++;
        while (diff > k) {
          auto res = que.front();
          que.pop(); size--;
          if (res[0] != res[1]) diff--;
        }
        ans = max(ans, size);
        p++;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
