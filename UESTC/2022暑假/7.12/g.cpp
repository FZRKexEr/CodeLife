//
//  g.cpp
//  2022-07-12 20:42
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long

const int N = 250000 + 10;

int f[N][4][10][10];

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int n, k; cin >> n >> k;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];     
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 9; j++) {
      for (int k = 1; k <= 9; k++) {
        // sta = 0 => 01 
        f[i + 1][1][j][k] = min(f[i + 1][1][j][k], f[i][0][j][k] + a[i]);
        f[i + 1][1][j - 1][k + 1] = min(f[i + 1][1][j - 1][k + 1], f[i][0][j][k]);

        // sta = 1 => 3 or 2
        f[i + 1][3][j][k] = min(f[i + 1][3][j][k], f[i][1][j][k] + a[i]);
        f[i + 1][3][j + 1][k] = min(f[i + 1][3][j + 1][k], f[i][1][j][k] + a[i]);
        f[i + 1][3][j - 1][k + 1] = min(f[i + 1][3][j - 1][k + 1], f[i][1][j][k]);
        f[i + 1][3][j][k + 1] = min(f[i + 1][3][j][k + 1], f[i][1][j][k]);
        f[i + 1][2][j][k] = min(f[i + 1][2][j][k], f[i][1][j][k]);
        
        // sta = 2 => 1 or 0
        f[i + 1][1][j][k] = min(f[i + 1][1][j][k], f[i][2][j][k] + a[i]);
        f[i + 1][1][j + 1][k] = min(f[i + 1][1][j + 1][k], f[i][2][j][k] + a[i]);
        f[i + 1][1][j - 1][k] = min(f[i + 1][1][j - 1][k], f[i][2][j][k]);
        f[i + 1][1][j][k] = min(f[i + 1][1][j][k], f[i][1][j][k]);
        f[i + 1][0][j][k] = min(f[i + 1][0][j][k], f[i][1][j][k]);
        
        // 
      }
    }
  }

  return 0;
}
