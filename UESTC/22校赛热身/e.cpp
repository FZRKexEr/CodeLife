/**   author:  LiZnB
 *    created: 07.12.2021 20:59:33
 **/
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5 + 10;
const long long INF = 0x3f3f3f3f3f3f3f3f;
int MOD;

struct Segment_Tree {

  // 修改和查询前一定要 build
  // 注意根据题目数据范围来修改 N ， 1e6 很容易 MLE。

  #define tl tree[pos].l 
  #define tr tree[pos].r 
  struct Info {
    long long sum, maxi, mini; 
    Info() { sum = 0ll, maxi = -INF, mini = INF; } 
  };

  struct Tree {
    int l, r; 
    Info val;
  } tree[4 * N];  
  long long lazy1[8 * N];
  long long lazy2[8 * N];

  // 合并两个儿子
  Info merge(Info a, Info b) {
    Info res;
    res.sum = (a.sum + b.sum) % MOD;
    res.maxi = max(a.maxi, b.maxi);
    res.mini = min(a.mini, b.mini);
    return res;
  }

  void build(int pos, int l, int r, long long *arr) {

    tl = l; tr = r;    
    lazy1[pos] = 1; 
    lazy2[pos] = 0;

    int m = l + (r - l) / 2;
    if (l == r) {
      tree[pos].val.sum = arr[l] % MOD; 
      return;
    } 
    build(pos << 1, l, m, arr);
    build(pos << 1 | 1, m + 1, r, arr);
    tree[pos].val = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  }

  // 对树上一个位置进行修改
  void add(int pos, long long val, int o) {
    if (o == 1) {
      (lazy2[pos] *= val) %= MOD;
      (lazy1[pos] *= val) %= MOD; 
      (tree[pos].val.sum *= val) %= MOD;
      (tree[pos].val.maxi *= val) %= MOD;
      (tree[pos].val.mini *= val) %= MOD;
    } else {
      (lazy2[pos] += val) %= MOD;
      (tree[pos].val.sum += (tr - tl + 1) * val % MOD) %= MOD;
      (tree[pos].val.maxi += val) %= MOD;
      (tree[pos].val.mini += val) %= MOD;
    }
  }

  void push_down(int pos, int o) {
    if (o == 1) {
      if (lazy1[pos] == 1) return;
      add(pos << 1, lazy1[pos], o);
      add(pos << 1 | 1, lazy1[pos], o);
      lazy1[pos] = 1;
    } else {
      if (lazy2[pos] == 0) return;
      add(pos << 1, lazy2[pos], o);
      add(pos << 1 | 1, lazy2[pos], o);
      lazy2[pos] = 0;
    }
  } 

  void modify(int pos, int l, int r, long long val, int o) {
    if (tl >= l && tr <= r) {
      add(pos, val, o); 
      return;
    }  
    push_down(pos, 1);
    push_down(pos, 2);
    int m = tl + (tr - tl) / 2;
    if (l <= m) modify(pos << 1, l, r, val, o);
    if (r > m) modify(pos << 1 | 1, l, r, val, o);
    tree[pos].val = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  } 

  Info query(int pos, int l, int r) {
    if (tl >= l && tr <= r) {
      return tree[pos].val;
    }   
    push_down(pos, 1);
    push_down(pos, 2);
    int m = tl + (tr - tl) / 2;
    Info res;

    if (l <= m && r > m) {
      res = merge(query(pos << 1, l, r), query(pos << 1 | 1, l , r));
    } else if (l > m) {
      res = query(pos << 1 | 1, l, r);
    } else if (r <= m) {
      res = query(pos << 1, l, r);
    }

    tree[pos].val = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
    return res;
  }
  #undef tl
  #undef tr
} ST;

int a[N];
signed main() {
  int n, m; cin >> n >> m >> MOD;   
  for (int i = 1; i <= n; i++) {
    cin >> a[i]; 
  }
  ST.build(1, 1, n, a);
  for (int i = 1; i <= m; i++) {
    long long o, l, r, k; 
    cin >> o;
    if (o == 3) {
      cin >> l >> r;
      cout << ST.query(1, l, r).sum << endl;
    } else if (o == 1) {
      cin >> l >> r >> k;
      k %= MOD;
      ST.modify(1, l, r, k, 1); 
    } else {
      cin >> l >> r >> k;
      k %= MOD;
      ST.modify(1, l, r, k, 2); 
    }
    
  }
  return 0;
}
