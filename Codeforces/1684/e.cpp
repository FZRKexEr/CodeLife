//
//  e.cpp
//  2022-05-20 16:14
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define LOCAL
using namespace std;

#ifdef ONLINE_JUDGE
#ifndef LOCAL_TEST
#pragma GCC optimize("O3","unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif
#endif

vector<string> vec_splitter(string s) {
	s += ',';
  vector<string> res;
	while(!s.empty()) {
    res.push_back(s.substr(0, s.find(',')));
		s = s.substr(s.find(',') + 1);
	}
	return res;
}

void debug_out(
vector<string> __attribute__ ((unused)) args,
__attribute__ ((unused)) int idx, 
__attribute__ ((unused)) int LINE_NUM) { cerr << endl; } 
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T) {
	if(idx > 0) cerr << ", "; else cerr << "Line(" << LINE_NUM << ") ";
  stringstream ss; ss << H;
  cerr << args[idx] << " = " << ss.str();
	debug_out(args, idx + 1, LINE_NUM, T...);
}


#ifdef LOCAL
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) 2022
#endif

random_device rd; 
mt19937 seed(rd());
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> U(1, 1000000000ll); // 1 - 1e9

const int MOD = 1e9 + 7;
int power(int a, int b) {
  assert(b >= 0);
  int base = a, ans = 1;
  while (b) {
    if (b & 1) ans = ans * base % MOD;
    base = base * base % MOD;
    b >>= 1;
  }
  return ans;
}

void file() {
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
#endif
}

// 无旋 Treap
// 特性说明:
// 1. kth 可以求出 Treap 中第 k 小的数 1-indexed
// 2. merge_treap 可以合并两个 treap，并且不需要保证它们之间的大小关系, 例题: CF911G。
//    但是效率成迷, 感性理解大概是大常数 O(logn),  实测:
//    a. 在洛谷快速排序中 merge 可以 AC, merge_treap T 3组。
//    b. Treap 板题merge 和 merge_treap 都可以AC。(因为数据水)
//    c. Treap 板题加强版中 merge_treap 用时是 merge 的两倍, 但还是 AC 了
// 3. erase 可以删除一个 key, 如果要删光 key, 把 res2[1] 赋值成 -1 即可
// 4. 这个 Treap 是模拟的 multiset
// 5. 没有 lower_bound 和 upper_bound, nxt() pre() count() 够用了，不要尝试实现 lower_bound,
//    返回 pos(下标) 对 Treap 没用，因为不能保证是根结点。
// 
// 注意:
// 1. 不是根结点的点是完全没用的，不能提供任何有用性质。所以一定要用 split 来得到根结点。
// 2. 不要随意在外面修改 size。修改后要想办法 update
// 3. 时刻留意是不是数组访问了-1
// 4. create 一定不要用 mt19937, 花费时间是函数随机的两倍!
// 5. nxt pre 可以在找不到的时候返回-1，kth 必须找得到。 
// 6. 判断子树是否为空不能用 size = 0 判断，子树为空的时候下标是 -1 !
// 
// 修改:
// 1. push_down 只用在 merge merge_treap output 
// 2. 区间操作修改 push_down
// 
// 模板题: https://www.luogu.com.cn/problem/P6136

struct Treap {
  struct Node {
    int l, r; 
    int key, pri, size;
    int lazy;
    Node (int a, int b) : key(a), pri(b) { 
      l = r = -1, size = 1, lazy = 0; 
    }
  };

  vector<Node> tree; 
  vector<int> root; 
  int seed = 1;
  
  Treap(int n) : root(n + 1, -1) {} 

  void push_down(int pos) {
    
  }
  
  array<int, 2> split(int pos, int key) {
    if (pos == -1) return {-1, -1};
    push_down(pos);
    if (tree[pos].key <= key) {
      array<int, 2> res = split(tree[pos].r, key);
      tree[pos].r = res[0];
      update(pos);
      return {pos, res[1]};
    } else {
      array<int, 2> res = split(tree[pos].l, key);
      tree[pos].l = res[1]; 
      update(pos);
      return {res[0], pos};
    }
  }

  array<int, 2> split_sz(int pos, int sz) {
    if (pos == -1) return {-1, -1};
    push_down(pos);
    int lsize = tree[pos].l == -1 ? 1 : tree[tree[pos].l].size + 1;
    if (lsize <= sz) {
      array<int, 2> res = split_sz(tree[pos].r, sz - lsize);
      tree[pos].r = res[0];
      update(pos);
      return {pos, res[1]};
    } else {
      array<int, 2> res = split_sz(tree[pos].l, sz); 
      tree[pos].l = res[1];
      update(pos);
      return {res[0], pos};
    }
  }

  int merge(int x, int y) {
    if (x == -1) return y;
    if (y == -1) return x;
    if (tree[x].pri < tree[y].pri) {
      push_down(x);
      tree[x].r = merge(tree[x].r, y);  
      update(x);
      return x;
    } else {
      push_down(y);
      tree[y].l = merge(x, tree[y].l); 
      update(y);
      return y;
    }
  }

  int merge_treap(int x, int y) {
    if (x == -1) return y;
    if (y == -1) return x;
    push_down(x), push_down(y);
    if (tree[x].pri > tree[y].pri) swap(x, y);
    array<int, 2> res = split(y, tree[x].key);
    tree[x].l = merge_treap(tree[x].l, res[0]);
    tree[x].r = merge_treap(tree[x].r, res[1]);
    update(x);
    return x;
  }

  vector<int> output(int pos) {
    if (pos == -1) return {};
    push_down(pos);
    vector<int> res;
    vector<int> l = output(tree[pos].l), r = output(tree[pos].r);
    res.insert(res.end(), l.begin(), l.end());
    res.push_back(tree[pos].key);
    res.insert(res.end(), r.begin(), r.end());
    return res;
  }

  void update(int pos) {
    if (pos == -1) return;
    tree[pos].size = 1;
    if (tree[pos].l != -1) tree[pos].size += tree[tree[pos].l].size;
    if (tree[pos].r != -1) tree[pos].size += tree[tree[pos].r].size;
  }

  int func_rand() {
    return seed *= 19260817;
  }

  int create(int key) {
    tree.emplace_back(key, func_rand());
    return (int) tree.size() - 1;
  }
  
  void insert(int &pos, int key) {
    int o = create(key);
    array<int, 2> res = split(pos, key);
    pos = merge(merge(res[0], o), res[1]); 
  }

  int rank(int &pos, int key) {
    array<int, 2> res = split(pos, key - 1);
    int rk = (res[0] == -1) ? 1 : tree[res[0]].size + 1;
    pos = merge(res[0], res[1]);
    return rk;
  }

  int kth(int pos, int k) {
    while (pos != -1) {
      int lsize = tree[pos].l == -1 ? 1 : tree[tree[pos].l].size + 1;
      if (lsize == k) return tree[pos].key; 
      if (k < lsize) pos = tree[pos].l;
      if (k > lsize) pos = tree[pos].r, k -= lsize;
    }
    assert(0);
  }

  void erase(int &pos, int key) {
    array<int, 2> res1 = split(pos, key); 
    array<int, 2> res2 = split(res1[0], key - 1); 
    if (res2[1] != -1) {
      res2[1] = merge(tree[res2[1]].l, tree[res2[1]].r);
    }
    pos = merge(merge(res2[0], res2[1]), res1[1]);
  }

  int pre(int &pos, int key) {
    array<int, 2> res = split(pos, key - 1); 
    if (res[0] == -1) return -1;
    int ans = kth(res[0], tree[res[0]].size);
    pos = merge(res[0], res[1]);
    return ans;
  }

  int nxt(int &pos, int key) {
    array<int, 2> res = split(pos, key);
    if (res[1] == -1) return -1;
    int ans = kth(res[1], 1);
    pos = merge(res[0], res[1]);
    return ans;
  }

  int count(int &pos, int key) {
    array<int, 2> res1 = split(pos, key);
    array<int, 2> res2 = split(res1[0], key - 1);
    int ans = res2[1] == -1 ? 0 : tree[res2[1]].size;
    pos = merge(merge(res2[0], res2[1]), res1[1]);
    return ans;
  }
};

signed main() {
//  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z; 
  while (z--) {
    int n, k; cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    vector<int> b = a;
    b.erase(unique(b.begin() + 1, b.end()), b.end());

    Treap que(1);
    
    map<int, int> cnt, vis; 
    for (int i = n; i >= 1; i--) {
      cnt[a[i]]++;
    }
    for (int i = n; i >= 1; i--) {
      if (vis[a[i]]) continue;
      vis[a[i]] = 1;
      que.insert(que.root[1], cnt[a[i]]);
    }
    int ans = n; 
    int need = 0, oth = 0;
     
    for (int i = 0; i <= n; i++) {
      int all = n - (lower_bound(a.begin() + 1, a.end(), i) - a.begin()) + 1 + oth; 
      if (min(all, k) < need) break;

      int mex = i;
      int diff = (int) b.size() - 1;
      int ned = need; 

      if (que.root[1] != -1) {
        int val = que.kth(que.root[1], 1);
        while (val != -1) {
          int count = que.count(que.root[1], val);
          if (ned <= count * val) {
            diff += ned;
            diff -= ned / val;
            ned = 0;
            break;
          } else {
            diff += count * val;
            diff -= count;
            ned -= count * val;
          }    
          val = que.nxt(que.root[1], val);
        }
      }

      if (ned == 0) {
        ans = min(ans, diff - mex);
      } else {
        diff += ned;  
        ans = min(ans, diff - mex);
      }
      if (cnt[i]) {
        que.erase(que.root[1], cnt[i]);
        oth += cnt[i] - 1;
      } else {
        need++;
      }
    }
    cout << ans << endl;
  }
   
  return 0;
}
