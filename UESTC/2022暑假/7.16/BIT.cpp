//
//  BIT.cpp
//  2022-07-16 19:45
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long

// 树状数组
// 1. 支持 区间add，区间查询 sum
// 2. 不要用 modify 和 query (避免误用)
// 3. 用 add 函数和 get_sum 函数 修改和查询
// 4. 下标必须从1开始
// 5. 复杂度 O(nlogn)
// 6. 常数很小，比线段树快6倍！

struct BIT {
  vector<array<long long, 2>> tree; 
  int limit;

  BIT(int n) : tree(n + 1, {0ll, 0ll}), limit(n) {}

  inline int lowbit(int x) {
    return x & (-x);
  }

  void modify(int x, long long v1) {
    assert(x >= 1);
    long long v2 = v1 * x;
    while (x <= limit) {
      tree[x][0] += v1;
      tree[x][1] += v2;
      x += lowbit(x);
    }
  }

  long long query(int x) {
    assert(x >= 0);
    long long ans = 0ll;
    int backup = x;
    while (x) {
      ans -= tree[x][1];
      ans += 1ll * (backup + 1) * tree[x][0];
      x -= lowbit(x);
    }
    return ans;
  }

  void add(int l, int r, long long val) {
    modify(l, val);
    modify(r + 1, -val);
  }

  long long get_sum(int l, int r) {
    return query(r) - query(l - 1);
  }
};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int n, q; cin >> n >> q;   
  BIT T(n);
  for (int i = 1; i <= n; i++) {
    int val; cin >> val;
    T.add(i, i, val); 
  }
  for (int i = 1; i <= q; i++) {
    int o; cin >> o;
    if (o == 1) {
      int l, r, x; cin >> l >> r >> x;
      T.add(l, r, x);
    } else {
      int l, r; cin >> l >> r;
      cout << T.get_sum(l, r) << endl;
    }
  }

  return 0;
}
