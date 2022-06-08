//
//  f.cpp
//  2022-05-22 14:52
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

// 可持久化线段树
// 1. vector<int> ver 保存版本, add_ver 会添加一个版本.
// 2. 注意：访问版本一定用 ver[i], 访问版本一定用 ver[i], 访问版本一定用 ver[i]
// 3. 如果操作范围是连续的 1-n, 且 n 较小，可以直接 O(n) build.
// 4. modify 不增加版本修改(主要用于不使用 build 的初始化), pmodify 是可持久化修改
//
// 优化空间的方法:
// 1. 关闭 long long
// 2. Info 里面把无关的变量删了
// 3. T.tree.reserve() , 一般大小是 log2(n) * m , 可以减少很多空间
// 
// 前缀和性质:
// 不同的版本按照时间顺序具有前缀和性质，可以相减

const int INF = 0x3f3f3f3f3f3f3f3f;
struct Segment_Tree {

  struct Info {
    int minn; 
    Info () { minn = INF; }
  };

  struct Tree {
    int ls, rs; // 左儿子，右儿子 编号
    int l, r; // 左边界，右边界
    Info dat;
    Tree(int a, int b, int c, int d) : ls(a), rs(b), l(c), r(d) {} 
  };

  vector<Tree> tree; 
  vector<int> ver;

  Segment_Tree(int l, int r) {
    tree.push_back({-1, -1, l, r});
    ver.push_back((int) tree.size() - 1);
  }
 
  int add_ver(int l, int r) {
    tree.push_back({-1, -1, l, r}); 
    ver.push_back((int) tree.size() - 1);
    return (int) tree.size() - 1;
  }

  int insert(int l, int r) {
    tree.push_back({-1, -1, l, r});
    return (int) tree.size() - 1;
  }
 
  Info merge(const Info &a, const Info &b) {
    Info res;
    res.minn = min(a.minn, b.minn);
    return res;
  }

  void add(int pos, int val) {
    tree[pos].dat.minn = val;
  }

  void push_up(int pos) {
    tree[pos].dat.minn = INF;
    if (tree[pos].ls != -1) tree[pos].dat = merge(tree[pos].dat, tree[tree[pos].ls].dat);
    if (tree[pos].rs != -1) tree[pos].dat = merge(tree[pos].dat, tree[tree[pos].rs].dat);
  }

//  void build(int pos, vector<int> &arr) {
//    if (tree[pos].l == tree[pos].r) {
//      tree[pos].dat.sum = arr[tree[pos].l];
//      return;
//    }
//    int mid = (tree[pos].l + tree[pos].r) >> 1;
//    if (tree[pos].ls == -1) tree[pos].ls = insert(tree[pos].l, mid);
//    if (tree[pos].rs == -1) tree[pos].rs = insert(mid + 1, tree[pos].r);
//    build(tree[pos].ls, arr); 
//    build(tree[pos].rs, arr);
//    push_up(pos);
//  }

//  // 普通修改，不增加版本  
//  void modify(int pos, int goal, int val) {
//    if (tree[pos].l == tree[pos].r) {
//      add(pos, val);
//      return;
//    }
//    int mid = (tree[pos].l + tree[pos].r) >> 1;
//    if (goal <= mid) {
//      if (tree[pos].ls == -1) tree[pos].ls = insert(tree[pos].l, mid);
//      modify(tree[pos].ls, goal, val);
//    } else {
//      if (tree[pos].rs == -1) tree[pos].rs = insert(mid + 1, tree[pos].r);
//      modify(tree[pos].rs, goal, val);
//    }
//    push_up(pos);
//  }
  
  int calc_cnt(int l, int r, vector<array<int, 2>> &arr) {
    int pr = upper_bound(arr.begin(), arr.end(), (array<int, 2>) {r, INF}) - arr.begin(); 
    int pl = lower_bound(arr.begin(), arr.end(), (array<int, 2>) {l, -INF}) - arr.begin();  
    return pr - pl;
  }

  void pmodify(int base, int pos, vector<array<int, 2>> &arr) {
    if (tree[pos].l == tree[pos].r) {
      tree[pos].dat = tree[base].dat; 
      auto it = lower_bound(arr.begin(), arr.end(), (array<int, 2>){tree[pos].l, 0});
      add(pos, (*it)[1]);
      return;        
    }
    int mid = (tree[pos].l + tree[pos].r) >> 1;
    if (calc_cnt(tree[pos].l, mid, arr)) {
      tree[pos].ls = insert(tree[pos].l, mid);
      if (tree[base].ls == -1) tree[base].ls = insert(tree[base].l, mid);
      pmodify(tree[base].ls, tree[pos].ls, arr);
    } else {
      tree[pos].ls = tree[base].ls;
    }
    if (calc_cnt(mid + 1, tree[pos].r, arr)) {
      tree[pos].rs = insert(mid + 1, tree[pos].r);
      if (tree[base].rs == -1) tree[base].rs = insert(mid + 1, tree[base].r);
      pmodify(tree[base].rs, tree[pos].rs, arr);
    } else {
      tree[pos].rs = tree[base].rs;
    }
    push_up(pos);
  }

  Info query(int pos, int l, int r) {
    if (tree[pos].l >= l && tree[pos].r <= r) {
      return tree[pos].dat;
    }
    int mid = (tree[pos].l + tree[pos].r) >> 1;
    Info res; res.minn = INF; //注意初始值

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
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  vector<vector<int>> G(n + 1); 
  for (int i = 1; i <= n - 1; i++) {
    int u, v; cin >> u >> v;
    G[u].push_back(v); 
    G[v].push_back(u);
  }
  vector<int> st(n + 1, -1), ed(n + 1, -1), dep(n + 1, -1);
  int tot = 0;
  vector<vector<int>> belong(n + 1);
  function<void(int, int)> dfs = [&] (int pos, int fa) {
    st[pos] = ++tot;
    belong[dep[pos]].push_back(pos);
    for (auto &v : G[pos]) {
      if (v == fa) continue;  
      dep[v] = dep[pos] + 1;
      dfs(v, pos);
    }
    ed[pos] = tot; 
  };

  dep[r] = 1; 
  dfs(r, -1);
  Segment_Tree T(1, n);

  for (int i = 1; i <= n; i++) {
    T.add_ver(1, n);
    vector<array<int, 2>> wait;
    for (auto &it : belong[i]) {
      wait.push_back({st[it], a[it]});
    }
    sort(wait.begin(), wait.end());
    T.pmodify(T.ver[i - 1], T.ver[i], wait);
  }

  int m; cin >> m;
  int last = 0;
  for (int i = 1; i <= m; i++) {
    int p, q; cin  >> p >> q;  
    int x = (p + last) % n + 1;
    int k = (q + last) % n; 
    int limit = min(dep[x] + k, n);
    last = T.query(T.ver[limit], st[x], ed[x]).minn;
    cout << last << endl;
  }

  return 0;
}
