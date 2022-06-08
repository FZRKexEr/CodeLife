//
//  e.cpp
//  2022-05-17 22:06
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
  string s; cin >> s; 
  int all = 0;  
  for (int i = 0; i < (int) s.length(); i++) 
    all += s[i] == '?';
  
  vector<vector<int>> f(n, vector<int> (n, -1));
  vector<vector<int>> g(n, vector<int> (n, -1));

  function<array<int, 2>(int, int)> dp = [&] (int l, int r) {
    if (r < l) return (array<int, 2>) {0, 0};
    if (l == r) {
      if (s[l] == '?') return (array<int, 2>) {0, 1};
      else return (array<int, 2>) {0, 0};
    }
    if (f[l][r] != -1) return (array<int, 2>) {f[l][r], g[l][r]}; 

    auto res = dp(l + 1, r - 1);
    if (res[1] == -1) {
      f[l][r] = 0;
      g[l][r] = -1;
      return (array<int, 2>) {0, -1};
    }

    if (s[l] == '?' && s[r] == '?') {
      f[l][r] = res[0];
      g[l][r] = res[1] + 1;
    } else if (s[l] == '?') {
      f[l][r] = res[0] | (1 << (s[r] - 'a'));
      g[l][r] = res[1];
    } else if (s[r] == '?') {
      f[l][r] = res[0] | (1 << (s[l] - 'a'));
      g[l][r] = res[1];
    } else {
      if (s[l] == s[r]) {
        f[l][r] = res[0];
        g[l][r] = res[1];
      } else {
        f[l][r] = 0;
        g[l][r] = -1;
      }
    }
    return (array<int, 2>) {f[l][r], g[l][r]};
  };

  vector<vector<int>> a(1ll << 17, vector<int>(18, 0)); 
  
  for (int i = 0; i < n; i++) {
    int cnt = 0;
    for (int j = i; j < n; j++) {
      if (s[j] == '?') cnt++;
      auto [u, v] = dp(i, j);
      if (v == -1) continue;
      v += all - cnt; 
      for (int i = 1; i <= 17; i++) {
        a[u][i] += power(i, v); 
        a[u][i] %= MOD;
      }
    }
  }
  
//  // 无损枚举子集
//  vector<int> ans(1 << 17);
//  for (int mask = 0; mask < (1 << 17); mask++){
//    int cnt = 0;
//    for (int i = 0; i <= 17; i++) {
//      if (mask >> i & 1) cnt++;
//    }
//    ans[mask] = a[0][cnt];
//    for(int i = mask; i > 0; i = (i - 1) & mask) {
//       
//      ans[mask] += a[i][cnt];
//      ans[mask] %= MOD;
//    }
//  }
  
  // SOSDP
  for (int i = 0; i < 17; i++) {
    for (int j = 0; j < (1ll << 17); j++) {
      for (int k = 1; k <= 17; k++) {
        if (j >> i & 1)
          (a[j][k] += a[j ^ (1ll << i)][k]) %= MOD;
      }
    }
  }

  int q; cin >> q; 
  for (int i = 1; i <= q; i++) {
    string t; cin >> t;
    int mask = 0;
    for (auto &it : t) mask |= (1 << (it - 'a'));
    cout << a[mask][(int) t.length()] << endl;
  }
  
  return 0;  
}
