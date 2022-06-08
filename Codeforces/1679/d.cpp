//
//  d.cpp
//  2022-05-14 18:06
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


int check(const vector<int> &a, int limit, const vector<vector<int>> &G, int n, int k) {
  vector<vector<int>> g(n + 1);
  vector<int> degree(n + 1, 0); 
  vector<int> st;

  for (int i = 1; i <= n; i++) {
    if (a[i] <= limit) st.push_back(i);
  }

  if ((int) st.size() == 0) return false;

  for (auto &i : st) {
    for (auto &v : G[i]) {
      if (a[v] <= limit) {
        g[i].push_back(v);
        degree[v]++;
      }
    }
  }
  queue<int> que;
  for (auto &i : st) {
    if (degree[i] == 0) {
      que.push(i);
    }
  }
  int cnt = 0;
  while (que.empty() == 0) {
    int x = que.front(); que.pop();
    cnt++;
    for (auto &v : g[x]) {
      assert(a[v] <= limit);
      degree[v]--;
      if (degree[v] == 0) {
        que.push(v);
      }
    }
  }
  if (cnt != (int) st.size()) {
    // 有环
    return true;
  } else {
    vector<int> dp(n + 1, 0);
    function<int(int)> dfs = [&] (int pos) {
      if (dp[pos]) return dp[pos];
      dp[pos] = 1;
      int res = 0;
      for (auto &v : g[pos]) {
        res = max(res, dfs(v));
      }
      dp[pos] += res;
      return dp[pos];
    };
    int res = 0;
    for (auto &i : st) {
      res = max(res, dfs(i));
    }
    if (res >= k) return true;
    return false;
  }
}

signed main() {
  //file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  
  int n, m, k; cin >> n >> m >> k; 
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  vector<vector<int>> G(n + 1);
  for (int i = 1; i <= m; i++) {
    int u, v; cin >> u >> v;
    G[u].push_back(v);
  }
  int l = 1, r = 1e9; 
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (check(a, mid, G, n, k)) r = mid - 1; 
    else l = mid + 1;
  }
  
  if (l == 1e9 + 1) cout << -1;
  else cout << l;
   
  return 0;
}
