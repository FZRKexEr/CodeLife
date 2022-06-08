//
//  ff.cpp
//  2022-05-23 17:06
//
//  Created by liznb
//  

#include <bits/stdc++.h>
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


// 合并线段树
// 特性说明：
// 1. 在 vector<Tree> tree; 中初始有 n 个权值线段树(动态开点), 用于合并
// 2. 使用 merge_tree , 合并两个线段树(可以是子树), 需要保证传入的两个下标对应的 l, r 相同
// 3. 使用 merge_tree_lossless 后，原有的两个线段树依然可以正常访问。
// 4. 访问初始的 n 个root，一定！要用 root[i], 因为 root[i] 会因为 merge_tree 变动，类比 Treap
// 5. root[pos] = merge_tree(root[pos], root[v]); 才是 merge_tree 的正确用法，一定要让 merge_tree 的返回值被用到！
//
// 针对不同的题需要重写模板的一部分，修改顺序如下:
// 1. Info 结构体(注意初始值)
// 2. merge 函数
// 3. add 函数
// 4. merge_tree 函数
// 5. 检查 query, push_up 里的初始值是否赋值正确
// 6. 一般来说 modify 函数绝对不会被修改 ！

const int INF = 0x3f3f3f3f;
struct Segment_Tree {

  struct Info {
    int minn;
    Info () { minn = INF; } // 注意初始值
  };

  struct Tree {
    int ls, rs; // 左儿子，右儿子 编号
    int l, r; // 左边界，右边界
    Info dat;
    Tree(int a, int b, int c, int d) : ls(a), rs(b), l(c), r(d) {} 
  };

  vector<Tree> tree; 
  vector<int> root;

  // 初始化 n 棵线段树 1-indexed
  Segment_Tree (int n, int l, int r) {
    root.resize(n + 1);
    iota(root.begin(), root.end(), 0);
    tree.resize(n + 1, {-1, -1, l, r});  
  }

  int insert(int l, int r) {
    tree.push_back({-1, -1, l, r});
    return (int) tree.size() - 1;
  }

  // 无损合并：合并后原来的两个线段树完整保留, 但是要耗费很多空间(和重合点数正相关)。
  // 一般只有在强制在线题目用这个。
  //
  // 注意: 合并后不要进行修改，否则会破坏原来的线段树，变成有损，需要提前modify好。
  // 
  // n = 1e5, 256mb 大概率在不优化的时候空间会爆
  // 优化手段：(建议都加上)
  // 1. 关掉 #define int long long, 只把sum之类的加上 long long
  // 2. 强优化: tree.reserve(n * 50) (n = 1e5 256mb 刚好)
  // 3. 不要初始化成 (-1e9, 1e9)

  int merge_tree_lossless(int a, int b) {
    if (a == -1) return b;       
    if (b == -1) return a;
    int p = insert(tree[a].l, tree[a].r);
    // merge_tree 只会在叶子结点合并, 注意这里的合并不能使用两个儿子的 merge 函数! 要单独写
    if (tree[a].l == tree[a].r) {
      // 需要重写!!!
      tree[p].dat.minn = min(tree[a].dat.minn, tree[b].dat.minn);
      return p;
    }
    tree[p].ls = merge_tree_lossless(tree[a].ls, tree[b].ls);
    tree[p].rs = merge_tree_lossless(tree[a].rs, tree[b].rs);
    push_up(p); 
    return p;
  }
  // 同一棵树里两个儿子合并, 注意不能用在不同树的相同结点合并。
  Info merge(Info a, Info b) {
    Info res;
    // merge 函数每一道题都需要重写!!!
    res.minn = min(a.minn, b.minn); 
    return res;
  }

  void add(int pos, int val) {
    if (tree[pos].dat.minn == INF) tree[pos].dat.minn = val;  
    else tree[pos].dat.minn += val;
  }

  void push_up(int pos) {
    tree[pos].dat.minn = INF; 
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
    Info res; res.minn = INF; //注意初始值 可能需要修改的地方
                               
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
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, r; cin >> n >> r; 

  vector<int> a(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  vector<vector<int>> G(n + 1);
  for (int i = 1; i <= n - 1; i++) {
    int u, v; cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  vector<int> dep(n + 1, 0); 


  function<void(int, int)> dfs1 = [&] (int pos, int fa) {
    for (auto &v : G[pos]) {
      if (v == fa) continue;
      dep[v] = dep[pos] + 1;
      dfs1(v, pos);
    }
  };
  dep[r] = 1;
  dfs1(r, -1);

  Segment_Tree T(n, 1, n);
  T.tree.reserve(n * 50);
  for (int i = 1; i <= n; i++) {
    T.modify(T.root[i], dep[i], a[i]);
  }

  function<void(int, int)> dfs = [&] (int pos, int fa) {
    for (auto &v : G[pos]) {
      if (v == fa) continue;
      dfs(v, pos);
      T.root[pos] = T.merge_tree_lossless(T.root[pos], T.root[v]);
    }
  }; 
  dfs(r, -1);

  int m; cin >> m; 
  int last = 0;
  for (int i = 1; i <= m; i++) {
    int p, q; cin >> p >> q;
    int x = (p + last) % n + 1;
    int k = (q + last) % n; 
//    cout << x << " " << k << endl;
    last = T.query(T.root[x], dep[x], min(dep[x] + k, n)).minn;
    cout << last << endl;
  }
   
  return 0;
}
