//
//  f.cpp
//  2022-05-23 23:52
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

// 回滚并查集
// 1. 操作的两个数 >= 0
// 2. rollback 回滚到第 t 次操作，注意一次合并有两次操作
struct DSU {
  vector<int> f, size;   
  vector<array<int, 2>> ops;
  DSU(int n) : f(n + 1), size(n + 1, 1) { iota(f.begin(), f.end(), 0); }

  inline int find(int x) {
    while (x != f[x]) x = f[f[x]];
    return x;
  }

  inline bool merge(int x, int y) {
    x = find(x), y = find(y); 
    if (x == y) return false;
    if (size[x] > size[y]) swap(x, y);
    ops.push_back({x, f[x]});
    f[x] = y;    
    ops.push_back({~y, size[y]});
    size[y] += size[x];
    return true;
  }

  void rollback(int t) {
    while ((int) ops.size() > t) {
      assert(ops.size());
      auto [i, j] = ops.back();
      ops.pop_back();
      if (i >= 0) {
        f[i] = j;
      } else {
        size[~i] = j;
      }
    }
  }
};

signed main() {
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n; cin >> n;

  vector<vector<array<int, 2>>> G(n + 1);

  for (int i = 1; i <= n - 1; i++) {
    int u, v, c; cin >> u >> v >> c;
    G[c].push_back({u, v});
  }
  
  DSU T(n);
  int ans = 0; 
  function<void(int, int)> dfs = [&] (int l, int r) {
    if (l == r) {
      for (auto &it : G[l]) {
        ans += T.size[T.find(it[0])] * T.size[T.find(it[1])]; 
      }
      return;
    }
    int mid = (l + r) >> 1;
    {
      int save = T.ops.size();
      for (int i = l; i <= mid; i++) {
        for (auto &it : G[i]) {
          T.merge(it[0], it[1]);
        }
      }
      dfs(mid + 1, r); 
      T.rollback(save);
    }
    {
      int save = T.ops.size();
      for (int i = mid + 1; i <= r; i++) {
        for (auto &it : G[i]) {
          T.merge(it[0], it[1]);
        }
      }
      dfs(l, mid);
      T.rollback(save);
    }
  };
  dfs(1, n);
  cout << ans;
  return 0;
}
