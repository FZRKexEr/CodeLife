//
//  884.cpp
//  2022-05-19 20:36
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define LOCAL
using namespace std;

const long long INF = 0x3f3f3f3f3f3f3f3f;


// 先build！先build！先build！
// 修改：区间加法
// 查询：区间和，最大值，最小值
// 修改模板顺序：
// 0. 如果是单点修改，可以删除 lazy 数组 和 push_down, 也可以不删
// 1. Info 结构体
// 2. build 函数
// 3. merge 函数
// 4. add 函数
// 5. push_down 函数 
// modify 和 query 不需要修改！
const int MOD = 1e9 + 7;
struct Segment_Tree {
  
  #define tl tree[pos].l 
  #define tr tree[pos].r 
  #define tv tree[pos].val
  struct Info {
    long long cnt, maxi; 
  };

  struct Tree {
    int l, r; 
    Info val;
  };  
  vector<Tree> tree;

  Segment_Tree(int n) {
    tree.resize(n * 4 + 10);  
  }

  // 合并两个儿子
  Info merge(Info a, Info b) {
    Info res;
    if (a.maxi < b.maxi) swap(a, b);
    if (a.maxi == b.maxi) {
      res.cnt = a.cnt + b.cnt;
      res.cnt %= MOD;
    } else res.cnt = a.cnt;
    res.maxi = max(a.maxi, b.maxi);
    return res;
  }

  void build(int pos, int l, int r) {
    tl = l; tr = r;    

    int m = l + (r - l) / 2;
    if (l == r) {
      tv.cnt = 1;
      tv.maxi = 0;
      return;
    } 
    build(pos << 1, l, m);
    build(pos << 1 | 1, m + 1, r);
    tv = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  }


  // 对树上一个位置进行修改
  void add(int pos, array<int, 2> val) {
    if (val[1] > tv.maxi) {
      tv.maxi = val[1];
      tv.cnt = val[0]; 
    } else {
      tv.cnt += val[0];
      tv.cnt %= MOD;
    }
  }


  void modify(int pos, int l, int r, array<int, 2> val) {
    if (tl >= l && tr <= r) {
      add(pos, val);
      return;
    }  
    int m = tl + (tr - tl) / 2;
    if (l <= m) modify(pos << 1, l, r, val);
    if (r > m) modify(pos << 1 | 1, l, r, val);
    tv = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  } 

  Info query(int pos, int l, int r) {
    if (tl >= l && tr <= r) {
      return tv;
    }   
    int m = tl + (tr - tl) / 2;
    Info res;

    if (l <= m && r > m) {
      res = merge(query(pos << 1, l, r), query(pos << 1 | 1, l , r));
    } else if (l > m) {
      res = query(pos << 1 | 1, l, r);
    } else if (r <= m) {
      res = query(pos << 1, l, r);
    }

    tv = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
    return res;
  }
  #undef tl
  #undef tr
  #undef tv
};


signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n; cin  >> n; 
  vector<int> a(n + 1), b;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  b = a;
  sort(b.begin() + 1, b.end());
  b.erase(unique(b.begin() + 1, b.end()), b.end());
  for (int i = 1; i <= n; i++) {
    a[i] = lower_bound(b.begin() + 1, b.end(), a[i]) - b.begin();
  }

  Segment_Tree T(n); T.build(1, 1, b.size() - 1);

  T.modify(1, a[1], a[1], (array<int, 2>) {1, 1}); 
  int maxn = 1, ans = 1;
   
  for (int i = 2; i <= n; i++) {
    Segment_Tree::Info res;
    if (a[i] != 1) res = T.query(1, 1, a[i] - 1);  
    else res = {1, 0};

    T.modify(1, a[i], a[i], (array<int, 2>) {res.cnt, res.maxi + 1}); 

    if (res.maxi + 1 > maxn) {
      maxn = res.maxi + 1;
      ans = res.cnt;
    } else if (res.maxi + 1 == maxn) {
      maxn = res.maxi + 1;
      ans += res.cnt;
      ans %= MOD;
    }
  }
  cout << ans;
  
  return 0;
}
