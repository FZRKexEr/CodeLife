//
//  i.cpp
//  2022-07-12 13:04
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
   
  vector<int> f(5004, -1);

  f[0] = f[1] = 0;
  
  function<int(int)> sol = [&](int x) {
    if (f[x] != -1) return f[x];
    vector<int> a;
    for (int i = 0; i <= x - 2; i++) {
      int l = i, r = x - 2 - i;
      a.push_back(sol(l) ^ sol(r));
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    f[x] = a.size();
    for (int i = 0; i < (int) a.size(); i++) {
      if (a[i] != i) {
        f[x] = i;
        break;
      }
    }
    return f[x];
  };
 
  int n; cin >> n;
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    if (sol(x) == 0) cout << "Second" << endl;
    else cout << "First" << endl;
  }
  

  return 0;
}
