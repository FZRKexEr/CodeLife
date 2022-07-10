//
//  b.cpp
//  2022-04-27 00:59
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

void file() {
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
#endif
}
const int N = 1e5 + 10;
int MOD = 998244353;

struct Segment_Tree {

  // 修改：乘法和加法混合运算
  // 查询：区间和
  // 修改和查询前一定要 build
  // 注意根据题目数据范围来修改 N ， 1e6 很容易 MLE。
  // 关键顺序：
  // 1. 先乘法 push_down ，再加法 push_down
  // 2. 乘法的 lazy 标记下传需要同时更新乘法和加法的 lazy
  // 3. 乘法的 lazy 标记初始化为1

  #define tl tree[pos].l 
  #define tr tree[pos].r 
  #define tv tree[pos].val
  struct Info {
    long long sum; 
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
    return res;
  }

  void build(int pos, int l, int r, long long *arr) {

    tl = l; tr = r;    
    lazy1[pos] = 1; 
    lazy2[pos] = 0;

    int m = l + (r - l) / 2;
    if (l == r) {
      tv.sum = arr[l] % MOD; 
      return;
    } 
    build(pos << 1, l, m, arr);
    build(pos << 1 | 1, m + 1, r, arr);
    tv = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  }

  // 对树上一个位置进行修改
  void add(int pos, long long val, int o) {
    if (o == 1) {
      (lazy2[pos] *= val) %= MOD;
      (lazy1[pos] *= val) %= MOD; 
      (tv.sum *= val) %= MOD;
    } else {
      (lazy2[pos] += val) %= MOD;
      (tv.sum += (tr - tl + 1) * val % MOD) %= MOD;
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
    tv = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
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

    tv = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
    return res;
  }
  #undef tl
  #undef tr
  #undef tv
} ST;

int arr[N];
signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, m; cin >> n >> m; 
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }
  ST.build(1, 1, n, arr);
  for (int i = 1; i <= m; i++) {
    int o; cin >> o;
    if (o == 1) {
      int l, r, val; cin >> l >> r >> val; 
      ST.modify(1, l, r, val, o);
    } else if(o == 2) {
      int l, r, val; cin >> l >> r >> val;
      ST.modify(1, l, r, val, o);
    } else {
      int l, r; cin >> l >> r;
      cout << ST.query(1, l, r).sum << endl;;
    }
  }
   
  return 0;
}
