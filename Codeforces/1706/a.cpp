//
//  a.cpp
//  2022-07-18 22:38
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
    int n, m; cin >> n >> m;
    vector<int> a(n + 1);
    string s;
    for (int i = 1; i <= m; i++) s += 'B';
    for (int i = 1; i <= n;i ++) {
      cin >> a[i];
      int p1 =a[i] - 1; 
      int p2 = m + 1 - a[i] - 1; 
      if (p1 > p2) swap(p1, p2);

      if (s[p1] == 'B') s[p1] = 'A';
      else {
        if (s[p2] == 'B') s[p2] = 'A';
      }
    }
    cout << s << endl;
  }

  return 0;
}
