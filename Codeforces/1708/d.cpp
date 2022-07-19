//
//  d.cpp
//  2022-07-17 17:48
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
    vector<int> a(n);
    multiset<int> que; 
    int cnt = 0;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      if (i >= 1 && a[i] - a[i - 1] == 0) cnt++; 
    }

    a.erase(unique(a.begin(), a.end()), a.end()); 

    for (int i = 1; i < (int) a.size(); i++) {
      que.insert(a[i] - a[i - 1]);
    }

    while (que.size() != 1 && !que.empty()) {
      vector<int> b;
      for (auto &it : que) b.push_back(it);
      que.clear();
      int add = 0;
      for (int i = 1; i < (int) b.size(); i++) {
        if (b[i] - b[i - 1] == 0) add++;
      }
      b.erase(unique(b.begin(), b.end()), b.end());
      for (int i = 1; i < (int) b.size(); i++) {
        que.insert(b[i] - b[i - 1]);
      }
      if (cnt) {
        que.insert(b[0]);
        cnt--;
      }
      cnt += add;
    }

    if (que.empty()) cout << 0 << endl;
    else {
      auto it = que.begin();
      cout << *it << endl;
    }
  }

  return 0;
}
