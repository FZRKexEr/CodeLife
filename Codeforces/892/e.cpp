//
//  e.cpp
//  2022-05-24 13:27
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
  int n, m; cin >> n >> m;

  vector<array<int, 3>> edges(m + 1), bedges;
    
  for (int i = 1; i <= m; i++) {
    cin >> edges[i][1] >> edges[i][2] >> edges[i][0];
  }

  bedges = edges;
  sort(bedges.begin() + 1, bedges.end());
  
  int q; cin >> q;

  vector<int> ans(q + 1, 1);
  vector<vector<vector<int>>> belong(5e5 + 1);
   
  for (int i = 1; i <= q; i++) {
    int k; cin >> k;
    map<int, vector<int>> mp; 
    for (int j = 1; j <= k; j++) {
      int val; cin >> val;
      mp[edges[val][0]].push_back(val);
    }
    for (auto &it : mp) {
      it.second.push_back(i);
      belong[it.first].push_back(it.second);
    }
  }

  DSU T(n);   
  int last = 1;

  for (int i = 1; i <= 5e5; i++) {
    while (last <= m && bedges[last][0] <= i - 1) {
      auto [w, u, v] = bedges[last];
      if (T.find(u) != T.find(v)) T.merge(u, v);    
      last++;
    }
    int t = T.ops.size();  
    for (auto &it : belong[i]) {
      for (int j = 0; j < (int) it.size() - 1; j++) {
        auto jt = it[j];
        auto [w, u, v] = edges[jt];
        if (T.find(u) == T.find(v)) {
          ans[it.back()] = 0;
        } else {
          T.merge(u, v);
        }
      }
      T.rollback(t);
    }
  }

  for (int i = 1; i <= q; i++) {
    if (ans[i]) cout << "YES" << endl;
    else cout << "NO" << endl;
  }
   
  return 0;
}
