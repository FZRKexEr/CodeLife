//
//  c.cpp
//  2022-05-12 11:53
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

signed main() {
  
  file();
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n; cin >> n; 
  vector<vector<int>> a(n + 1, vector<int> (n + 1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
      a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
    }
  }

  vector<vector<int>> dp(n + 1, vector<int> (n + 1, -1)); 
  const int INF = 0x3f3f3f3f3f3f3f3f;

  auto sum = [&] (int x1, int y1, int x2, int y2) {
    if (y1 < y2) return 0ll;
    assert(x1 >= x2);
    return a[x1][y1] - a[x1][y2 - 1] - a[x2 - 1][y1] + a[x2 - 1][y2 - 1];
  };

  vector<vector<int>> ans(n + 1, vector<int> (n + 1, -1)); 
  function <void(int, int)> dfs = [&] (int l, int r) {
    if (dp[l][r] != -1) return;
    auto &t = dp[l][r] = INF;
    if (l == r) { ans[l][r] = l, t = 0; return; }
    for (int i = l + 1; i < r; i++) {
      int res = 0;
      res += sum(i - 1, l - 1, l, 1) + sum(i - 1, n, l, i); // l - i - 1
      res += sum(r, i, i + 1, 1) + sum(r, n, i + 1, r + 1); // i + 1 - r

      dfs(l, i - 1); dfs(i + 1, r);
      if (dp[l][i - 1] + dp[i + 1][r] + res < t) {
        t = dp[l][i - 1] + dp[i + 1][r] + res;
        ans[l][r] = i;
      }
    }
    dfs(l + 1, r); dfs(l, r - 1);
    if (dp[l + 1][r] + sum(r, l, l + 1, 1) + sum(r, n, l + 1, r + 1) < t) {
      ans[l][r] = l;
    }
    t = min(t, dp[l + 1][r] + sum(r, l, l + 1, 1) + sum(r, n, l + 1, r + 1));
    if (dp[l][r - 1] + sum(r - 1, l - 1, l, 1) + sum(r - 1, n, l, r) < t) {
      ans[l][r] = r;
    }
    t = min(t, dp[l][r - 1] + sum(r - 1, l - 1, l, 1) + sum(r - 1, n, l, r));
  };

  dfs(1, n);

  cout << dp[1][n] << endl;
  return 0;
}
