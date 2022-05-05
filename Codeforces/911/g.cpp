//
//  g.cpp
//  2022-04-30 15:30
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

void file() {
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
#endif
}


// Treap 森林
// 一棵子树就是一个 Treap
// 同一个 Treap 每一个键值只能出现一次。
// 不同 Treap 可以含有相同键值
struct Treap {

  struct Maintain {
    int cnt, sz;    
    
    Maintain() {
      // cnt 当前 key 的个数
      // sz 当前子树所有 key 的个数和 
      cnt = 1, sz = 1;
    }
  };

  struct Node {
    array<int, 2> son;
    int key, pri;
    Maintain val;

    Node(int a, int b) : key(a), pri(b) {
      son[0] = son[1] = -1; // 默认 -1 是空结点
    }
  };

  vector<Node> tree;  // 0 - indexed
  vector<int> root; // 需要手动设置，初始根结点是-1

  int create(int key) {
    mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());     
    tree.push_back({key, (int) (rng() & ((1ll << 31) - 1))});
    return (int) tree.size() - 1;
  }

  // merge 两个子树，只要求 x 和 y 都是二叉搜索树就行
  // 复杂度???
  // 1. 当 x key 全都小于 y key 时，显然是 O(h)
  // 2. 当 子树x 和 子树y 的 key 完全相同时, 复杂度O(size)
  // 3. 当 x 或者 y size = 1的时候，复杂度 O(h)
  int merge(int x, int y) {
    if (x == -1) return y;
    if (y == -1) return x;
    if (tree[x].pri < tree[y].pri) swap(x, y);

    int &l = tree[x].son[0];
    int &r = tree[x].son[1];

    int o = find(y, tree[x].key);
    if (o != -1) {
      tree[x].val.cnt += tree[y].val.cnt;
      erase_all(y, tree[y].key);
    }
    array<int, 2> res = split(y, tree[x].key);
    l = merge(l, res[0]); 
    r = merge(r, res[1]);

    update(x);
    return x;
  }

  // 从子树 pos 里删光键值为 key 的数, 子树里必须包含 key
  void erase_all(int &pos, int key) {
    if (find(pos, key) == -1) assert(0);
    array<int, 2> res1 = split(pos, key - 1);
    array<int, 2> res2 = split(res1[1], key); 
    pos = merge(res1[0], res2[1]);
  }

  // 删除一个键值为 key 的数, 子树里必须包含 key
  void erase(int &pos, int key) {
    int o = find(pos, key);
    assert(o != -1);
    if (tree[o].val.cnt == 1) erase_all(pos, key);
    else {
      tree[o].val.cnt--;
      tree[o].val.sz--;
    }
  }

  // 把子树 pos 分裂成 <= key 和 > key
  array<int, 2> split(int pos, int key) {
    if (pos == -1) return {-1, -1};
    if (tree[pos].key <= key) {
      int &r = tree[pos].son[1];
      array<int, 2> res = split(r, key);
      r = res[0];
      return {pos, res[1]};
    } else {
      int &l = tree[pos].son[0];
      array<int, 2> res = split(l, key);
      l = res[1];
      return {res[0], pos};
    }
    update(pos);
  }

  // 从树里找到键值为 key 的位置. 找不到返回 -1
  int find(int pos, int key) {
    if (pos == -1) return -1;
    if (tree[pos].key == key) return pos;
    else if (tree[pos].key < key) {
      return find(tree[pos].son[1], key);
    } else {
      return find(tree[pos].son[0], key);
    }
  }

  // 从儿子更新 pos 的 val 值
  void update(int pos) {
    int l = tree[pos].son[0];  
    int r = tree[pos].son[1];
    tree[pos].val.sz = tree[pos].val.cnt;
    if (l != -1) tree[pos].val.sz += tree[l].val.sz;
    if (r != -1) tree[pos].val.sz += tree[r].val.sz;
  }

  // 向以 pos 为根的树里插入 key, 一般 pos 是一个 root
  void insert(int &pos, int key) {
    int o = create(key);
    pos = merge(pos, o);
  }

  // 输出子树 pos
  vector<int> output(int pos) {
    if (pos == -1) return {};
    auto l = output(tree[pos].son[0]);
    l.push_back(tree[pos].key); 
    auto r = output(tree[pos].son[1]);
    l.insert(l.end(), r.begin(), r.end());
    return l;
  }
};

signed main() {
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n; cin >> n;

  Treap T;
  T.root.resize(101, -1);
  
  for (int i = 1; i <= n; i++) {
    int val; cin >> val;
    T.insert(T.root[val], i);
  }

  int m; cin >> m;
  for (int i = 1; i <= m; i++) {
    int l, r, x, y; cin >> l >> r >> x >> y;
    array<int, 2> res1 = T.split(T.root[x], l - 1); 
    array<int, 2> res2 = T.split(res1[1], r); 

    int a = res1[0], b = res2[0], c = res2[1];
    T.root[x] = T.merge(a, c);
    T.root[y] = T.merge(b, T.root[y]);  
  }

  vector<int> ans(n + 1); 
  for (int i = 1; i <= 100; i++) {
    vector<int> res = T.output(T.root[i]);
    for (auto &it : res) ans[it] = i; 
  }

  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " ";
  }
  
  return 0;
}
