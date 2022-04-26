//
//  l.cpp
//  2022-04-25 20:12
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
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, m, s; cin >> n >> m >> s;
  vector<vector<int>> G(n + 1);
  for (int i = 1; i <= m; i++) {
    int u, v; cin >> u >> v; 
    G[u].push_back(v);
  }
  vector<int> pre(n + 1, 0), vis(n + 1, 0), belong(n + 1);

  function<void(int)> dfs = [&] (int pos) {
    assert(belong[belong[pos]] == belong[pos]);
    for (auto &v : G[pos]) {
      if (vis[v]) continue;
      vis[v] = 1;
      pre[v] = pos;
      belong[v] = belong[pos];
      dfs(v);
    }
  };

  belong[s] = s;
  pre[s] = 0;
  vector<int> root(n + 1, 0);
  vis[s] = 1;
  for (auto &v : G[s]) {
    if (vis[v]) continue;
    root[v] = 1;
    vis[v] = 1;
    belong[v] = v;
    pre[v] = s;
    dfs(v);
  }
  
  for (int i = 1; i <= n; i++) {
    if (vis[i] == 0) continue;
    for (auto &v : G[i]) {
      if (vis[v] == 0) continue;
      if (v == s) continue;
      if (root[v] == 1 && i == s) {
        continue;
      }
      if (belong[v] != belong[i]) {
        cout << "Possible" << endl;
        vector<int> ans1, ans2;
        int p = v;
        while (p != 0) {
          ans1.push_back(p);
          p = pre[p];
        }
        reverse(ans1.begin(), ans1.end());
        ans2.push_back(v);
        p = i;
        while (p != 0) {
          ans2.push_back(p);
          p = pre[p];
        }
        reverse(ans2.begin(), ans2.end());

        cout << ans1.size() << endl;
        for (auto &it : ans1) cout << it << " ";
        cout << endl;
        cout << ans2.size() << endl;
        for (auto &it : ans2) cout << it << " ";
        cout << endl;

        return 0;
      }
    }
  }
  cout << "Impossible" << endl;
  return 0;
}
