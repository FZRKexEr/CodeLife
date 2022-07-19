//
//  b.cpp
//  2022-07-18 22:49
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
    vector<int> last(n + 1, 0);
    vector<int> ans(n + 1, 0), res(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      if (last[a[i]] == 0) {
        res[a[i]] = 1;
        ans[a[i]] = max(res[a[i]], ans[a[i]]);
        last[a[i]] = i;
      } else if (abs(last[a[i]] - i) % 2) {
        res[a[i]] += 1;
        ans[a[i]] = max(res[a[i]], ans[a[i]]);
        last[a[i]] = i;
      } 
    }
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << " ";
    }
    cout << endl;
  }

  return 0;
}
