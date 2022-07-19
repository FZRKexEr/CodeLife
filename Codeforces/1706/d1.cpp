//
//  d1.cpp
//  2022-07-18 23:23
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
    int n, k; cin >> n >> k;
    vector<int> a(n + 1);
    int maxn = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      maxn = max(maxn, a[i]);
    }
    int ans = 0x3f3f3f3f;

    auto solve1 = [&](int a, int b) {
      int l = 1, r = a;
      while (l <= r) {
        int mid = (l + r) / 2;
        if (a / mid <= b) r = mid - 1;
        else l = mid + 1;
      }
      return l;
    };

    auto solve2 = [&](int a, int b) {
      assert(a >= b);
      int l = 1, r = a + 1;
      while (l <= r) {
        int mid = (l + r) >> 1;  
        if (a / mid < b) r = mid - 1; 
        else l = mid + 1;
      }
      return r;
    };

    for (int i = maxn / k; i <= maxn; i++) {
      int l = 0, r = i;  
      while (l <= r) {
        int mid = (l + r) >> 1;  
        int flag = true;
        for (int j = 1; j <= n; j++) {
          if (a[j] < mid) flag = false;
          if (a[j] > i) {
            int least;
            if (i == 0) least = 0x3f3f3f3f;
            else {
              least = a[j] / (i + 1) + 1;
            }

            int high;
            if (mid == 0) high = 0x3f3f3f3f;
            else high = a[j] / mid;

            if (least > high) flag = false;
            if (least > k) flag = false;  
            if (high == 0) flag = false;
          }
        }
        if (flag) l = mid + 1;
        else r = mid - 1;
      }
      ans = min(ans, i - r);
    }
    cout << ans << endl;
  }


  return 0;
}
