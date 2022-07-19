//
//  P3960bao.cpp
//  2022-07-18 01:41
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
  freopen("in.txt", "r", stdin);
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int n, m, q;  
  cin >> n >> m >> q;
  vector<vector<int>> d(n + 1, vector<int> (m + 1)); 
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      d[i][j] = (i - 1) * m + j;
    }
  }
  for (int i = 1; i <= q; i++) {
    int x, y; cin >> x >> y;
    cout << d[x][y] << endl;
    for (int j = y; j < m; j++) {
      swap(d[x][j], d[x][j + 1]);
    }
    for (int j = x; j < n; j++) {
      swap(d[j][m], d[j + 1][m]);
    }
  }

  return 0;
}
