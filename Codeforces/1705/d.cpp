//
//  d.cpp
//  2022-07-15 22:01
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
    string s, t; cin >> s >> t;
    int flag = true;
    
    if (s[0] != t[0]) {
      flag = false;
    }
    if (s.back() != t.back()) {
      flag = false;
    }

    if (!flag) {
      cout << -1 << endl;
      continue;
    }

    int cnt0 = 1, cnt1 = 1; 
    vector<array<int, 2>> res0, res1; 
    for (int i = 1; i < n; i++) {
      if (s[i] != s[i - 1]) {
        cnt0++;
        if (res0.size() == 0) res0.push_back({0, i - 1});
        else res0.push_back({res0.back()[1] + 1, i - 1});
      }
    }

    if (res0.size() == 0) res0.push_back({0, n - 1});
    else res0.push_back({res0.back()[1] + 1, n - 1});

    for (int i = 1; i < n; i++) {
      if (t[i] != t[i - 1]) {
        cnt1++;
        if (res1.size() == 0) res1.push_back({0, i - 1});
        else res1.push_back({res1.back()[1] + 1, i - 1});
      }
    }

    if (res1.size() == 0) res1.push_back({0, n - 1});
    else res1.push_back({res1.back()[1] + 1, n - 1});

    if (cnt0 != cnt1) flag = false;
    if (!flag) {
      cout << -1 << endl;
      continue;
    }

    int ans0 = 0, ans1 = 0;

    for (int i = 0; i < (int) res0.size(); i += 2) {
      ans0 += abs(res0[i][0] - res1[i][0]) + abs(res0[i][1] - res1[i][1]); 
    }
    for (int i = 1; i < (int) res0.size(); i += 2) {
      ans1 += abs(res0[i][0] - res1[i][0]) + abs(res0[i][1] - res1[i][1]); 
    }
  
    cout << min(ans0, ans1) << endl;
  }

  return 0;
}
