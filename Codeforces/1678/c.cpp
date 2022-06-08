//
//  c.cpp
//  2022-05-08 23:36
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


// 二元索引树, Binary Indexed Tree, Fenwick树, 树状数组
// 特性:
// 1. 只能处理具有前缀和性质数组。
// 2. 下标绝对不能为 0
struct BIT {
  vector<int> tree;
  int limit;
  BIT (int n) : tree(n + 1, 0), limit(n) {}

  inline int lowbit(int x) { return x & (-x); }

  void modify(int x, int val) { // 单点修改
    assert(x >= 1);
    while (x <= limit) {
      tree[x] += val;     
      x += lowbit(x);
    }
  }

  int query(int x) {
    assert(x >= 0);
    int ans = 0;
    while (x) {
      ans += tree[x];
      x -= lowbit(x);
    }
    return ans;
  }

  int sum(int l, int r) {
    if (r < l) return 0;
    assert(l >= 1 && r >= 1);
    return query(r) - query(l - 1); 
  }
};

signed main() {
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  
  int z; cin >> z; 
  while (z--) {
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    int ans = 0;
    for (int i = 4; i <= n; i++) {
      int res = 0;
      BIT l(n), r(n);
      for (int j = 1; j <= i - 2; j++) {
        l.modify(a[j], 1);
      }
      for (int j = i - 1; j >= 2; j--) {
        if (a[j] > a[i]) ans += res; 
        
        res -= r.sum(a[j - 1] + 1, n);  
        r.modify(a[j], 1);
        
        l.modify(a[j - 1], -1); 
        res += l.sum(1, a[j] - 1);
      }
    }
    cout << ans << endl;
  }
  return 0;
}
