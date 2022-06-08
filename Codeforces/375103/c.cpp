//
//  c.cpp
//  2022-04-29 22:10
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

const int MOD = 998244353;
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
int vis[505][505];

struct Combination {
  // 务必 #define int long long
  // 适用于小模数和大模数
  // 复杂度 O(n)
  vector<int> fac, cnt;
  int MOD;

  Combination(int n, int p) : fac(n + 1), cnt(n + 1), MOD(p) {
    fac[0] = fac[1] = 1; cnt[0] = cnt[1] = 0;
    for (int i = 2; i <= n; i++) {
      fac[i] = fac[i - 1] * i;
      cnt[i] = cnt[i - 1];
      while (fac[i] % MOD == 0) {
        cnt[i]++;
        fac[i] /= MOD;
      }
      fac[i] %= MOD;
    }
  } 
  
  int power(int a, int b) {
    assert(b >= 0);
    int base = a % MOD, ans = 1ll;
    while (b) {
      if (b & 1) ans = ans * base % MOD;
      base = base * base % MOD;
      b >>= 1;
    }
    return ans;
  }

  int inv(int x) {
    return power(x, MOD - 2);
  }

  int C(int a, int b) { // C_a^b
    if (vis[a][b] != -1) return vis[a][b];
    if (b > a) return 0;
    if (cnt[a] != cnt[b] + cnt[a - b]) {
      assert(0);
      return 0;
    }
    return vis[a][b] = fac[a] * inv(fac[b] * fac[a - b] % MOD) % MOD;
  }
};

void file() {
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
#endif
}

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  int n, limit; cin >> n >> limit;  
  vector<vector<int>> dp(n + 1, vector<int>(limit + 1, 0));
  memset(vis, -1, sizeof(vis));
  Combination T(1000, MOD);

  for (int i = 0; i <= limit; i++) {
    dp[0][i] = 1;
  }

  for (int i = 1; i <= n - 1; i++) {
    for (int j = 1; j <= limit; j++) {
      for (int t = 1; t <= i; t++) {
        int res = dp[i - t][j - 1] * T.C(n - 1 - (i - t), t) % MOD * power(limit - j + 1, (i - t) * t + T.C(t, 2)) % MOD;
        (dp[i][j] += res) %= MOD;
      }
      dp[i][j] += dp[i][j - 1];
      dp[i][j] %= MOD;
    }
  }
  cout << dp[n - 1][limit];

  return 0;
}
