//
//  d.cpp
//  2022-04-27 01:07
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

/*
 * 关于权值线段树:
 * 1. 经典问题：求数列第K大（区间第K大用可持久化线段树）
 * 关于动态开点：
 * 1. 能不用就不用，能离散化就离散化
 * 2. 已知用处：可持久化数据结构，线段树合并，强制在线不能离散化的题。
 * 模板特性：
 * 1. 只支持单点修改，区间查询。(反过来也行，不支持lazy标记)
 * 2. 如果问题能用普通线段树解决，就不要用这个。空间复杂度 Knlogn（K是大常数）
 * 3. 支持负数权值
 * 4. 不用 #define int long long 可以保证 long long 内结果正确
 * 优化：
 * 1. 模板内置了 sum，maxn，minn。可以根据题目要求删除一些，减少空间消耗。
 * 2. 还可以进一步优化空间：把 l 和 r 也删掉，直接在函数里传参
 * 3. 参考：逆序对问题：n = 5e5, 数值范围 1e9, 做了1，2优化后消耗 75mb 空间。
 */

const long long INF = 0x3f3f3f3f3f3f3f3f;
struct Segment_Tree {

  struct Info {
    int sum; 
    Info () { sum = 0; }
  };

  struct Tree {
    int ls, rs; // 左儿子，右儿子 编号
    int l, r; // 左边界，右边界
    Info dat;
    Tree(int a, int b, int c, int d) : ls(a), rs(b), l(c), r(d) {} 
  };

  vector<Tree> tree; 

  Segment_Tree(int l, int r) {
    tree.push_back({-1, -1, l, r});
  }

  int insert(int l, int r) {
    tree.push_back({-1, -1, l, r});
    return (int) tree.size() - 1;
  }
 
  Info merge(Info a, Info b) {
    Info res;
    res.sum = a.sum + b.sum;
    return res;
  }

  void add(int pos, int val) {
    tree[pos].dat.sum += val;
  }

  void push_up(int pos) {
    tree[pos].dat.sum = 0; 
    if (tree[pos].ls != -1) tree[pos].dat = merge(tree[pos].dat, tree[tree[pos].ls].dat);
    if (tree[pos].rs != -1) tree[pos].dat = merge(tree[pos].dat, tree[tree[pos].rs].dat);
  }

  void modify(int pos, int goal, int val) {
    if (tree[pos].l == tree[pos].r) {
      add(pos, val);
      return;
    }
    int mid = (tree[pos].l + tree[pos].r) >> 1;
    if (goal <= mid) {
      if (tree[pos].ls == -1) tree[pos].ls = insert(tree[pos].l, mid);
      modify(tree[pos].ls, goal, val);
    } else {
      if (tree[pos].rs == -1) tree[pos].rs = insert(mid + 1, tree[pos].r);
      modify(tree[pos].rs, goal, val);
    }
    push_up(pos);
  }

  Info query(int pos, int l, int r) {
    if (tree[pos].l >= l && tree[pos].r <= r) {
      return tree[pos].dat;
    }
    int mid = (tree[pos].l + tree[pos].r) >> 1;
    Info res; 

    if (l <= mid && tree[pos].ls != -1) {
      res = merge(res, query(tree[pos].ls, l, r));
    }
    if (r >= mid + 1 && tree[pos].rs != -1) {
      res = merge(res, query(tree[pos].rs, l, r));
    }
    push_up(pos);
    return res;
  }
};
signed main() {
//  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n; cin >> n; 
  Segment_Tree T(1, 3e7);

  map<int, int> cnt;

  int base = 1e7 + 1;
  for (int i = 1; i <= n; i++) {
    int o, x; cin >> o >> x;
    if (o == 1) {
      cnt[x]++;
      x += base;
      T.modify(0, x, 1); 
    } else if (o == 2) {
      cnt[x]--;
      if (cnt[x] == 0) cnt.erase(x);
      x += base;
      T.modify(0, x, -1);

    } else if (o == 3) {
      x += base;
      cout << T.query(0, 1, x - 1).sum + 1 << endl; 
    } else if (o == 4) {
      int l = 1, r = 3e7;
      while (l <= r) {
        int mid = (l + r) >> 1;
        int res = T.query(1, 1, mid).sum;
        if (res > x - 1) {
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
      cout << r + 1 - base << endl;

    } else if (o == 6) {
      auto it = cnt.upper_bound(x); 
      if (it == cnt.end()) {
        cout << "NOT FOUND" << endl;
      } else {
        cout << (it->first) << endl;
      }
    } else {
      auto it = cnt.lower_bound(x);
      if (it == cnt.begin()) {
        cout << "NOT FOUND" << endl;
      } else {
        it--;
        cout << (it->first) << endl;
      }
    }
  }
  return 0;
}
