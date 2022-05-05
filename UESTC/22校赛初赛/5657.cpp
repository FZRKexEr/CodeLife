//
//  5657.cpp
//  2022-05-04 18:35
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int __int128
#define endl '\n'
#define LOCAL
using namespace std;

int gray(int pos) {
  int ans = 0;
  for (int i = 1; i <= 63; i++) {
    int base = (1llu << (i - 1));
    if (pos <= base) continue;

    int val = pos - base;
    if (((val - 1) / (base * 2)) % 2 == 0) {
      ans |= (1llu << (i - 1));
    }
  }
  return ans;
}

signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, m; 
  unsigned long long nn, mm; 
  cin >> nn >> mm;
  n = nn;
  m = mm;
  int val = gray(m + 1); 
  vector<long long> a;
  while (val) {
    if (val & 1) a.push_back(1);
    else a.push_back(0);
    val >>= 1;
  }
  reverse(a.begin(), a.end());
  for (auto &it : a) cout << it;
   
  return 0;
}

