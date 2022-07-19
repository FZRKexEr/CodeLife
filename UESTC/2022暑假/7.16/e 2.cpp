//
//  e.cpp
//  2022-07-16 13:17
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

  int n; cin >> n;

  int limit = 1 << n;

  vector<int> a(limit), b(limit), c(limit);
  vector<int> cntb(limit, 0), cntc(limit, 0);
  for (int i = 0; i < (1ll << n); i++) {
    cin >> a[i];  
  }
  b = a;
  c = a;

  for (int i = 0; i <= 22; i++) {
    for (int j = 0; j < limit; j++) {
      int res1 = (j >> i & 1) ? b[j ^ (1 << i)] : -1;
      int res2 = b[j];
      if (res1 > res2) {
        b[j] = res1;
        cntb[j] = cntb[j ^ (1 << i)];
      } else if (res1 < res2) {
        b[j] = res2;
        cntb[j] = cntb[j];
      } else {
        b[j] = res1;
        cntb[j] = cntb[j ^ (1 << i)] + cntb[j];
      }
    }
  }

  for (int i = 0; i < limit; i++) {
    cout << b[i] << " ";
  }
  cout << endl; 

  for (int i = 0; i <= 22; i++) {
    for (int j = limit - 1; j >= 0; j--) {
      int res1 = !(j >> i & 1) ? c[j | (1 << i)] : -1;
      int res2 = c[j];
      if (res1 > res2) {
        c[j] = res1;
        cntc[j] = cntc[j | (1 << i)];
      } else if (res1 < res2) {
        c[j] = res2;
        cntc[j] = cntc[j]; 
      } else {
        c[j] = res2;
        cntc[j] = cntc[j | (1 << i)] + cntc[j];
      }
    }
  }

  int flag = false; 
  for (int i = 0; i < limit; i++) {
    int cnt = 0;
    if (b[i] == a[i]) cnt++;
    for (int j = 0; j < n; j++) {
      if (i >> j & 1) {
        if (a[i ^ (1 << j)] == b[i]) cnt++;  
      }
    }
    if (cnt == cntb[i]) continue;
    if (a[i] > b[i]) {
      flag = true;      
      for (int j = 0; j < limit; j++) {
        if ((i | j) == i && a[j] == b[i]) {
          int dif = i ^ j;    
          if (dif == (dif & -dif)) continue;
          int ansj = (dif - (dif & -dif)) | j;
          int ansi = (ansj ^ i) | j; 
          cout << ansi << " " << ansj << endl;
          break;
        }
      }
      break;
    }
  }
  if (!flag) cout << -1 << endl;

  return 0;
}
