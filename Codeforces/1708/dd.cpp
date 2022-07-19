//
//  dd.cpp
//  2022-07-17 18:37
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
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    int st = 0;
    for (int i = 0; i < n - 1; i++) {
      vector<int> temp;  
      for (int j = st; j < n; j++) {
        if (j == i) continue;
        temp.push_back(a[j] - a[j - 1]);
      }
      sort(temp.begin(), temp.end());
      int p = 0;
      for (int j = st; j < n; j++) {
        if (j == i) {
          a[j] = 0;
          continue;
        }
        a[j] = temp[p++];
      }
      while (a[st] == 0) st++;
    }
    cout << a[n - 1] << endl;
  }

  return 0;
}
