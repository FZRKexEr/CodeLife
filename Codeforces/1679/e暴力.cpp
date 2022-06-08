//
//  e.cpp
//  2022-05-17 16:52
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

  vector<int> sum(s.length() + 1);
  sum[0] = s[0] == '?' ? 1 : 0;
  for (int j = 1; j < (int) s.length(); j++) {
    sum[j] = sum[j - 1] + (s[j] == '?' ? 1 : 0); 
  }
  int all = sum[(int) s.length() - 1];

  int q; cin >> q;  
  for (int i = 1; i <= q; i++) {
    string t; cin >> t;

    vector<int> has(300, 0); 
    for (auto &it : t) has[it] = 1; 

    int ans = 0;

    vector<vector<int>> f(s.length(), vector<int> (s.length(), -1));
    
    function<int(int, int)> dp = [&] (int l, int r) {
      if (f[l][r] != -1) return f[l][r]; 
      if (r < l) return f[l][r] = 1ll;
      if (l == r) {
        if (s[l] == '?') return f[l][r] = t.length();
        else return f[l][r] = 1ll;
      }
      if (s[l] == '?' && s[r] == '?') {
        return f[l][r] = (int) t.length() % MOD * dp(l + 1, r - 1) % MOD; 
      } 
      else if (s[l] == '?') {
        if (has[s[r]] == 0) return f[l][r] = 0ll;
        return f[l][r] = dp(l + 1, r - 1);
      }
      else if (s[r] == '?') {
        if (has[s[l]] == 0) return f[l][r] = 0ll;
        return f[l][r] = dp(l + 1, r - 1);
      } else {
        if (s[l] == s[r]) return f[l][r] = dp(l + 1, r - 1);
        else return f[l][r] = 0ll;
      }
    };
    
    for (int l = 0; l < (int) s.length(); l++) {
      for (int r = l; r < (int) s.length(); r++) {
        int res = dp(l, r);
        if (l == 0) {
          res *= power(t.length(), all - sum[r]);
          res %= MOD;
        } else {
          res *= power(t.length(), all - (sum[r] - sum[l - 1]));
          res %= MOD;
        }
        ans = ans + res; 
        ans %= MOD;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
