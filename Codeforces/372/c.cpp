//
//  c.cpp
//  2022-05-08 15:23
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define endl '\n'
#define int long long
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

signed main() {
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, m, d; cin >> n >> m >> d;   
  vector<array<int, 3>> a(m + 1);
  for (int i = 1; i <= m; i++) {
    cin >> a[i][0] >> a[i][1] >> a[i][2]; 
  }

  int o = 1;
  vector<vector<int>> dp(2, vector<int> (n + 1, 0));
  
  for (int i = 1; i <= n; i++) {
    dp[1][i] = a[1][1] - abs(a[1][0] - i);
  }
  for (int i = 2; i <= m; i++) {
    o ^= 1;
    int t = (a[i][2] - a[i - 1][2]) * d;  
    deque<array<int, 2>> que;  
    for (int j = 1; j <= min(t, n); j++) {
      array<int, 2> x = {dp[o ^ 1][j], j};
      while (!que.empty() && que.back() < x) que.pop_back();
      que.push_back(x);
    }
    for (int j = 1; j <= n; j++) {
      int c = a[i][1] - abs(a[i][0] - j); 
      if (j + t <= n) {
        array<int, 2> x = {dp[o ^ 1][j + t], j + t};
        while (!que.empty() && que.back() < x) que.pop_back();
        que.push_back(x);
      }
      while (que.front()[1] < j - t) que.pop_front();
      dp[o][j] = que.front()[0] + c; 
    }
  }
  int ans = -0x3f3f3f3f3f3f3f3f;
  for (int i = 1; i <= n; i++) ans = max(ans, dp[o][i]);
  cout << ans;

  return 0;
}
