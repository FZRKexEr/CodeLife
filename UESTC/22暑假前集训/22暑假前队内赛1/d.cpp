//
//  d.cpp
//  2022-04-26 23:38
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

signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n; cin >> n; 
  vector<vector<int>> G(n + 1);
  for (int i = 1; i <= n; i++) {
    int u, v; cin >> u >> v; 
    G[u].push_back(v);
    G[v].push_back(u);
  }
  vector<int> vis(n + 1, 0), pre(n + 1), ring(n + 1, 0);
  function<int(int, int)> dfs = [&](int pos, int fa) {
    int cnt = 0;
    for (auto &v : G[pos]) {
      if (v == fa && ++cnt == 1) continue;
      if (vis[v]) {
        int p = pos;
        ring[v] = 1;
        while (p != v) {
          ring[p] = 1;
          p = pre[p];
        }
        return true; 
      } else {
        vis[v] = 1;
        pre[v] = pos;
        if (dfs(v, pos)) return true;
      }
    }
    return false;
  };
  vis[1] = 1;
  pre[1] = -1;
  dfs(1, -1);
  vector<int> d(n + 1, 0);
  function<void(int, int)> dfs1 = [&](int pos, int fa) {
    for (auto &v : G[pos]) {
      if (v == fa) continue;
      if (ring[v]) continue;
      d[v] = d[pos] + 1;
      dfs1(v, pos);
    }
  };
  for (int i = 1; i <= n; i++) {
    if (ring[i]) {
      dfs1(i, -1);
    }
  }
  for (int i = 1; i <= n; i++) cout << d[i] << " ";
   
  return 0;
}
