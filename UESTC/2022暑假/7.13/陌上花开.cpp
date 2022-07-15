//
//  陌上花开.cpp
//  2022-07-13 20:01
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#define LOCAL
#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long


struct BIT {
  vector<int> tree;
  int limit;
  BIT (int n) : tree(n + 1, 0), limit(n) {}

  inline int lowbit(int x) { return x & (-x); }

  void modify(int x, int val) { // 单点修改
    assert(x >= 1);
    while (x <= limit) {
      tree[x] += val;     
      x += lowbit(x);
    }
  }

  int query(int x) {
    assert(x >= 0);
    int ans = 0;
    while (x) {
      ans += tree[x];
      x -= lowbit(x);
    }
    return ans;
  }

  int sum(int l, int r) {
    if (r < l) return 0;
    assert(l >= 1 && r >= 1);
    return query(r) - query(l - 1); 
  }
};

signed main() {
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int n, k; cin >> n >> k; 

  vector<array<int, 4>> arr;


  auto trans = [&](array<int, 4> x) {
    return (array<int, 3>) {x[0], x[1], x[2]};
  };

  map<array<int, 3>, int> cnt, ord;
  for (int i = 1; i <= n; i++) {
    int a, b, c; cin >> a >> b >> c;
    arr.push_back({a, b, c, i});
    cnt[trans(arr.back())]++;
  }

  vector<int> f(arr.size(), 0);

  BIT T(200010); 
  
  function<void(int, int)> CDQ = [&] (int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    CDQ(l, mid); CDQ(mid + 1, r); 
    sort(arr.begin() + l, arr.begin() + mid + 1, [&](auto i, auto j) { return i[1] < j[1]; });  
    sort(arr.begin() + mid + 1, arr.begin() + r + 1, [&](auto i, auto j) { return i[1] < j[1]; });
    int p = l;
    for (int i = mid + 1; i <= r; i++) {
      vector<array<int, 4>> wait;
      while (p <= mid && arr[p][1] <= arr[i][1]) {
        if (arr[p] == arr[i]) {
          wait.push_back(arr[p]);
          p++;
          continue;
        }
        T.modify(arr[p][2], 1);
        p++;
      }
      f[arr[i][3]] += T.query(arr[i][2]); 
      for (auto &it : wait) {
        T.modify(it[2], 1);
      }
    }
    for (int i = l; i < p; i++) {
      T.modify(arr[i][2], -1);
    }
  };
  
  sort(arr.begin(), arr.end());
  CDQ(0, (int) arr.size() - 1);
  
  map<array<int, 3>, int> res;
  for (int i = 0; i < (int) arr.size(); i++) {
    res[trans(arr[i])] = max(res[trans(arr[i])], f[arr[i][3]]);      
  }
  vector<int> ans(n, 0);
  for (auto &it : res) {
    ans[it.second] += cnt[it.first];
  }
  int all = 0;
  for (int i = 0; i < n; i++) {
    cout << ans[i] << endl;
    all += ans[i];
  }
  assert(all == n);
  return 0;
}
