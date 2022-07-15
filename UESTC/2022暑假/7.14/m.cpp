//
//  m.cpp
//  2022-07-14 13:57
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
//  freopen("test/6.in", "r", stdin);
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int z; cin >> z; 
  while (z--) {
    int n; cin >> n;
    vector<array<int, 2>> arr(n);
    for (int i = 1; i <= n; i++) {
      cin >> arr[i - 1][0];
      arr[i - 1][1] = i;
    }

    sort(arr.begin(), arr.end());
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = arr[i][0];
    
    vector<int> sum(n);

    sum[0] = a[0];
    for (int i = 1; i < n; i++) {
      sum[i] = sum[i - 1] + a[i];
    }

    int p, q; cin >> p >> q;
    int l = 1, r = n;
    while (l <= r) {
      int mid = (l + r) >> 1;
      int flag = false;
      if (sum[mid - 1] * p >= a[mid - 1] * q * mid) flag = true;
      for (int i = 1; i + mid - 1 < n; i++) {
        if ((sum[i + mid - 1] - sum[i - 1]) * p >= q * mid * a[i + mid - 1]) flag = true;
      }
      if (flag) l = mid + 1;
      else r = mid - 1;
    }
    int goal = r;
    vector<int> color(n + 1, 0);
    for (int i = goal - 1; i < n; i++) {
      int L = 0, R = i - (goal - 1);
      int val = sum[i] - sum[R];
      while (L <= R) {
        int mid = (L + R) >> 1;
        if ((val + a[mid]) * p >= a[i] * q * goal) R = mid - 1;      
        else L = mid + 1;
      }
      if (L > i - (goal - 1)) continue;
      color[L] += 1; 
      color[i + 1] -= 1;
    }
    vector<int> ans;
    int val = 0;
    for (int i = 0; i < n; i++) {
      val += color[i];
      if (val == 0) ans.push_back(arr[i][1]);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto &it : ans) cout << it << " ";
    cout << endl;
  }
  return 0;
}
