//
//  e.cpp
//  2022-05-07 00:13
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
  int z; cin >> z;  
  while (z--) {
    int p; cin >> p;
    int n = (1ll << p);
    vector<vector<int>> G(n + 1);
    vector<array<int, 2>> edges(n);
    for (int i = 1; i <= n - 1; i++) {
      int u, v; cin >> u >> v;
      G[u].push_back(v);
      G[v].push_back(u);
      edges[i] = {u, v};
    }
    vector<int> ans(n + 1, 0); ans[1] = n;
    map<int, map<int, int>> ans_edge;
    int tot = 0;
    function<void(int, int)> dfs = [&] (int pos, int fa) {
      for (auto &v: G[pos]) {
        if (v == fa) continue;
        if (ans[pos] >= n) {
          tot++;
          ans_edge[pos][v] = tot + n;
          ans_edge[v][pos] = tot + n;
          ans[v] = tot;
        } else {
          tot++;
          ans_edge[pos][v] = tot;
          ans_edge[v][pos] = tot;
          ans[v] = n + tot;
        }
        dfs(v, pos);
      }
    };
    dfs(1, -1);
    cout << 1 << endl;
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << " ";
    }
    cout << endl;
    for (int i = 1; i <= n - 1; i++) {
      cout << ans_edge[edges[i][0]][edges[i][1]] << " ";
    }
    cout << endl;

  }
   
  return 0;
}
