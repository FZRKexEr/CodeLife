//
//  k.cpp
//  2022-07-11 14:30
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long

struct Segment_Tree {
  
  #define tl tree[pos].l 
  #define tr tree[pos].r 
  #define tv tree[pos].val
  struct Info {
    long long sum, mx; 
  };

  struct Tree {
    int l, r; 
    Info val;
  };  
  vector<Tree> tree;
  vector<long long> lazy;

  Segment_Tree(int n) {
    tree.resize(n * 4 + 10);  
    lazy.resize(n * 4 + 10);
  }

  // 合并两个儿子
  Info merge(Info a, Info b) {
    Info res;
    res.sum = a.sum + b.sum;
    res.mx = max(a.mx + b.sum, b.mx);
    return res;
  }

  void build(int pos, int l, int r, vector<int> &arr) {
    tl = l; tr = r;    
    lazy[pos] = 0ll;

    int m = l + (r - l) / 2;
    if (l == r) {
      tv.sum = arr[l]; 
      tv.mx = arr[l] + l;
      return;
    } 
    build(pos << 1, l, m, arr);
    build(pos << 1 | 1, m + 1, r, arr);
    tv = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  }

  // 对树上一个位置进行修改
  void add(int pos, int tm, long long val) {
    lazy[pos] += val;
    tv.sum = val;
    tv.mx = val + tm;
  }

  void modify(int pos, int l, int r, long long val) {
    if (tl >= l && tr <= r) {
      add(pos, l, val);
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
   
  int q; cin >> q;
  
  Segment_Tree T(1e6 + 10);
  vector<int> arr(1e6 + 10, 0);
  T.build(1, 1, 1e6, arr);

  vector<array<int, 2>> opt(q + 1);  
  for (int i = 1; i <= q; i++) {
    char c; cin >> c;
    if (c == '+') {
      int t, d; cin >> t >> d;
      opt[i][0] = t;
      opt[i][1] = d;
      T.modify(1, t, t, d);      
    } else if (c == '-') {
      int o; cin >> o;
      T.modify(1, opt[o][0], opt[o][0], 0); 
    } else if (c == '?') {
      int t; cin >> t;
      cout << max(T.query(1, 1, t).mx - t, 0ll) << endl; 
    }
  }


  return 0;
}
