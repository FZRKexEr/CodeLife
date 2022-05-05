//
//  f.cpp
//  2022-05-02 23:48
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

random_device rd; // 使用硬件熵源的随机数生成器
mt19937 seed(rd());
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
 * 5. !!!!! pos 是 0-indexed !!!!
 * 优化：
 * 1. 模板内置了 sum，maxn，minn。可以根据题目要求删除一些，减少空间消耗。
 * 2. 还可以进一步优化空间：把 l 和 r 也删掉，直接在函数里传参
 * 3. 参考：逆序对问题：n = 5e5, 数值范围 1e9, 做了1，2优化后消耗 75mb 空间。
 */

const long long INF = 0x3f3f3f3f3f3f3f3f;
struct Segment_Tree {

  struct Info {
    long long sum; 
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
    Info res;  //注意初始值

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
  int n, m, q;  
  cin >> n >> m >> q;

  map<array<int, 2>, int> ord;
  int tot = 1;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      ord[{j, i}] = tot;
      tot++; 
    }
  }
  
  vector<vector<int>> a(n + 1, vector<int> (m + 1, 0));
  Segment_Tree T(1, n * m + 3);
  for (int i = 1; i <= n; i++) {
    string s; cin >> s;
    for (int j = 0; j < m; j++) {
      if (s[j] == '*') {
        a[i][j + 1] = 1;
        T.modify(0, ord[{i, j + 1}], 1);
      }
    }
  }
  for (int i = 1; i <= q; i++) {
    int x, y; cin >> x >> y;
    int o = ord[{x, y}];
    if (T.query(0, o, o).sum == 0) {
      T.modify(0, o, 1); 
    } else {
      T.modify(0, o, -1);
    }
    int goal = T.query(0, 1, n * m + 3).sum; 
    
    cout << T.query(0, goal + 1, n * m + 3).sum << endl;
  }
   
  return 0;
}
