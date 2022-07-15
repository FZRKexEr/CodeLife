//
//  a.cpp
//  2022-07-13 14:08
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long
struct Basis {
  vector<int> a; 
  // 不是主元的位置不管，是主元的位置 a 保证了正三角RREF
  void insert(int x) {
    // 把 x 中含有的所有被 a 包含的主元位置消掉
    for (auto &it : a) x = min(x, x ^ it);
    if (!x) return;
    // 说明 x 中含有 a 不包含的主元位置。
    // 把 a 中所有元素消掉 x 的主元位(x 的最高位)
    for (auto &it : a) it = min(it, it ^ x);
    a.push_back(x);
    // 加入的每一个数都保证了在其他数的主元位置为0，且其他数在该主元位置为0
    // 不 sort , 插入操作也正确。因为主元位是 RREF。sort 的目的是保证 kth 正确。
    sort(a.begin(), a.end());
  }
  // x 能否被消
  bool can(int x) {
    for (auto &it : a) x = min(x, x ^ it); 
    return !x;
  }

  int maxxor(int x = 0) {
    // 事实上，主元RREF后不需要取 max, 但是如果不 RREF 就需要取 max
    for (auto &it : a) x = max(x, x ^ it);
    return x;
  }

  // 第 K 小, 第一小是 0    
  // 显然第 K 小就是把 K 二进制分解后异或基底
  int kth(int k) {
    if (k > (1ll << (int) a.size())) return -1; 
    k--; int ans = 0;
    for (int i = 0; i < (int) a.size(); i++) {
      if (k >> i & 1) ans ^= a[i];
    }
    return ans;
  }
};
signed main() {
 // freopen("in.txt", "r", stdin);
  ios::sync_with_stdio(false); 
  cin.tie(0);
  
  int z; cin >> z;
  while (z--) {
    int n; cin >> n;
    vector<int> a(n + 1);
    Basis T;
    vector<int> cnt(100, 0);
    for (int i = 1; i <= n; i++) {
      cin >> a[i]; 
      for (int j = 0; j <= 62; j++) {
        if (a[i] >> j & 1) cnt[j]++;
      }
    }
    int goal = -1;
    for (int i = 0; i <= 62; i++) {
      if (cnt[i] % 2 == 0) {
        for (int j = 1; j <= n; j++) {
          if (a[j] >> i & 1)
            a[j] ^= (1ll << i);
        }
      } else {
        goal = max(goal, i);
      }
    }
    for (int i = 1; i <= n; i++) {
      T.insert(a[i]);  
    }
    if (goal == -1) cout << 0 << endl;
    else {
      int r = 1ll << T.a.size();
      int l = 1;
      while (l <= r) {
        int mid = (l + r) >> 1;
        if (T.kth(mid) >= (1ll << goal)) r = mid - 1;
        else l = mid + 1;
      }
      int res = T.kth(l); 
//      cout << (1ll << goal) << " " << res << endl;
      int all = 0;
      for (int i = 1; i <= n; i++) {
        all ^= a[i];
      }
      cout << res - (all ^ res) << endl;
    }
  }
   

  return 0;
}
