//
//  d.cpp
//  2022-04-20 00:11
//
//  Created by liznb
//  
//  https://codeforces.com/contest/1668/problem/D

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
const int N = 1e6 + 10;
struct Segment_Tree {
  // 先build！先build！先build！
  // 修改：区间加法
  // 查询：区间和，最大值，最小值
  // 1e6 很可能 MLE，一定要修改 N
  // 修改模板顺序：
  // 0. 如果是单点修改，一定是先删除 lazy 数组 和 push_down
  // 1. Info 结构体
  // 2. build 函数
  // 3. merge 函数
  // 4. add 函数
  // 5. push_down 函数 
  // modify 和 query 不需要修改！

  #define tl tree[pos].l 
  #define tr tree[pos].r 
  #define tv tree[pos].val
  struct Info {
    long long sum, maxi, mini; 
  };

  struct Tree {
    int l, r; 
    Info val;
  } tree[4 * N];  
  long long lazy[4 * N];

  // 合并两个儿子
  Info merge(Info a, Info b) {
    Info res;
    res.sum = a.sum + b.sum;
    res.maxi = max(a.maxi, b.maxi);
    res.mini = min(a.mini, b.mini);
    return res;
  }

  void build(int pos, int l, int r, long long *arr) {
    tl = l; tr = r;    
    lazy[pos] = 0ll;

    int m = l + (r - l) / 2;
    if (l == r) {
      tv.sum = arr[l]; 
      tv.maxi = arr[l];
      tv.mini = arr[l];
      return;
    } 
    build(pos << 1, l, m, arr);
    build(pos << 1 | 1, m + 1, r, arr);
    tv = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  }

  // 对树上一个位置进行修改
  void add(int pos, long long val) {
    lazy[pos] += val;
    tv.sum += (tr - tl + 1) * val;
    tv.maxi += val;
    tv.mini += val;
  }

  // 传递懒人标记
  void push_down(int pos) {
    if (lazy[pos] == 0) return; 
    add(pos << 1, lazy[pos]); 
    add(pos << 1 | 1, lazy[pos]);
    lazy[pos] = 0;
  } 

  void modify(int pos, int l, int r, long long val) {
    if (tl >= l && tr <= r) {
      add(pos, val);
      return;
    }  
    push_down(pos);
    int m = tl + (tr - tl) / 2;
    if (l <= m) modify(pos << 1, l, r, val);
    if (r > m) modify(pos << 1 | 1, l, r, val);
    tv = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  } 

  Info query(int pos, int l, int r) {
    if (tl >= l && tr <= r) {
      return tv;
    }   
    push_down(pos);
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
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int z; cin >> z; 
  while (z--) {
    int n; cin >> n;
    vector<int> a(n + 1), sum(n + 1, 0), dis(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      cin >> a[i]; 
      sum[i] = sum[i - 1] + a[i];
      dis[i] = sum[i];
    }

    sort(dis.begin(), dis.end());
    dis.erase(unique(dis.begin(), dis.end()), dis.end());
    vector<int> ord(n + 1); 
    for (int i = 1; i <= n; i++) {
      ord[i] = lower_bound(dis.begin(), dis.end(), sum[i]) - dis.begin() + 1;
    }
    // ST[i] = f[i] + dis(i + 1, j);  (sum[i] < sum[j])
    for (int i = 0; i <= (int) dis.size(); i++) arr[i] = -1e9;
    ST.build(1, 1, (int) dis.size(), arr);
    vector<int> f(n + 1, 0); 
    
    int p0 = lower_bound(dis.begin(), dis.end(), 0) - dis.begin() + 1;
    ST.modify(1, p0, p0, 1e9);

    for (int i = 1; i <= n; i++) {
      if (a[i] > 0) f[i] = f[i - 1] + 1;
      if (a[i] < 0) f[i] = f[i - 1] - 1;
      if (a[i] == 0) f[i] = f[i - 1];

      ST.modify(1, 1, (int) dis.size(), 1);

      if (ord[i] != 1)
        f[i] = max(ST.query(1, 1, ord[i] - 1).maxi, f[i]); 
      int res = ST.query(1, ord[i], ord[i]).sum; 
      if (res < f[i]) {
        ST.modify(1, ord[i], ord[i], -res + f[i]);
      }
    }
    cout << f[n] << endl;
  }
  return 0;
}
