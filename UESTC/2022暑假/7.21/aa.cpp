//
//  aa.cpp
//  2022-07-21 15:40
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
  struct Info {
    int sum[8]; 
  };

  struct Tree {
    int l, r; 
    Info val;
  };  
  vector<Tree> tree;
  vector<int> lazy;

  Segment_Tree(int n) {
    tree.resize(n * 4 + 10);  
    lazy.resize(n * 4 + 10);
  }

  // 合并两个儿子
  Info merge(Info a, Info b) {
    Info res;
    for (int i = 0; i <= 7; i++) {
      res.sum[i] = a.sum[i] + b.sum[i];
    }
    return res;
  }

  void build(int pos, int l, int r) {

    tree[pos].l = l; tree[pos].r = r;
    lazy[pos] = 0;

    int m = l + (r - l) / 2;
    if (l == r) {
      tree[pos].val.sum[0] = 1; 
      for (int i = 1; i <= 7; i++) {
        tree[pos].val.sum[i] = 0;
      }
      return;
    } 
    build(pos << 1, l, m);
    build(pos << 1 | 1, m + 1, r);
    tree[pos].val = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  }

  // 对树上一个位置进行修改
  void add(int pos, int val) {
    if (val == 8) {
      lazy[pos] = 8;

      for (int i = 0; i <= 7; i++) {
        tree[pos].val.sum[i] = 0;
      }
      tree[pos].val.sum[0] = tree[pos].r - tree[pos].l + 1;

    } else {
      if (lazy[pos] == 8) push_down(pos);
      lazy[pos] |= val;

      for (int i = 7; i > 0; i--) {
        for (int j = (i - 1) & i; j > 0; j = (j - 1) & i) {
          if ((j | val) != i) continue;
          tree[pos].val.sum[i] += tree[pos].val.sum[j];      
          tree[pos].val.sum[j] = 0;
        }
        if (i == val) {
          tree[pos].val.sum[i] += tree[pos].val.sum[0];
          tree[pos].val.sum[0] = 0;
        }
      }
    }
  }

  // 传递懒人标记
  void push_down(int pos) {
    if (tree[pos].l == tree[pos].r) return;
    if (lazy[pos] == 0) return; 
    add(pos << 1, lazy[pos]); 
    add(pos << 1 | 1, lazy[pos]);
    lazy[pos] = 0;
  } 

  void modify(int pos, int l, int r, long long val) {
    assert(l <= r);

    if (tree[pos].l >= l && tree[pos].r <= r) {
      add(pos, val);
      return;
    }  

    push_down(pos);
    int m = tree[pos].l + (tree[pos].r - tree[pos].l) / 2;
    if (l <= m) modify(pos << 1, l, r, val);
    if (r > m) modify(pos << 1 | 1, l, r, val);
    tree[pos].val = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  } 

  Info query(int pos, int l, int r) {
    assert(l <= r);

    if (tree[pos].l >= l && tree[pos].r <= r) {
      return tree[pos].val;
    }   

    push_down(pos);
    int m = tree[pos].l + (tree[pos].r - tree[pos].l) / 2;
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
};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  Segment_Tree T(10);   
  T.build(1, 1, 10);
  T.modify(1, 1, 10, 7);
  T.modify(1, 1, 5, 8);
  T.modify(1, 1, 5, 7);
  cout << T.query(1, 1, 10).sum[7];

  return 0;
}
